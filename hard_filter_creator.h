#ifndef HARD_FILTER_CREATOR_H
#define HARD_FILTER_CREATOR_H

#include "base_filter_creator.h"
#include "base_filter_view.h"
#include "hard_filter.h"

class hard_filter_creator : public base_filter_creator
{
public:
    hard_filter_creator(QWidget* parent) : base_filter_creator(parent){}

    virtual base_filter* create_filter() override;
    virtual base_filter_view* get_view() override;
    hard_filter_creator* set_target_string();
    virtual base_filter_creator * set_data(QString data) override;
    virtual base_filter * get_filter() override;
private:
    std::string target_string = "example";
};

#endif // HARD_FILTER_CREATOR_H
