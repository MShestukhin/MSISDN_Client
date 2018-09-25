#include "logger.h"

logger::logger()
{
}

void logger::init(std::string path_log){
    path=path_log+"/";
}

std::string logger::currentDateTime(std::string format) {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), format.c_str(), &tstruct);
    return buf;
}
void logger::info(std::string s){
    msg(s,"INFO");
}
void logger::warning(std::string s){
    msg(s,"WARNING");
}
void logger::error(std::string s){
    msg(s,"WARNING");
}

void logger::msg(std::string s, std::string inf_level){
    std::string file_name=path+currentDateTime("%d.%m.%Y")+".log";
    std::ofstream ifs(file_name.c_str(), std::ios_base::in | std::ios_base::app);
     if (ifs.is_open())
     {
         ifs <<currentDateTime("%d.%m.%Y %H:%M:%S")<<"\t"+inf_level+"\t"<< s+"\n";
         ifs.close();
     }
     else
         std::cout << "Error opening file\n";
}



