#pragma once

#include "ArkanoidError.h"

class FileFormatError : public ArkanoidError {
 public:
  FileFormatError(const string &m) : ArkanoidError("[File Format]: " + m) {}
};
