#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <iostream>

EM_ASYNC_JS(emscripten::EM_VAL, take_input, (), {
    const input = await getInput();
    return Emval.toHandle(input);
});

#include "main.cc"

EMSCRIPTEN_BINDINGS(straights_bindings) {
    emscripten::function("gameLoop", &gameLoop);
}
