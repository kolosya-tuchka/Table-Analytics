#include "base_filter_creator.h"
#include "codec.h"

base_filter_creator::base_filter_creator(QWidget* parent) {
    this->parent = parent;
}

base_filter_creator *base_filter_creator::set_short_name(std::string short_name)
{
    this->short_name = short_name;
    return this;
}

QAction *base_filter_creator::get_action()
{
    QAction* result = new QAction();
    result->setText(codec::get_codec()->toUnicode(short_name.c_str()));
    return result;
}

base_filter_creator *base_filter_creator::set_name(std::string name)
{
    this->name = name;
    return this;
}
