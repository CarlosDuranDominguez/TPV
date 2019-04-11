#include <time.h>
#include <iostream>
#include "Game.h"
#include "SDL.h"
#include "checkML.h"

using namespace std;

// The main method that runs the entire game
int main(int argc, char *argv[]) {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
                 _CRTDBG_LEAK_CHECK_DF);  // Check Memory Leaks
  srand((uint)time(NULL));
  try {
    Game *game = new Game();
    game->run();
    delete game;
    return 0;
  } catch (exception e) {
    cout << e.what();
    return -1;
  }
}
