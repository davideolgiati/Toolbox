// Copyright 2018 Davide Olgiati

#include "functions.h"

bool functions::set(std::string id, function function) {
    bool okay = true;
    try {
        _functions[id] = function;
    } catch(...) {
        okay = false;
    }
    return okay;
}

function functions::get(std::string id) {
    return _functions[id];
}

bool functions::parse(std::string input) {
    return std::regex_match(input, this->function_structure_regex);
}