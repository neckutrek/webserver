#include <iostream>
#include <ctime>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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
class TcpConnection
{
public:
   using Pointer = std::shared_ptr<TcpConnection>;

   static Pointer create(boost::asio::io_context& io)
   {
      return Pointer(new TcpConnection(io));
   }

   tcp::socket& socket()
   {
      return m_socket;
   }

   void sendMessage(const std::string& message)
   {
      boost::asio::async_write(
         m_socket,
         boost::asio::buffer(message),
         [](const boost::system::error_code& error, size_t bytes_written){
            // do nothing
         });
   }

private:
   TcpConnection(boost::asio::io_context& io)
      : m_socket(io)
   {}

   tcp::socket                m_socket;
   std::string                m_message;
};

/**
 *
 */
int main(int argc, char* argv[])
{
   try
   {
      boost::asio::io_context io;

      tcp::endpoint endpoint(tcp::v4(), 13);
      tcp::acceptor acceptor(io, endpoint);

      for (;;)
      {
         auto conn = TcpConnection::create(io);
         acceptor.accept(conn->socket());

         conn->sendMessage(getDateTime());
      }
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}

