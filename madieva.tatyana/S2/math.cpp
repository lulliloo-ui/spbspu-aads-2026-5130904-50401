#include "math.hpp"

namespace madieva
{

  bool isOperator(const std::string& token)
  {
    return token == "+" ||
      token == "-" ||
      token == "*" ||
      token == "/" ||
      token == "%" ||
      token == "gcd";
  }

  long long computeGcd(long long a, long long b)
  {
    while (b != 0) {
      long long temp = b;
      b = a % b;
      a = temp;
    }
    if (a < 0) {
      a *=  (-1);
    }
    return a;
  }

  long long calculateOperation(const std::string & op, madieva::Stack< long long > & temp)
  {
    if (temp.size() < 2) {
      throw std::runtime_error("Invalid expression");
    }
    const long long right = temp.top();
    temp.pop();
    const long long left = temp.top();
    temp.pop();
    if (op == "+") {
      if ((right > 0 && left > MAX - right) ||
        (right < 0 && left < MIN - right)) {
        throw std::runtime_error("Overflow");
      }
      return left + right;
    }
    if (op == "-") {
      if ((right > 0 && left < MIN + right) ||
        (right < 0 && left > MAX + right)) {
        throw std::runtime_error("Overflow");
      }
      return left - right;
    }
    if (op == "*") {
      if (left != 0 && right != 0) {
        if ((left > 0 && right > 0 && left > MAX / right) ||
          (left > 0 && right < 0 && right < MIN / left) ||
          (left < 0 && right > 0 && left < MIN / right) ||
          (left < 0 && right < 0 && left > MAX / right)) {
          throw std::runtime_error("Overflow");
        }
      }
      return left * right;
    }
    if (op == "/") {
      if (right == 0) {
        throw std::runtime_error("Division by zero");
      }
      return left / right;
    }
    if (op == "%") {
      if (right == 0) {
        throw std::runtime_error("Modulo by zero");
      }
      long long result = left % right;
      if (result < 0) {
        result += right;
      }
      return result;
    }
    if (op == "gcd") {
      return computeGcd(left, right);
    }
    throw std::runtime_error("Unknown operator");
  }

  void evaluateExpression(madieva::Queue< std::string > & post, madieva::Stack< long long > & res)
  {
    madieva::Stack< long long > temp;
    while (!post.empty()) {
      const std::string token = post.front();
      if (isOperator(token)) {
        temp.push(calculateOperation(token, temp));
      } else {
        temp.push(std::stoll(token));
      }
      post.pop();
    }
    if (temp.size() != 1) {
      throw std::runtime_error("Invalid expression");
    }
    res.push(temp.top());
  }

}