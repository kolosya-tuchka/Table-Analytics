#include "regex_filter.h"
#include <regex>

regex_filter::regex_filter(std::regex regex, std::string name, std::string short_name) : base_filter(name, short_name) {
    this->regex = regex;
}

bool regex_filter::filter(std::string text) const
{
  return std::regex_match(text, regex);
}
