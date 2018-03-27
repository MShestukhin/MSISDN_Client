#include <iostream>
#include <boost/asio.hpp>
#include "dnsclient.h"
#include <ocilib.h>
#include <vector>
#include <map>
#include <time.h>
using namespace std;

int main()
{
    std::vector<std::string> *all_to_send=new std::vector<std::string>;
    /*OCI_Connection* cn;
    OCI_Statement* st;
    OCI_Resultset*rs;
    OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT);
    cn = OCI_ConnectionCreate("sk", "svcbic", "m83hose55tcp", OCI_SESSION_DEFAULT);
    printf("Server major    version : %i\n", OCI_GetServerMajorVersion(cn));
    printf("Server minor    version : %i\n", OCI_GetServerMinorVersion(cn));
    printf("Server revision version : %i\n\n", OCI_GetServerRevisionVersion(cn));
    printf("Connection      version : %i\n\n", OCI_GetVersionConnection(cn));
    st = OCI_StatementCreate(cn);
    OCI_Prepare(st,"select * from ES_MSISDN");
    OCI_Execute(st);
    rs = OCI_GetResultset(st);*/
    int i=0;
    while(i<4000){
    //OCI_FetchNext(rs);
    char str[100];
    sprintf(str,"79834077832");
    all_to_send->push_back(str);
    i++;
    }
    boost::asio::io_service* io_service=new boost::asio::io_service;
    DnsClient client(*io_service, *all_to_send);
    unsigned int start_time=clock();
    client.MNP_start_timer();
    io_service->run();
    unsigned int stop_time=clock();
    printf("\i%f", stop_time-start_time);
    return 0;
}
