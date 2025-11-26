#include "Input.h"
#include "Key.h"
#include "WindowManager.h"

#include <iostream>

int main() {
  WindowManager wm;
  Window *win = wm.create(600, 400, "Test Window");

  Input input;
  input.init(win);

  while (wm.update()) {
    input.update();

    if (input.isKeyDown(Key::W))
      std::cout << "W is held\n";

    if (input.isKeyPressed(Key::SPACE))
      std::cout << "Space just pressed\n";

    if (input.isKeyReleased(Key::SPACE))
      std::cout << "Space just released\n";

    input.endFrame();
  }

  return 0;
}
