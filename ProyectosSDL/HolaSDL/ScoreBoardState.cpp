#include "ScoreBoardState.h"
#include "Game.h"

ScoreBoardState::ScoreBoardState(Game* game, SDL_Renderer* renderer): game(game), renderer(renderer) {
	SDL_Color white = { 255,255,255,255 };
	SDL_Color grey = { 80,80,80,255 };
	scoreboard = new ScoreBoard(game->getFonts()[0], 0, 0, 200, 300, white, "../saves/save.save");
	button = new Button(game->getFonts()[0], 0, 400, 200, 100, white, grey, "Exit", [this,game]() {
		exit = true; game->changeState("menu");
	});
}

ScoreBoardState::~ScoreBoardState() {
	delete scoreboard;
	delete button;
}

void ScoreBoardState::run() {
	exit = false;
	while (!exit) {
		handleEvents();
		render();
	}
}

void ScoreBoardState::render() {
	SDL_RenderClear(renderer);
	scoreboard->render();
	button->render();
	SDL_RenderPresent(renderer);
}

void ScoreBoardState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else {
			button->handleEvents(event);
		}
	}
}