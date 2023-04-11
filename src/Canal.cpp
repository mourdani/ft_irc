//
// Created by d420d4 on 11/04/23.
//
#include "Canal.hpp"

Canal::Canal() {

}

Canal::Canal(std::string name) {
    _name = name;
}

Canal::Canal(const Canal &canal) {
    *this = canal;
}

Canal::~Canal() {

}

Canal &Canal::operator=(const Canal &canal) {
    _name = canal._name;
    _users = canal._users;

    return *this;
}
