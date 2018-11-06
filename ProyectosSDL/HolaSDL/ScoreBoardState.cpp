#include "ScoreBoardState.h"
#include "Game.h"

ScoreBoardState::ScoreBoardState(Game* game, SDL_Renderer* renderer): game(game), renderer(renderer) {
	scoreboard = new ScoreBoard(game->getFonts()[0], 0, 0, 200, 40, WHITE, "../saves/save.save");
	button = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY, "Exit", [this,game]() {
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
		if (event.type == SDL_QUIT) {
			exit = true;
			game->changeState("gameover");
		} else {
			button->handleEvents(event);
		}
	}
}