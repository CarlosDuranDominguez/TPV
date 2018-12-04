#pragma once

#include "ArkanoidError.h"
#include <SDL.h>


class FileFormatError : public ArkanoidError {
public:
    FileFormatError(const string& m) : ArkanoidError("[File Format]: " + m) {}
};