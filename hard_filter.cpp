#include "hard_filter.h"

hard_filter::hard_filter(std::string target_text, std::string name, std::string short_name) : base_filter(name, short_name) {
    this->target_text = target_text;
}

bool hard_filter::filter(std::string text) const {
  return target_text == text;
}
