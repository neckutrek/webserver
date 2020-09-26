# add_subdirectory("./boost_tutorial")

set(SOURCES
   tcp_connection.cpp
   tcp_connection_manager.cpp
   main.cpp
   server.cpp)

add_executable(webserver ${SOURCES})
target_include_directories(webserver PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(webserver ${PROJECT_LINK_LIBRARIES})

