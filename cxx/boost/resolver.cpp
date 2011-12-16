#include <boost/asio.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>


int main()
{
    boost::asio::mutable_buffer buffer(malloc(1024), 1024);
    boost::system::error_code  ec;
    boost::asio::io_service  ioServer;
    boost::asio::io_service::work IO_work(ioServer);
    ioServer.run();

    boost::asio::ip::tcp::resolver resolver(ioServer);

    boost::asio::ip::tcp::socket  socket(ioServer);
    socket.connect(*resolver.resolve(boost::asio::ip::tcp::resolver::query("www.baidu.com", "http")));
    printf("connecting success\n");
    socket.read_some(buffer, ec);
    if (!ec)
    {
        printf("error happend\n");
        return 1;
    }
    char* p1 = boost::asio::buffer_cast<char*>(buffer);
    std::cout << p1 << std::endl;
    return 0;
}
