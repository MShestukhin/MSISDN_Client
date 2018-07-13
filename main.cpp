// Version:1.0 Date:12.07.2018 #
// Author: Shestukhin Maxim
// Email: shestukhin@svyazcom.ru
#include <iostream>
#include <boost/asio.hpp>
#include "dnsclient.h"
//#include <ocilib.h>
#include <vector>
#include <map>
#include <time.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include "includes/libconfig.h++"
#include "includes/occi.h"
#include "includes/ocilib.h"
#define SIZE_ARRAY 100
#define NB_LOAD    10
#define SIZE_COL1  20
#define SIZE_COL2  30
#define SIZE_COL3  8
#define NUM_COLS   3
#define ARRAY_SIZE 1
#define STRING_SIZE 20

//namespace logging = boost::log;
//namespace sinks = boost::log::sinks;
//namespace src = boost::log::sources;
//namespace expr = boost::log::expressions;
//namespace attrs = boost::log::attributes;
//namespace keywords = boost::log::keywords;
//using namespace logging::trivial;
//src::severity_logger< severity_level > lg;
using namespace std;
boost::mutex _lock;
std::vector<std::string> *all_to_send;
std::vector<std::string> *all_to_insert;
char file_id[100];
int iter;
int flag;
struct db
{
    string host;
    string user;
    string password;
    db(string h,
       string usr,
       string pswd){
        host=h;
        user=usr;
        password=pswd;
    }
};

db* Db;
int to_int(string str)
{
    return atoi(str.c_str());
}

vector<string> split(string str,char delimitr)
{
    vector<string> mass;
    int pos=0;
    if(str.find(delimitr)!=pos!=string::npos)
        while(pos!=string::npos)
        {
            pos=str.find(delimitr);
            mass.push_back(str.substr(0,pos));
            str.erase(0,pos+1);
        }
    else
        mass.push_back(str);
    return mass;
}

void mnp_thread()
{
    //BOOST_LOG_SEV(lg, info) << "MNP run "<<iter<<"\n";
    boost::asio::io_service* io_service=new boost::asio::io_service;
    if(all_to_send->size()==0)
        flag=1;
    DnsClient client(*io_service, *all_to_send, *all_to_insert);
    client.MNP_start_timer();
    io_service->run();
}


void db_thread()
{
    std::vector<std::string> v;
    OCI_Connection* cn1;
    OCI_Statement* st1;
    OCI_Error      *err;
    OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT);
    cn1 = OCI_ConnectionCreate(Db->host.c_str(), Db->user.c_str(), Db->password.c_str(), OCI_SESSION_DEFAULT);
    st1 = OCI_StatementCreate(cn1);
    _lock.lock();
    std::cout<<all_to_insert->size()<<"\n";
    if(all_to_insert->size()>0)
    {
        v.assign(all_to_insert->begin(),all_to_insert->end());
        all_to_insert->clear();
        _lock.unlock();
        int n=v.size();
        int tab_int[n];
        char tab_str[n][100+1];
        int tab_res[n];
        char tab_err[n][100+1];
        OCI_Prepare(st1, "begin ftp.set_rec_error(:file_id,:msisdn,:res,:err); end;");
        OCI_BindArraySetSize(st1, n);
        OCI_BindArrayOfInts(st1, ":file_id", (int*)tab_int, 0);
        OCI_BindArrayOfStrings(st1, ":msisdn", (char*)tab_str, 100, 0);
        OCI_BindArrayOfInts(st1, ":res", (int*)tab_res, 0);
        OCI_BindArrayOfStrings(st1, ":err", (char*)tab_err, 100, 0);
        std::cout<<n<<"\n";
        for(int i=0;i<n;i++)
        {
            std::string str=std::string(file_id)+v.at(i);
            vector<string> data=split(str,',');
            tab_int[i]=to_int(data.at(0));
            sprintf(tab_str[i],data.at(1).c_str());
            tab_res[i]=to_int(data.at(2));
            sprintf(tab_err[i],data.at(3).c_str());
        }
        v.clear();
        if (!OCI_Execute(st1))
        {
            //BOOST_LOG_SEV(lg, error) <<"Number of DML array errors : "<<OCI_GetBatchErrorCount(st1);
            err = OCI_GetBatchError(st1);
            while (err)
            {
                //BOOST_LOG_SEV(lg, error) <<"Error at row "<< OCI_ErrorGetRow(err)<< " : "<<OCI_ErrorGetString(err);
                err = OCI_GetBatchError(st1);
                flag=2;
            }
        }
    }
    else
        _lock.unlock();
    //BOOST_LOG_SEV(lg, info) <<"row inserted : "<<OCI_GetAffectedRows(st1);
    OCI_Commit(cn1);
    OCI_StatementFree(st1);
    OCI_ConnectionFree(cn1);
}

