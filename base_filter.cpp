#include "base_filter.h"
#include <QTableWidget>

base_filter::base_filter(std::string name, std::string short_name)
{
    this->name = name;
    this->short_name = short_name;
}

std::string base_filter::get_name()
{
    return name;
}

std::string base_filter::get_short_name()
{
    return short_name;
}
