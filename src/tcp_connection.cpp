#include "tcp_connection.h"

#include <array>
#include <iostream>
#include <memory>

#include "tcp_connection_manager.h"

std::shared_ptr<TcpConnection> TcpConnection::create(
      TcpConnectionManager& manager,
      tcp::socket&& socket)
{
   TcpConnection* c = new TcpConnection(manager, std::move(socket));
   auto sp = std::shared_ptr<TcpConnection>(c);
   sp->doRead();
   return sp;
}

TcpConnection::TcpConnection(
      TcpConnectionManager& manager,
      tcp::socket&& socket)
 : m_socket(std::move(socket)), m_manager(manager)
{}

void TcpConnection::doRead()
{
   auto self = shared_from_this();
   auto msg = std::make_shared< std::array<char, 8192> >();
   m_socket.async_read_some(
         boost::asio::buffer(*msg),
         [self, msg](const boost::system::error_code& error, size_t bytesRead) {
            if (error)
            {
               self->close();
            }
            else
            {
               std::cout.write(msg->data(), bytesRead) << std::endl;
               self->doRead();
            }
         });
}

void TcpConnection::close()
{
   m_socket.close();
   m_manager.removeConnection(shared_from_this());
}
