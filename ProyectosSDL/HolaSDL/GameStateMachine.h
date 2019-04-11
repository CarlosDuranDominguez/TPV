#pragma once
#include <stack>

class State;

class GameStateMachine final {
  std::stack<State*> stack_;

 public:
  GameStateMachine();
  ~GameStateMachine();

  State* currentState() const;
  void pushState(State* state);
  void changeState(State* state);
  void popState();
  bool empty() const;
};
