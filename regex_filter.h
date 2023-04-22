#ifndef REGEX_FILTER_H
#define REGEX_FILTER_H

#include "base_filter.h"
#include <regex>

class regex_filter : public base_filter
{
public:
    regex_filter(std::regex regex, std::string name = "filter", std::string short_name = "=");
    virtual bool filter(std::string text) const override;
protected:
    std::regex regex;
};

#endif // REGEX_FILTER_H
