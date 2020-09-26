#include <iostream>

#include <boost/asio.hpp>

#include "server.h"
#include "tcp_connection_manager.h"

int main(int argc, char* argv[])
{
   if (argc != 4)
   {
      std::cout << "Usage: webserver <host> <port> <doc-root>" << std::endl;
      return 1;
   }

   auto connectionHandler = std::make_unique<TcpConnectionManager>(argv[3]);
   Server s(std::move(connectionHandler));
   s.setup(argv[1], argv[2]);
   s.run();

   return 0;
}
