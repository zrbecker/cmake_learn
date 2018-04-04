#ifndef GAME_SDL_APPLICATION_H
#define GAME_SDL_APPLICATION_H

#include <map>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "game_logic.h"

class SDLException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct Image {
  SDL_Surface* surface;
  SDL_Texture* texture;
};

class SDLApplication {
public:
  SDLApplication(GameLogic& game_logic);
  ~SDLApplication();

  void run();

  void draw_image(const std::string& image_name, int x, int y);
  void resize_image(const std::string& image_name, int w, int h);
  void clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void flip_display();
  void load_image(const std::string& image_name, const std::string& filename);
  void load_font(
    const std::string& font_name, const std::string& filename, int size);
  void render_text(
    const std::string& font_name, const std::string& text,
    int x, int y,
    uint8_t r, uint8_t g, uint8_t b
  );

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  bool running_;
  std::map<std::string, Image> images_;
  GameLogic& game_logic_;
  std::map<std::string, TTF_Font*> fonts_;
};

#endif  // GAME_SDL_APPLICATION_H