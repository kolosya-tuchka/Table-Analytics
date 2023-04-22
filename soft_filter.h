#ifndef SOFT_FILTER_H
#define SOFT_FILTER_H

#include "base_filter.h"

class soft_filter : public base_filter
{
public:
    soft_filter(std::string target_text, std::string name = "filter", std::string short_name = "=");
    virtual bool filter(std::string text) const override;
protected:
    std::string target_text;
};

#endif // SOFT_FILTER_H
