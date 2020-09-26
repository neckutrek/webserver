#ifndef INCGRD_TCP_CONNECTION_MANAGER_H
#define INCGRD_TCP_CONNECTION_MANAGER_H

#include <string>
#include <set>
#include <memory>

#include <boost/asio.hpp>

#include "tcp_connection.h"

using boost::asio::ip::tcp;

/**
 * Handler keeping track of TcpConnections
 */
class TcpConnectionManager
{
public:
                           TcpConnectionManager(const std::string& docRoot);
                           ~TcpConnectionManager() = default;

                           TcpConnectionManager(TcpConnectionManager&) = delete;
                           TcpConnectionManager(const TcpConnectionManager&) = delete;
         TcpConnectionManager& operator=(TcpConnectionManager&) = delete;
   const TcpConnectionManager& operator=(const TcpConnectionManager&) = delete;

         TcpConnectionHandle  addConnection(tcp::socket&& socket);
         void              removeConnection(std::shared_ptr<TcpConnection> connection);

private:
         std::set<std::shared_ptr<TcpConnection>>    m_connections;
};

#endif
