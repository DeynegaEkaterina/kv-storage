// Copyright 2020 Your Name <your_email>

#ifndef SUGGESTION_ELEMENT_HPP_
#define SUGGESTION_ELEMENT_HPP_

#include <string>
struct Element{
  Element() = default;

  Element(std::string key, std::string value, std::string family_name){
    _key = key;
    _value = value;
    _family_name = family_name;
  }

  std::string _key;
  std::string _value;
  std::string _family_name;
};
#endif  // SUGGESTION_ELEMENT_HPP_
