#include "tcp_connection_manager.h"
#include <memory>

TcpConnectionManager::TcpConnectionManager(
   const std::string& docRoot)
{

}

TcpConnectionHandle TcpConnectionManager::addConnection(
   tcp::socket&& socket)
{
   m_connections.insert(TcpConnection::create(*this, std::move(socket)));
   return 0;
}

void TcpConnectionManager::removeConnection(std::shared_ptr<TcpConnection> connection)
{
   m_connections.erase(connection);
}
