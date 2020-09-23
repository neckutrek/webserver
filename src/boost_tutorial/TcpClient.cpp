#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      std::cout << "Usage: client <host>" << std::endl;
      return 0;
   }

   boost::asio::io_context io;

   tcp::resolver resolver(io);
   tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

   tcp::socket socket(io);
   boost::asio::connect(socket, endpoints);

   try
   {
      for (;;)
      {
         std::array<char, 128> msg;

         boost::system::error_code error;
         size_t len = socket.read_some(boost::asio::buffer(msg), error);
         if (error == boost::asio::error::eof)
         {
            break;
         }
         else if (error)
         {
            throw boost::system::system_error(error);
         }

         std::cout.write(msg.data(), len);
      }
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}
