#include <iostream>
#include <boost/asio.hpp>
#include "dnsclient.h"

using namespace std;

int main()
{

    cout << "Hello World!" << endl;
    boost::asio::io_service* io_service=new boost::asio::io_service;
    DnsClient client(*io_service);
    client.MNP_start_timer();
    io_service->run();
    return 0;
}
