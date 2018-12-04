#pragma once

#include "ArkanoidError.h"
#include <SDL.h>


class SDLError : public ArkanoidError {
public:
    SDLError(const string& m) : ArkanoidError("[SDL]: " + m) {}
};