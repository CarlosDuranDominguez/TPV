#include "ScoreBoardState.h"

ScoreBoardState::ScoreBoardState(Game* game) {
	SDL_Color white = { 255,255,255,255 };
	SDL_Color grey = { 80,80,80,255 };
	scoreboard = new ScoreBoard(game->getFonts()[0], 0, 0, 200, 300, white, "../save/save.save");
	button = new Button(game->getFonts()[0], 0, 400, 200, 100, white, grey, "Exit", []() {
	});
}

ScoreBoardState::~ScoreBoardState() {
	delete scoreboard;
	delete button;
}

void ScoreBoardState::run() {
	while (!exit) {
		handleEvents();
		render();
	}
}

void ScoreBoardState::render() {
	scoreboard->render();
	button->render();
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