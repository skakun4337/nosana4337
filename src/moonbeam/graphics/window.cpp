#include <moonbeam/graphics/window.hpp>
#include <moonbeam/core/exception.hpp>

using namespace MoonBeam;
using namespace Graphics;

Window::Window(unsigned int width, unsigned int height) {
  this->_height = height;
  this->_width = width;
}

Window::~Window() {
  //glfwDestroyWindow(this->_window);
  //glfwTerminate();
}

void Window::Open() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
  _window = glfwCreateWindow(this->_width, this->_height, "LearnOpenGL", NULL, NULL);
  if (_window == NULL) {
    glfwTerminate();
    throw Core::Exception("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(_window);
  glfwSetFramebufferSizeCallback(_window, this->framebuffer_size_callback);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw Core::Exception("Failed to initialize GLAD");
  }
  glfwSwapInterval(0);
}

void Window::Close() {
  glfwSetWindowShouldClose(this->_window, true);
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(this->_window);
}

void Window::SwapBuffers() {
  glfwSwapBuffers(this->_window);
}

bool Window::GetKeyPressed(int key) {
  return glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
