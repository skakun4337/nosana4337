#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>

namespace MoonBeam {
  namespace Core {
    class Exception {
    public:
      Exception();
      Exception(std::string message);
      virtual ~Exception();

      virtual std::string what() const;
    private:
      std::string _message;
    };
  }
}
#endif
