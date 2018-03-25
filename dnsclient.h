#ifndef DNSCLIENT_H
#define DNSCLIENT_H
#include <boost/asio.hpp>
#include "dnsstructs.h"
class DnsClient
{

private:
    char sendBuf[512], recvBuf[512], *qname;
    int bufSize,iter;
    boost::asio::io_service* io_serviceLocal;
    boost::asio::deadline_timer* timer;
    boost::asio::ip::udp::endpoint* endpoint;
    boost::asio::ip::udp::socket* socket;
public:
    DnsClient(boost::asio::io_service &io_service);
    void MNP_start_timer();
    void MNP_timer_handler(const boost::system::error_code& e);
    void MNP_send_handler(const boost::system::error_code& e);
    void MNP_recive_nandler(const boost::system::error_code& e);
    void MSISDN_Conversion_by_send(char* MSISDN);
    void ChangetoDnsNameFormat(char *dns, char *host);
    char* ReadName(char* reader,char* buffer,int* count);
};

#endif // DNSCLIENT_H
