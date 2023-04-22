#ifndef SOFT_FILTER_CREATOR_H
#define SOFT_FILTER_CREATOR_H

#include "base_filter_creator.h"
#include "soft_filter.h"

class soft_filter_creator : public base_filter_creator
{
public:
    soft_filter_creator(QWidget* parent) : base_filter_creator(parent){}

    virtual base_filter* create_filter() override;
    virtual base_filter_view* get_view() override;
    soft_filter_creator* set_target_string();
    virtual base_filter_creator * set_data(QString data) override;
    virtual base_filter * get_filter() override;
private:
    std::string target_string = "example";
};
#endif // SOFT_FILTER_CREATOR_H
