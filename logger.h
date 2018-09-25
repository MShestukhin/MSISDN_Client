#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <iostream>
class logger
{
public:
    logger();
    std::string currentDateTime(std::string format);
    std::string path;
    void init(std::string path_log);
    void info(std::string s);
    void warning(std::string s);
    void error(std::string s);
    void msg(std::string s,std::string inf_level);
};

#endif // LOGGER_H
