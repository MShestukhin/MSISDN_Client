#include <iostream>
#include <boost/asio.hpp>
#include "dnsclient.h"
#include <ocilib.h>
#include <vector>
#include <map>
#include <time.h>
#include <boost/thread.hpp>
using namespace std;

std::vector<std::string> *all_to_send;
std::vector<std::string> *all_to_insert;
void thread_body(){
    boost::asio::io_service* io_service=new boost::asio::io_service;
    DnsClient client(*io_service, *all_to_send, *all_to_insert);
    unsigned int start_time=clock();
    while(1){
        if(all_to_send->size()>0) break;
    }
    client.MNP_start_timer();
    io_service->run();
    unsigned int stop_time=clock();
    //printf("\i%f", stop_time-start_time);
}

int main()
{
    all_to_insert=new std::vector<std::string>;
    boost::thread thread(&thread_body);
    thread.detach();
    all_to_send=new std::vector<std::string>;
    OCI_Connection* cn;
    OCI_Statement* st;
    OCI_Resultset*rs;
    OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT);
    cn = OCI_ConnectionCreate("sk", "svcbic", "m83hose55tcp", OCI_SESSION_DEFAULT);
    printf("Server major    version : %i\n", OCI_GetServerMajorVersion(cn));
    printf("Server minor    version : %i\n", OCI_GetServerMinorVersion(cn));
    printf("Server revision version : %i\n\n", OCI_GetServerRevisionVersion(cn));
    printf("Connection      version : %i\n\n", OCI_GetVersionConnection(cn));
    st = OCI_StatementCreate(cn);
    OCI_Prepare(st,"select * from FTP_ES_MSISDN");
    OCI_Execute(st);
    rs = OCI_GetResultset(st);
        while(OCI_FetchNext(rs)){
        char str[100];
        sprintf(str,OCI_GetString(rs,2));
        all_to_send->push_back(str);
        }
        char file_id[100];
        sprintf(file_id,OCI_GetString(rs,1));
        while(all_to_send->size()){
            if(all_to_insert->size()>0){
                for(int i=0;i<all_to_insert->size();i++){
                    std::string msisdn=all_to_insert->at(i);
                    all_to_insert->erase(all_to_insert->begin()+i);
                    std::string insert_str="begin ftp.set_rec_error("+std::string(file_id)+",'"+msisdn+"',9, 'MNP check error'); end;";
                    std::cout<<insert_str<<"\n";

                    OCI_Prepare(st,otext(insert_str.c_str()));
                    OCI_Execute(st);
                    rs = OCI_GetResultset(st);
                    std::cout<<rs;
                }
            }
        };
        OCI_Cleanup();
        std::cout<<file_id;
        std::cout<<all_to_send->size();
    return 0;
}
