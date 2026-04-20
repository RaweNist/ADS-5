// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static std::string numbers = "0123456789";
static std::string operands = "()+-*/";
std::string infx2pstfx(const std::string& inf) {
  std::string res = "";
  TStack<char, 100> temp;
  for (int i = 0; i < inf.size(); ++i) {
    if (numbers.find(inf[i]) <= 10 && numbers.find(inf[i]) >= 0) {
      res += inf[i];
    } else if (operands.find(inf[i]) >= 0) {
      int op, op_temp;
      if (inf[i] == '(')
        temp.push(inf[i]);
      else if (!temp.isEmpty()) {
        op = operands.find(inf[i]);
        op_temp = operands.find(temp.get());
        if (op == 2 || op == 3) op = 2;
        else if (op == 4 || op == 5) op = 3;
        if (op_temp == 2 || op_temp == 3) op_temp = 2;
        else if (op_temp == 4 || op_temp == 5) op_temp = 3;
        if (op > op_temp && inf[i] != ')') {
          temp.push(inf[i]);
        } else if (inf[i] == ')') {
          while (temp.get() != '(') {
              res += temp.get();
              temp.pop();
          }
          temp.pop();
        } else {
          while (op_temp >= op) {
            res += temp.get();
            temp.pop();
            if (!temp.isEmpty()) {
              op_temp = operands.find(temp.get());
            } else break;
          }
          temp.push(inf[i]);
        }
      } else if (temp.isEmpty())
        temp.push(inf[i]);
    } else throw std::string("Wrong element format");
  }
  while (!temp.isEmpty()) {
    res += temp.get();
    temp.pop();
  }
  return res;
}

int eval(const std::string& pref) {
  TStack<int, 100> temp1;
  std::string str = infx2pstfx(pref);
  for (int i = 0; i < str.size(); ++i) {
    if (numbers.find(str[i]) >= 0 && numbers.find(str[i]) <= 10) {
      temp1.push(str[i] - '0');
    } else if (operands.find(str[i]) >= 0) {
      int b = temp1.get();
      temp1.pop();
      int a = temp1.get();
      temp1.pop();
      int ab = 0;
      switch (str[i]) {
      case '+': ab = a + b; break;
      case '-': ab = a - b; break;
      case '*': ab = a * b; break;
      case '/': ab = a / b; break;
      default:
        break;
      }
      temp1.push(ab);
    } else throw std::string("Wrong element format");
  }
  return temp1.get();
}
