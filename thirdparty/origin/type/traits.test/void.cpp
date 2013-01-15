#include "../traits.hpp"

using namespace std;

int main()
{
  static_assert(Void<void>(), "");
  static_assert(!Void<int>(), "");
}
