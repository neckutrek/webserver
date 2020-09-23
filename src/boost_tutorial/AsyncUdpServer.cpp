#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::udp;

/**
 *
 */
std::string getDateTime()
{
   std::time_t now = std::time(0);
   return std::ctime(&now);
}

/**
 *
 */
int main(int argc, char* argv[])
{
   boost::asio::io_context io;

   udp::socket socket(io, udp::endpoint(udp::v4(), 13));

   udp::endpoint clientEndpoint;

   std::function<void(void)> waitReceive;

   auto onRequest = [&socket, &clientEndpoint, &waitReceive](const boost::system::error_code& error, std::size_t bytesTransfered)
   {
      if (!error || error == boost::asio::error::message_size)
      {
         auto msg = std::make_shared<std::string>(getDateTime());
         socket.async_send_to(
            boost::asio::buffer(*msg),
            clientEndpoint,
            [msg](const boost::system::error_code& error, std::size_t bytesTransfered){});
      }
      waitReceive();
   };

   waitReceive = [&socket, &clientEndpoint, &onRequest]()
   {
      char requestMsg[1] = {0};
      socket.async_receive_from(boost::asio::buffer(requestMsg), clientEndpoint, onRequest);
   };

   waitReceive();
   io.run();

   return 0;
}

