#ifndef REGEX_FILTER_CREATOR_H
#define REGEX_FILTER_CREATOR_H

#include "base_filter_creator.h"
#include "regex_filter.h"
#include <regex>

class regex_filter_creator : public base_filter_creator
{
public:
    regex_filter_creator(QWidget* parent) : base_filter_creator(parent){}

    virtual base_filter* create_filter() override;
    virtual base_filter_view* get_view() override;
    regex_filter_creator* set_regex();
    virtual base_filter_creator * set_data(QString data) override;
    virtual base_filter * get_filter() override;
private:
    std::regex regex = std::regex("example");
    std::string target_string = "example";
};

#endif // REGEX_FILTER_CREATOR_H
