#include "Button.h"

Button::Button(Font* font, float32 x, float32 y, float32 width, float32 height,
               SDL_Color inColor, SDL_Color outColor, string text,
               function<void()> callback)
    : Text(font, x, y, width, height, outColor, text),
      inColor_(inColor),
      outColor_(outColor),
      callback_(callback) {}
Button::~Button() {}

/**
 * It detects if the cursor is on the button. If it is clicked the call the
 * callback function.
 */
void Button::handleEvents(SDL_Event event) {
  SDL_Point p;
  switch (event.type) {
    case SDL_MOUSEMOTION:

      p = {event.motion.x, event.motion.y};
      if (SDL_PointInRect(&p, &getRect())) {
        setColor(inColor_);
        mouseIn_ = true;
      } else {
        setColor(outColor_);
        mouseIn_ = false;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (mouseIn_ && event.button.button == SDL_BUTTON_LEFT) {
        callback_();
      }
      break;
    default:
      break;
  }
}
