#ifndef HARD_FILTER_H
#define HARD_FILTER_H

#include "base_filter.h"

class hard_filter : public base_filter
{
public:
    hard_filter(std::string target_text, std::string name = "filter", std::string short_name = "=");
    virtual bool filter(std::string text) const override;
protected:
    std::string target_text;
};

#endif // HARD_FILTER_H
