#include "soft_filter.h"

soft_filter::soft_filter(std::string target_text, std::string name, std::string short_name) : base_filter(name, short_name) {
    this->target_text = target_text;
}

bool soft_filter::filter(std::string text) const
{
  return text.find(target_text) != std::string::npos;
}
