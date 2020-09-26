#ifndef INCGRD_SERVER_H
#define INCGRD_SERVER_H

#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "tcp_connection_manager.h"

using boost::asio::ip::tcp;

/**
 * A Server asynchronously listens to incoming TCP connections on a certain
 * host:port endpoint and forwards them to a TcpConnectionManager.
 */
class Server
{
public:
                           Server(
                             std::unique_ptr<TcpConnectionManager>&& connectionManager);

                           Server() = delete;
                           Server(Server&) = delete;
                           Server(const Server&) = delete;
            Server&        operator=(Server&) = delete;
            const Server&  operator=(const Server&) = delete;

            void           setup(
                              const std::string& hostAddress,
                              const std::string& hostPort);

            void           run();
            void           close();

private:
            boost::asio::io_context
                           m_ioContext;

            tcp::acceptor  m_acceptor;

            std::unique_ptr<TcpConnectionManager>
                           m_connectionManager;

            void           doAwaitAccept();
            void           doAwaitStop();
};

#endif
