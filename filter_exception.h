#ifndef FILTER_EXCEPTION_H
#define FILTER_EXCEPTION_H

#include <exception>
#include <string>

class filter_exception : public std::exception
{
public:
    filter_exception(std::string msg = "");
    std::string what();
protected:
    std::string msg;
};

#endif // FILTER_EXCEPTION_H
