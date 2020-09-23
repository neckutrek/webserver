#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class AsyncCountdownTimer
{
public:
   AsyncCountdownTimer(boost::asio::io_context& io, int counter_start)
    : m_timer(io, boost::posix_time::seconds(1)),
      m_counter(counter_start)
   {
      m_fun = [this](const boost::system::error_code&)
         {
            if (m_counter > 0)
            {
               std::cout << m_counter-- << std::endl;
               m_timer.expires_at(m_timer.expires_at() + boost::posix_time::seconds(1));
               m_timer.async_wait(m_fun);
            }
         }; 
      m_timer.async_wait(m_fun);
   }

private:
   boost::asio::deadline_timer  m_timer;
   int                          m_counter;
   std::function<void(const boost::system::error_code&)>
                                m_fun;
};

int main(int argc, char* argv[])
{
   boost::asio::io_context io;
   AsyncCountdownTimer timer1(io, 5);
   AsyncCountdownTimer timer2(io, 6);

   std::thread th([&io](){io.run();});  
   io.run();
   th.join();
   return 0;
}
