#pragma once
#include "ArkanoidError.h"

class FileNotFoundError final : public ArkanoidError {
 public:
  explicit FileNotFoundError(const string &name)
      : ArkanoidError("[File Not Found]: " + name) {}
};
