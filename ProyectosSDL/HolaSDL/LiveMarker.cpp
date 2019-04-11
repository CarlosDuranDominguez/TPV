#include "LiveMarker.h"
#include "Game.h"

// Constructor
LiveMarker::LiveMarker(const float32 x, const float32 y, const float32 width,
                       const float32 height, Texture *texture)
    : GameObject(x, y, width, height), Renderable(texture) {}

// Defines the render behaviour
void LiveMarker::render() const {
  SDL_Rect rect{int(position_.x), int(position_.y), texture_->getW(),
                texture_->getH()};
  const auto lives = Game::getGameManager()->getLives();
  for (auto i = 0; i < lives; i++) {
    rect.x = int(position_.x) + i * texture_->getW();
    texture_->render(rect);
  }
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &LiveMarker::deserialize(std::istream &out) { return out; }

// Defines the serialize method behaviour to save the data into a file save
std::ostream &LiveMarker::serialize(std::ostream &is) const { return is; }
