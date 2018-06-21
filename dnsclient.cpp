#include "dnsclient.h"
#include <iostream>
#include <boost/bind.hpp>
#define T_NAPTR 35


DnsClient::DnsClient(boost::asio::io_service &io_service, std::vector<std::string> &MSISDN_FROM_BD, std::vector<std::string> &for_insert) : socket(io_service, {boost::asio::ip::udp::v4(),53})
{
    iter=0;
    msisdnBufSize=0;
    recvPac=0;
    sendPac=0;
    timeCounter=0;
    io_serviceLocal=(boost::asio::io_service*)&io_service;
    msisdnBufSize=MSISDN_FROM_BD.size();
    all_to_send=(std::vector<std::string>*)&MSISDN_FROM_BD;
    all_to_insert=(std::vector<std::string>*)&for_insert;
    endpoint=new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("10.241.30.170"), 53);
    timer=new boost::asio::deadline_timer(io_service);
    msisdnBufSize=all_to_send->size();
}

void DnsClient::MNP_start_timer()
{
    timer->expires_from_now(boost::posix_time::microseconds(100));
    timer->async_wait(boost::bind(&DnsClient::MNP_timer_handler,this,boost::asio::placeholders::error()));
}

void DnsClient::MNP_timer_handler(const boost::system::error_code& e)
{
    if(iter<all_to_send->size())
    {
    std::string str=all_to_send->at(iter);
    MSISDN_Conversion_by_send((char*)str.c_str());
    socket.async_send_to(boost::asio::buffer(sendBuf,bufSize),
                         *endpoint,boost::bind(&DnsClient::MNP_send_handler,
                                              this ,
                                              boost::asio::placeholders::error()));
    iter++;
    MNP_start_timer();
    }
    else
    {
        timer->expires_from_now(boost::posix_time::microseconds(150));
        timer->async_wait(boost::bind(&DnsClient::MNP_timer_loss_handler,this,boost::asio::placeholders::error()));
    }
}
void DnsClient::MNP_timer_loss_handler(const boost::system::error_code& e)
{
    if(msisdnBufSize==all_to_send->size())
    {
        iter=0;
        sendPac++;
        if(sendPac==4)
        {
            for(int i=0; i<all_to_send->size(); i++)
            {
                std::string insert_str=","+all_to_send->at(i)+",9, MNP check erro";
                all_to_insert->push_back(insert_str);
                all_to_send->erase(all_to_send->begin()+i);
            }
        }
    }
    else if(all_to_send->size()==0) io_serviceLocal->stop();
    else
    {
        sendPac=0;
        msisdnBufSize=all_to_send->size();
    }
    MNP_start_timer();
}

void DnsClient::MNP_send_handler(const boost::system::error_code &e)
{
    if(!e)
    {
    socket.async_receive_from(boost::asio::buffer(recvBuf,512),*endpoint,
                              boost::bind(&DnsClient::MNP_recive_nandler,
                              this , boost::asio::placeholders::error()));
    }
    else{
        printf("Error to send");
        std::cerr<<e.message();
    }
}

