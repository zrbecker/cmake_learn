#ifndef GAME_ENGINE_SDL_APPLICATION_H
#define GAME_ENGINE_SDL_APPLICATION_H

#include <map>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "game/engine/engine.h"

namespace game {
namespace engine {

struct Image {
  SDL_Surface* surface;
  SDL_Texture* texture;
};

struct KeyInfo {
  std::string input_name;
  Key key;
  bool is_key_down;
};

class SDLEngine : public Engine {
public:
  SDLEngine(GameLogic& game_logic);
  ~SDLEngine();

  void run() override;

  void draw_image(const std::string& image_name, int x, int y) override;
  void resize_image(const std::string& image_name, int w, int h) override;
  void clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
  void flip_display() override;
  void load_image(
    const std::string& image_name, const std::string& filename) override;
  void load_font(
    const std::string& font_name,
    const std::string& filename,
    int size
  ) override;
  void render_text(
    const std::string& font_name, const std::string& text,
    int x, int y,
    uint8_t r, uint8_t g, uint8_t b
  ) override;
  void register_input(const std::string& input_name, Key key) override;
  bool input_is_down(const std::string& input_name) override;

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  bool running_;
  std::map<std::string, Image> images_;
  GameLogic& game_logic_;
  std::map<std::string, TTF_Font*> fonts_;
  std::map<std::string, std::unique_ptr<KeyInfo>> input_to_key_info_;
  std::map<Key, KeyInfo*> key_to_key_info_;
};
  
}  // namespace engine
}  // namespace game

#endif  // GAME_ENGINE_SDL_APPLICATION_H