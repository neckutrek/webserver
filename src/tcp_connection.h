#ifndef INCGRD_TCP_CONNECTION_H
#define INCGRD_TCP_CONNECTION_H

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using TcpConnectionHandle = unsigned int;

class TcpConnectionManager;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
   static   std::shared_ptr<TcpConnection>
                           create(TcpConnectionManager& manager, tcp::socket&& socket);
private:
                           TcpConnection(TcpConnectionManager& manager, tcp::socket&& socket);

         tcp::socket       m_socket;

         TcpConnectionManager&
                           m_manager;

         void              doRead();
         void              close();
};

#endif
