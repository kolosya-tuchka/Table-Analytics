#ifndef BASE_FILTER_CREATOR_H
#define BASE_FILTER_CREATOR_H

#include "base_filter_view.h"
#include "base_filter.h"
#include <QtWidgets>

class base_filter_creator
{
public:
    base_filter_creator(QWidget* parent);
    virtual base_filter* create_filter() = 0;
    virtual base_filter_creator* set_data(QString data) = 0;
    base_filter_creator* set_name(std::string name);
    base_filter_creator* set_short_name(std::string short_name);
    virtual QAction* get_action();
    virtual base_filter_view* get_view() = 0;
    virtual base_filter* get_filter() = 0;
protected:
    bool success = true;
    QWidget* parent;
    std::string name = "filter";
    std::string short_name = "=";
};

#endif // BASE_FILTER_CREATOR_H
