#pragma once
#include <string>
#include <functional>

#ifndef WASM

template<typename T>
T inputTaker(std::function<bool(T const&)> pred, std::string const& error_msg) {
    while(true) {
        T input{};
        std::cout << "> ";
        std::cin >> input;
        bool fail = std::cin.fail() || !pred(input);
        if(fail) {
            std::cin.clear();
            std::cout << error_msg << "\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>().max(), '\n');
        if(!fail) return input;
    }
    // Unreachable
};

#else

#include <sstream>
#include <emscripten/val.h>

__attribute__((import_name("__asyncjs__take_input"))) emscripten::EM_VAL take_input();

template<typename T>
T inputTaker(std::function<bool(T const&)> pred, std::string const& error_msg) {
    while(true) {
        auto js_input = emscripten::val::take_ownership(take_input());
        std::istringstream iss(js_input.as<std::string>());
        T input{};
        iss >> input;
        bool fail = iss.fail() || !pred(input);
        if(fail) std::cerr << error_msg << std::endl;
        else return input;
    }
    // Unreachable
};

#endif
