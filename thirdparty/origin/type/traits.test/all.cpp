#include "../traits.hpp"

using namespace std;

constexpr bool True_func() { return true; }
constexpr bool False_func() { return false; }

int main()
{
  static_assert(All(true, true, true), "");
  static_assert(!All(true, true, false), "");

  static_assert(All(True_type{}), "");
  static_assert(All(True_func()), "");
  static_assert(!All(False_func()), "");
  static_assert(!All(False_type{}), "");

  static_assert(All(), "");
  return 0;
}
