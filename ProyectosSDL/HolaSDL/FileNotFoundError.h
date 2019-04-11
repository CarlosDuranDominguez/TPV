#pragma once

#include "ArkanoidError.h"

class FileNotFoundError : public ArkanoidError {
 public:
  FileNotFoundError(const string &name)
      : ArkanoidError("[File Not Found]: " + name) {}
};
