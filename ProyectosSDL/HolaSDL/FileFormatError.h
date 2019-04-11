#pragma once
#include "ArkanoidError.h"

class FileFormatError final : public ArkanoidError {
 public:
  explicit FileFormatError(const string &m)
      : ArkanoidError("[File Format]: " + m) {}
};
