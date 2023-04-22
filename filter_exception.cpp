#include "filter_exception.h"

filter_exception::filter_exception(std::string msg) {
    this->msg = msg;
}

std::string filter_exception::what()
{
    return msg;
}
