// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>
template<typename T, int k>
class tstack {

  private:

  T arr[k];
  int top;

  public:

  tstack():top(-1) {}
  bool isEmpty() const {
    return top == -1;
  }
  bool isFull() const {
    return top == k - 1;
  }
  T get() const {
    if (!isEmpty())
      return arr[top];
    else throw std::string("Empty");
  }
  void pop() {
    if (!isEmpty())
      top--;
    else throw std::string("Empty");
  }
  void push(T item) {
    if (!isFull())
      arr[++top] = item;
    else throw std::string("Full");
  }
};

#endif  // INCLUDE_TSTACK_H_
