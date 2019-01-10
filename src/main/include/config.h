#pragma once

#include <string>


template <typename T>
struct ParameterKey {
    std::string key;
    T value;
};

const ParameterKey<double> MAGIC_KEY_NAME = {"path/to/key", 2.5};