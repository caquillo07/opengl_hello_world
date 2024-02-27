//
// Created by Hector Mejia on 2/26/24.
//

#ifndef OPENGL_HELLO_WORLD_PANIC_H
#define OPENGL_HELLO_WORLD_PANIC_H

#include <fmt/core.h>

static void panic(const char* message) {
    fmt::print("{}\n", message);
    exit(EXIT_FAILURE);
}

static void panicIf(bool condition, const char* message) {
    if (condition) {
        panic(message);
    }
}
#endif //OPENGL_HELLO_WORLD_PANIC_H
