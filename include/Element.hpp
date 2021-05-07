// Copyright 2021 Deynega Ekaterina

#ifndef INCLUDE_ELEMENT_HPP_
#define INCLUDE_ELEMENT_HPP_

#include <string>

/**
 * @namespace std
 * @struct Element
 * @brief
 * This class describes database's element structure. Elements consist of
 * key-value pairs. This pairs are grouped in columns.
 */

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
#endif  // INCLUDE_ELEMENT_HPP_
