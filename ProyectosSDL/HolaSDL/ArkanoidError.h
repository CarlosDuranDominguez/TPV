#pragma once
#include <stdexcept>

class ArkanoidError : public std::logic_error {
 public:
  explicit ArkanoidError(const string &m)
      : std::logic_error("Arkanoid Error " + m) {}
};
