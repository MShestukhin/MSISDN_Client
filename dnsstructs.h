#ifndef DNSSTRUCTS_H
#define DNSSTRUCTS_H
#include <iostream>

struct DNS_HEADER
{
    unsigned short id; // identification number

    char rd :1; // recursion desired
    char tc :1; // truncated message
    char aa :1; // authoritive answer
    char opcode :4; // purpose of message
    char qr :1; // query/response flag

    char rcode :4; // response code
    char ad :1; // authenticated data
    //char z :1; // its z! reserved

    short q_count; // number of question entries
    short ans_count; // number of answer entries
    short auth_count; // number of authority entries
    short add_count; // number of resource entries
};
struct QUESTION
{
    short qtype;
    short qclass;
};
struct R_DATA
{
    unsigned short type;
    unsigned short _class;
    unsigned int ttl;
    unsigned short data_len;
    unsigned short other;
    unsigned short pref;
    unsigned short flagLen;
    unsigned char flag;
    unsigned short servLen;
    unsigned char serv;
    unsigned short regLen;
    unsigned char reg;
};
//Pointers to resource record contents
struct RES_RECORD
{
    char *name;
    struct R_DATA *resource;
    char *rdata;
    RES_RECORD(){
        name=0;
        resource=0;
        rdata=0;
    }
    ~RES_RECORD(){

    }
};


#endif // DNSSTRUCTS_H
