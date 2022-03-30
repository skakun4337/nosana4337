#include <moonbeam/core/exception.hpp>

using namespace MoonBeam;
using namespace Core;

Exception::Exception() {}

Exception::Exception(std::string message) : _message(message.c_str()) {}

Exception::~Exception() {}

std::string Exception::what() const {
  return this->_message;
}