void DnsClient::MNP_recive_nandler(const boost::system::error_code &e)
{
    recvPac++;
    struct DNS_HEADER* dns = (struct DNS_HEADER*) recvBuf;
    std::string errCode;
    struct RES_RECORD answers;
    int stop;
    char *reader = &recvBuf[sizeof(struct DNS_HEADER)];
    stop=0;
    answers.name=ReadName(reader,recvBuf,&stop);
    reader = reader + stop;
    answers.resource = (struct R_DATA*)(reader);
    reader = reader + sizeof(struct R_DATA);
    answers.rdata = ReadName(reader,recvBuf,&stop);
    reader = reader + stop;
    std::string query_response=answers.name;
    std::string query_msisdn;
    int pos=query_response.find("e164");
    while(pos>1){
        pos-=2;
        query_msisdn+=query_response.at(pos);
    }
     for(int i=0;i<all_to_send->size();i++)
     {
         std::string str=all_to_send->at(i);
         if(str==query_msisdn){
             if(ntohs(dns->rcode)!=0){
                 int n=ntohs(dns->rcode)/256;
                 switch (n) {
                 case 1:
                     errCode=",8,Query Format Error";
                         break;
                 case 2:
                     errCode=",8,Server failed to complete the DNS request";
                         break;
                 case 3:
                     errCode=",8,MSISDN does not exist";
                         break;
                 case 4:
                     errCode=",8,Function not implemented";
                     break;
                 case 5:
                     errCode=",8,The server refused to answer for the query";
                 default:
                     errCode=",9, MNP check erro";
                         break;
                 }
                 std::string insert_str=","+all_to_send->at(i)+errCode;
                 std::cout<<insert_str<<"\n";
                 all_to_insert->push_back(insert_str);
             }
             all_to_send->erase(all_to_send->begin()+i);
             break;
         }
     }
     //std::cout<<str.at(0)<<"\n";
     /*std::string regStr=answers.rdata;
     char* ident=answers.rdata+(strlen((char*)answers.rdata)-3);
     std::cout<<ident<<"\n";
     char* mtsIdent="01!";
     if((strcmp((char*)ident,mtsIdent))==0)
         mtsOr=false;
     else
         mtsOr=true;
     std::string::size_type n;
        for(int i=0;i<all_to_send->size();i++)
        {
            std::string str=all_to_send->at(i);
            n=regStr.find(str);
            if(n!=std::string::npos)
            {
                if(mtsOr)
                {
                    std::string insert_str=","+all_to_send->at(i)+",2, NULL";
                    //all_to_insert->push_back(insert_str);
                }
                else
                {
                    std::string insert_str=","+all_to_send->at(i)+",0, NULL";
                    //all_to_insert->push_back(insert_str);
                }
                all_to_send->erase(all_to_send->begin()+i);
                break;
            }
        }*/
     memset(recvBuf,0,512);
}

void DnsClient::MSISDN_Conversion_by_send(char *MSISDN)
{
    char* host;
    int i;
    int sizeNumber=strlen((char*)MSISDN);
    char str[2*sizeNumber];
    int index=1;
    str[0]=MSISDN[sizeNumber-1];
    i=1;
    while(i!=sizeNumber+1)
    {
        str[index]='.';
        str[index+1]=MSISDN[sizeNumber-i-1];
        index=index+2;
        i++;
    }
    host=(char*)&str;
    strcat(host,"e164.arpa\0");
    struct DNS_HEADER *dns = (struct DNS_HEADER *)&sendBuf;
    dns->id = (unsigned short) htons(getpid()+iter);
    dns->qr = 0; //This is a query
    dns->opcode = 0; //This is a standard query
    dns->aa = 0; //Not Authoritative
    dns->tc = 0; //This message is not truncated
    dns->rd = 1; //Recursion Desired
    dns->z = 0;
    dns->ad = 1;
    dns->rcode = 1;
    dns->q_count = htons(1); //we have only 1 question
    dns->ans_count = 0;
    dns->auth_count = 0;
    dns->add_count = 0;
    qname =(char*)&sendBuf[sizeof(struct DNS_HEADER)];
    ChangetoDnsNameFormat(qname , host);
    struct QUESTION* qinfo =(struct QUESTION*)&sendBuf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1)];
    qinfo->qtype = htons(T_NAPTR);
    qinfo->qclass = htons(1);
    bufSize=sizeof(struct DNS_HEADER)+(strlen((const char*)qname)+1)+sizeof(struct QUESTION);
    i=1;
}

void DnsClient::ChangetoDnsNameFormat(char *dns, char *host)
{
    int lock = 0 , i;
    std::strcat(host,".");
    for(i = 0 ; i < strlen((char*)host) ; i++)
    {
        if(host[i]=='.')
        {
            *dns++= i-lock;
            for(;lock<i;lock++)
                *dns++=host[lock];
            lock++;
        }
    }
    *dns++='\0';
}


char* DnsClient::ReadName(char* reader,char* buffer,int* count)
{
    char *name;
    int p=0,jumped=0;//,offset;
    *count = 1;
    name = (char*)malloc(256);
    name[0]='\0';
    //read the names in 3www6google3com format
    while(*reader!=0)
    {
        if(*reader>=192)
            jumped = 1; //we have jumped to another location so counting wont go up!
        else
            name[p++]=*reader;
        reader = reader+1;
        if(jumped==0)
            *count = *count + 1; //if we havent jumped to another location then we can count up
    }
    name[p]='\0'; //string complete
    if(jumped==1)
        *count = *count + 1; //number of steps we actually moved forward in the packet
        return name;
}
