//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class udp_server
{
public:
  udp_server(boost::asio::io_service& io_service, int port)
    : socket_(io_service, udp::endpoint(udp::v4(), port))
  {
    std::cout << "Listening on port " << port << std::endl;
    start_receive();
  }

private:
  void start_receive()
  {
     socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), remote_endpoint_,
        boost::bind(&udp_server::handle_receive, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
      std::cout << "Bytes received: " << boost::asio::placeholders::bytes_transferred << std::endl;
      std::cout << "Received: " << std::string(reinterpret_cast<const char*>(recv_buffer_.data())) << std::endl;
      

  }

  void handle_receive(const boost::system::error_code& error,
      std::size_t bytes_transferred)
  {

    if (!error || error == boost::asio::error::message_size)
    {
      start_receive();
    }
  }


  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 1000> recv_buffer_;
};

int main(int argc, char** argv)
{

  if (argc < 2) {
    std::cout << "Usage: udpserver [listen port]\n";
    std::cout << "Example: udpserver 8094\n";
    return 1;
  }


  unsigned int port = atoi(argv[1]);
  setvbuf(stdout, NULL, _IONBF, 0);
  try
  { 
    boost::asio::io_service io_service;
    udp_server server(io_service, port);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
