#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "sdl_application.h"

int main(int argc, char *argv[]) {
  try {
    SDLApplication app;
    app.run();
  } catch (SDLException ex) {
    std::cout << "SDLException Caught" << std::endl;
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
