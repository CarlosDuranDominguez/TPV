#pragma once

/*
 *Updatable interface
 */
class Updatable {
 public:
  Updatable();
  virtual ~Updatable();
  virtual void update() = 0;
};

inline Updatable::Updatable() {}

inline Updatable::~Updatable() {}