void init()
{
    libconfig::Config conf;
    try{
        conf.readFile("/home/bic/bic-ftp/etc/MSISDN_Client.conf");
    }
    catch(libconfig::ParseException e){
        //BOOST_LOG_SEV(lg, fatal) << e.getError() << " line:" << e.getLine() << std::endl;
    }
    Db=new db(conf.lookup("MNP.Db.host"),
    conf.lookup("MNP.Db.user"),
    conf.lookup("MNP.Db.pswd"));
    std::string log_path_str= conf.lookup("MNP.log_path");
//    logging::add_file_log
//    (
//        keywords::file_name =log_path_str+ "/%Y-%m-%d.log",
//                keywords::auto_flush = true ,
//        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
//        keywords::format =
//        (
//            expr::stream
//            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
//            << "\t: <" << logging::trivial::severity
//            << "> \t" << expr::smessage
//        )
//    );
}

void err_handler(OCI_Error *err)
{
    printf("%s\n", OCI_ErrorGetString(err));
}

int main()
{
    flag=0;
    OCI_Connection* cn;
    OCI_Statement* st;
    OCI_Resultset*rs;
    init();
    //BOOST_LOG_SEV(lg, info) << "Run MNP module;";
    all_to_insert=new std::vector<std::string>;
    all_to_send=new std::vector<std::string>;
    if(!OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT)){
        return EXIT_FAILURE;
    }
    cn = OCI_ConnectionCreate(Db->host.c_str(), Db->user.c_str(), Db->password.c_str(), OCI_SESSION_DEFAULT);
//    BOOST_LOG_SEV(lg, info) <<"Server major    version : "<< OCI_GetServerMajorVersion(cn);
//    BOOST_LOG_SEV(lg, info) <<"Server minor    version : "<< OCI_GetServerMinorVersion(cn);
//    BOOST_LOG_SEV(lg, info) <<"Server revision version : "<< OCI_GetServerRevisionVersion(cn);
//    BOOST_LOG_SEV(lg, info) <<"Connection      version : "<< OCI_GetVersionConnection(cn);
    st = OCI_StatementCreate(cn);
    OCI_Prepare(st,"select * from FTP_ES_MSISDN");
    OCI_Execute(st);
    rs = OCI_GetResultset(st);
    while(OCI_FetchNext(rs))
    {
        sprintf(file_id,OCI_GetString(rs,1));
        char str[100];
        sprintf(str,OCI_GetString(rs,2));
        all_to_send->push_back(str);
        if((all_to_send->size()%4000)==0)
        {
            boost::thread thread(&mnp_thread);
            boost::thread thread1(&db_thread);
            thread.join();
            thread1.join();
            if(flag!=0){
                return flag;
            }
        }
    }
    if(all_to_send->size()>0){
        boost::thread thread(&mnp_thread);
        boost::thread thread1(&db_thread);
        thread1.join();
        thread.join();
    }
    //BOOST_LOG_SEV(lg, info) << "Work with database is complete;";
    OCI_Cleanup();
    all_to_insert->clear();
    all_to_send->clear();
    return 0;
}
