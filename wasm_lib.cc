#define WASM
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <sstream>
#include <string>
#include <iostream>

EM_ASYNC_JS(emscripten::EM_VAL, take_input, (), {
    const input = await getInput();
    return Emval.toHandle(input);
});

template<typename T>
T inputTaker(std::function<bool(T const&)> pred, std::string const& error_msg) {
    while(true) {
        auto js_input = emscripten::val::take_ownership(take_input());
        std::istringstream iss(js_input.as<std::string>());
        T input;
        iss >> input;
        bool fail = iss.fail() || !pred(input);
        if(fail) std::cerr << error_msg << std::endl;
        else return input;
    }
    // Unreachable
}

#include "main.cc"

EMSCRIPTEN_BINDINGS(straights_bindings) {
    emscripten::function("gameLoop", &gameLoop);
}
