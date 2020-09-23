add_executable(TcpClient TcpClient.cpp)
target_include_directories(TcpClient PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(TcpClient ${PROJECT_LINK_LIBRARIES})

add_executable(AsyncTcpServer AsyncTcpServer.cpp)
target_include_directories(AsyncTcpServer PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(AsyncTcpServer ${PROJECT_LINK_LIBRARIES})

add_executable(AsyncCountdownTimer AsyncCountdownTimer.cpp)
target_include_directories(AsyncCountdownTimer PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(AsyncCountdownTimer ${PROJECT_LINK_LIBRARIES})

add_executable(UdpClient UdpClient.cpp)
target_include_directories(UdpClient PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(UdpClient ${PROJECT_LINK_LIBRARIES})

add_executable(AsyncUdpServer AsyncUdpServer.cpp)
target_include_directories(AsyncUdpServer PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(AsyncUdpServer ${PROJECT_LINK_LIBRARIES})


