#include <iostream>
#include "../traits.hpp"

using namespace std;

int main(int argc, char** argv)
{
  static_assert(Same<int, int>(), "");
  static_assert(Same<const int, const int>(), "");
  static_assert(Same<volatile int, volatile int>(), "");
  static_assert(Same<const volatile int, const volatile int>(), "");

  static_assert(Same<int&, int&>(), "");
  static_assert(Same<const int&, const int&>(), "");
  static_assert(Same<volatile int&, volatile int&>(), "");
  static_assert(Same<const volatile int&, const volatile int&>(), "");

  static_assert(Same<int&&, int&&>(), "");
  static_assert(Same<const int&&, const int&&>(), "");
  static_assert(Same<volatile int&&, volatile int&&>(), "");
  static_assert(Same<const volatile int&&, const volatile int&&>(), "");
 
  static_assert(Same<int*, int*>(), "");
  static_assert(Same<const int*, const int*>(), "");
  static_assert(Same<volatile int*, volatile int*>(), "");
  static_assert(Same<const volatile int*, const volatile int*>(), "");

  using X = int;
  static_assert(Same<int, X>(), "");
  static_assert(Same<const int, const X>(), "");
  static_assert(Same<int&, X&>(), "");
  static_assert(Same<int&&, X&&>(), "");
  static_assert(Same<int*, X*>(), "");

  static_assert(Same<int, int, int, int, int>(), "");
  static_assert(!Same<int, int, int&, int>(), "");

  static_assert(Different<int, const int>(), "");
  static_assert(Different<const int, int>(), "");

  static_assert(Different<int, int&>(), "");
  static_assert(Different<int&, int>(), "");

  static_assert(Different<int, int&&>(), "");
  static_assert(Different<int&&, int>(), "");
  
  static_assert(Different<int, int*>(), "");
  static_assert(Different<int*, int>(), "");

  return 0;
}

