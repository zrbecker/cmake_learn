#ifndef GAME_ENGINE_ENGINE_H
#define GAME_ENGINE_ENGINE_H

#include <string>
#include <memory>

namespace game {
namespace engine {

class GameLogic;

class Engine {
public:
  static std::unique_ptr<Engine> create_sdl_engine(GameLogic& game_logic);

  virtual void run() = 0;

  virtual void draw_image(const std::string& image_name, int x, int y) = 0;
  virtual void resize_image(const std::string& image_name, int w, int h) = 0;
  virtual void clear_display(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
  virtual void flip_display() = 0;
  virtual void load_image(
    const std::string& image_name, const std::string& filename) = 0;
  virtual void load_font(
    const std::string& font_name, const std::string& filename, int size) = 0;
  virtual void render_text(
    const std::string& font_name, const std::string& text,
    int x, int y,
    uint8_t r, uint8_t g, uint8_t b
  ) = 0;
};

}  // namespace engine
}  // namespace game

#endif  // GAME_ENGINE_ENGINE_H