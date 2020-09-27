#include "server.h"

#include <memory>

Server::Server(std::unique_ptr<TcpConnectionManager>&& connectionManager)
 : m_ioContext(1), m_acceptor(m_ioContext), m_connectionManager(std::move(connectionManager))
{}

void Server::close()
{
   m_acceptor.close();
}

void Server::doAwaitAccept()
{
   m_acceptor.async_accept(
         [this](const boost::system::error_code& error, tcp::socket socket)
         {
            if (error || !m_acceptor.is_open())
            {
               return;
            }
            m_connectionManager->addConnection(std::move(socket));
            doAwaitAccept();
         }
      );
}

void Server::doAwaitStop()
{
   auto signals = std::make_shared<boost::asio::signal_set>(m_ioContext);
   signals->add(SIGINT);
   signals->add(SIGTERM);
   signals->async_wait(
         [this, signals](const boost::system::error_code& error, int signo)
         {
            close();
         }
      );
}

void Server::run()
{
   m_ioContext.run();
}

void Server::setup(
   const std::string& hostAddress,
   const std::string& hostPort)
{
   tcp::resolver resolver(m_ioContext);
   tcp::resolver::results_type endpoints = resolver.resolve(hostAddress, hostPort);
   auto endpoint = static_cast<tcp::endpoint>( *endpoints.begin() );

   m_acceptor.open(endpoint.protocol());
   m_acceptor.set_option(tcp::acceptor::reuse_address(true));
   m_acceptor.bind(endpoint);
   m_acceptor.listen();

   doAwaitStop();
   doAwaitAccept();
}
