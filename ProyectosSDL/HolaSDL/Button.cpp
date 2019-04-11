#include "Button.h"

Button::Button(Font* font, const float32 x, const float32 y,
               const float32 width, const float32 height,
               const SDL_Color inColor, const SDL_Color outColor,
               const string text, const function<void()>& callback)
    : Text(font, x, y, width, height, outColor, text),
      inColor_(inColor),
      outColor_(outColor),
      callback_(callback) {}

Button::~Button() = default;

/**
 * It detects if the cursor is on the button. If it is clicked the call the
 * callback function.
 */
void Button::handleEvents(const SDL_Event event) {
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
