#ifndef GAME_SDL_APPLICATION_H
#define GAME_SDL_APPLICATION_H

#include <map>
#include <stdexcept>
#include <string>

#include <SDL.h>

class SDLException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

struct Image {
  SDL_Surface* surface;
  SDL_Texture* texture;
};

class SDLApplication {
public:
  SDLApplication();
  ~SDLApplication();

  void run();

protected:
  virtual void setup();
  virtual void render();
  virtual void cleanup();

  void draw_image(const std::string& image_name);
  void clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void flip_display();
  void load_png(const std::string& image_name, const std::string& filename);

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  bool running_;
  std::map<std::string, Image> images_;
};

#endif  // GAME_SDL_APPLICATION_H