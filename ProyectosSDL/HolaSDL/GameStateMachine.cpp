#include "GameStateMachine.h"
#include "State.h"

GameStateMachine::GameStateMachine() = default;

GameStateMachine::~GameStateMachine() {
  while (!stack_.empty()) {
    delete stack_.top();
    stack_.pop();
  }
}

State* GameStateMachine::currentState() const {
  return stack_.empty() ? nullptr : stack_.top();
}

void GameStateMachine::pushState(State* state) { stack_.push(state); }

void GameStateMachine::changeState(State* state) {
  popState();
  pushState(state);
}

void GameStateMachine::popState() {
  if (!stack_.empty()) {
    delete stack_.top();
    stack_.pop();
  }
}

bool GameStateMachine::empty() const { return stack_.empty(); }
