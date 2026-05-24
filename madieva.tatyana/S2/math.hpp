#ifndef MATH_HPP
#define MATH_HPP
#include <limits>
#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace madieva {

  const long long MAX = std::numeric_limits<long long>::max();
  const long long MIN = std::numeric_limits<long long>::min();

  bool isOperator(const std::string& token);
  long long computeGcd(long long a, long long b);
  long long calculateOperation(const std::string & op, madieva::Stack< long long > & temp);
  void evaluateExpression(madieva::Queue< std::string > & post, madieva::Stack< long long > & res);

}

#endif
