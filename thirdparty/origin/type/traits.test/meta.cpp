#include "../traits.hpp"

using namespace std;

int main(int argc, char** argv)
{
  static_assert(Same<Front_type<char>, char>(), "");
  static_assert(Same<Front_type<char, short, int, long>, char>(), "");

  static_assert(Same<Back_type<char>, char>(), "");
  static_assert(Same<Back_type<char, short, int, long>, long>(), "");
}
