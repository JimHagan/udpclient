#include <iostream>
#include "udpclient.hpp"

int main(int argc, char** argv)
{
	if (argc < 4) {
	    std::cout << "Usage: udpclient [dest host] [dest port] [payload]\n";
            std::cout << "Example: udpclient \"my.metrics.host.com\" 8094 \"boost.udp.test,host=testhost count=1\"\n";
            return 1;
	}

        char *dest_host = argv[1];
        char *dest_port = argv[2];
        char *payload = argv[3];


	boost::asio::io_service io_service;
	UDPClient client(io_service, dest_host/*"influxdbc1n1.dev.bo1.csnzoo.com"*/, dest_port /*"8094"*/);

	client.send(payload);
        return 0;
}
