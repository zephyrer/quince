#include "../traits.hpp"

using namespace std;

int main(int argc, char** argv)
{
  static_assert(Same<Select<0, char, short, int, long>, char>(), "");
  static_assert(Same<Select<1, char, short, int, long>, short>(), "");
  static_assert(Same<Select<2, char, short, int, long>, int>(), "");
  static_assert(Same<Select<3, char, short, int, long>, long>(), "");
  
  return 0;
}
