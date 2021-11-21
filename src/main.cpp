#include <iostream>

#include <core/http.hpp>

int main() {
  core::ServeForever();
  std::cout << "hello";
  return 0;
}
