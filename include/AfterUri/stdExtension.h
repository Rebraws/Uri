#ifndef STDEXTENSION_H_
#define STDEXTENSION_H_

#include <string>
#include <cctype>
#include <algorithm>

namespace InternalUriStdExt {


// Instead of writting some function like toLower, we can use our custom String
// class It provides a better performance
// (https://www.quick-bench.com/q/lGLevQz0Fwahy-LdWQpqdX1cD1E) and is more
// simple to use instead of calling a function like
class String : public std::string
{
public:
  using std::string::string;

  template<class InputIt, class UnaryOperation>
  constexpr String(InputIt first, InputIt last, UnaryOperation unary_op);
};


template<class InputIt, class UnaryOperation>
constexpr String::String(InputIt first, InputIt last, UnaryOperation unary_op)
{
  this->resize(static_cast<std::string::size_type>(std::distance(first, last)));
  std::transform(first, last, this->begin(), unary_op);
}


}// namespace InternalUriStdExt


#endif
