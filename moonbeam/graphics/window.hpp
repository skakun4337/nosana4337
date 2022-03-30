#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <moonbeam/dependencies.hpp>

namespace MoonBeam { namespace Graphics {
class Window {
public:
  Window(unsigned int width, unsigned int height);
  ~Window();

  void Open();
  void Close();
  bool ShouldClose();
  void SwapBuffers();

  bool GetKeyPressed(int key);
private:
  GLFWwindow* _window;
  unsigned int _width;
  unsigned int _height;

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
}}
#endif
