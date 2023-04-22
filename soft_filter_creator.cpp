#include "soft_filter_creator.h"
#include <QInputDialog>
#include "codec.h"

base_filter* soft_filter_creator::create_filter()
{
    set_target_string();
    return !success ? nullptr : new soft_filter(target_string, name, short_name);
}

base_filter_view *soft_filter_creator::get_view()
{
    return new base_filter_view(parent, nullptr, target_string);
}

soft_filter_creator *soft_filter_creator::set_target_string()
{
    this->target_string = QInputDialog::getText(parent, codec::get_codec()->toUnicode("Ввод строки"), codec::get_codec()->toUnicode("Введите строку для фильтра"), QLineEdit::Normal, "", &success).toStdString();
    return this;
}

base_filter_creator *soft_filter_creator::set_data(QString data)
{
    target_string = data.toStdString();
    return this;
}

base_filter *soft_filter_creator::get_filter()
{
  return new soft_filter(target_string, name, short_name);
}
