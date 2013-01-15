#include "../traits.hpp"

using namespace std;

int main()
{
  static_assert(Floating_point<float>(), "");
  static_assert(Floating_point<double>(), "");
  static_assert(Floating_point<long double>(), "");

  static_assert(!Floating_point<int>(), "");
}
