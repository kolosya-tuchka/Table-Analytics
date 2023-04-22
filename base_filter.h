#ifndef BASE_FILTER_H
#define BASE_FILTER_H

#include <QTableWidget>

class base_filter
{
public:
    base_filter(std::string name, std::string short_name);
    virtual bool filter(std::string text) const = 0;
    bool enabled = true;

    std::string get_name();
    std::string get_short_name();
protected:
    std::string name = "filter";
    std::string short_name = "=";
};

#endif // BASE_FILTER_H
