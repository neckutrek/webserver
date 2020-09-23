#include <iostream>
#include <array>

#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      std::cout << "Usage: client <host>" << std::endl;
      return 1;
   }

   boost::asio::io_context io;

   udp::resolver resolver(io);
   udp::resolver::results_type receiverEndpoins =
      resolver.resolve(udp::v4(), argv[1], "daytime");

   udp::socket socket(io);
   socket.open(udp::v4());

   socket.send_to(boost::asio::buffer({0}), *receiverEndpoins.begin());

   std::array<char, 128> msg;
   udp::endpoint senderEndpoint;
   size_t len = socket.receive_from(boost::asio::buffer(msg), senderEndpoint);

   std::cout.write(msg.data(), len);

   return 0;
}

