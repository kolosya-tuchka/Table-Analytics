#include "regex_filter_creator.h"
#include <QInputDialog>
#include "codec.h"
#include <QErrorMessage>
#include "filter_exception.h"

base_filter* regex_filter_creator::create_filter()
{
    set_regex();
    return !success ? nullptr : new regex_filter(regex, name, short_name);
}

base_filter_view *regex_filter_creator::get_view()
{
    return new base_filter_view(parent, nullptr, target_string);
}

regex_filter_creator *regex_filter_creator::set_regex()
{
    try {
        target_string = QInputDialog::getText(parent, codec::get_codec()->toUnicode("Ввод строки"), codec::get_codec()->toUnicode("Введите строку для фильтра"), QLineEdit::Normal, "", &success).toStdString();
        this->regex = std::regex(target_string);
    }
    catch(std::regex_error e) {
        throw new filter_exception("regex \"" + target_string + "\" is incorrect!");
    }
    return this;
}

base_filter_creator *regex_filter_creator::set_data(QString data)
{
  try {
        target_string = data.toStdString();
        this->regex = std::regex(target_string);
  }
  catch(std::regex_error e) {
      throw new filter_exception("regex \"" + target_string + "\" is incorrect!");
  }
}

base_filter *regex_filter_creator::get_filter()
{
  return new regex_filter(regex, name, short_name);
}
