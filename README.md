# udpclient

*A Simple UDP Client Written in C++ (using Boost)*

*TODO:* Support comma separated list of hosts/ips and randomly choose destination

Usage: `udpclient [dest host or IP] [dest port] [payload]`

Example: `udpclient "my.metrics.host.com" 8094 "boost.udp.test,host=testhost count=1"`

Many useful packages use UDP as a means of receiving input form distributed sources. Such packages include: Logstash, InfluxDB, Telegraf, and various statsd clients.  Some of the main benefits of UDP for certain distributed data applilcations are:

- There is no need to maintain connection state in the end systems(ie no need for send and receive buffers,congestion control parameters and sequence and acknowledgement number parameters)..hence more active clients could be supported

- Small packet header overhead for udp(only 8 bytes) where as tcp has 20 bytes of header

#Testing

This repo also comes with a trival udpsersver.  It will be automatically built by make.sh.  To run simple use the commmand `udpserver [port]`.  By running this on the same host you are testing the client you can go through the following sequence...

```
$ udpserver 8094 &
$ Listening on port 8094
$ udpclient localhost 8094 "TEST"
$ Received: TEST
```
