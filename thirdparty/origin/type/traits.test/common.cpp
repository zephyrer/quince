#include "../traits.hpp"
#include <string>

using namespace std;

struct s {
  s(s&&) = delete;
  s(const s&) = delete;
};

struct base {};
struct derived : base {};

int main()
{
  static_assert(Common<int, int>(), "");
  static_assert(Same<Common_type<int, int>, int>(), "");

  static_assert(Common<const int, const int>(), "");
  static_assert(Same<Common_type<const int, const int>, int>(), "");

  static_assert(Common<int, const int>(), "");
  static_assert(Same<Common_type<int, const int>, int>(), "");

  static_assert(Common<int&, int&>(), "");
  static_assert(Same<Common_type<int&, int&>, int>(), "");
  static_assert(Same<Common_type<const int&, const int&>, int>(), "");
 
  static_assert(Same<Common_type<s, s>, s>(), "");
  static_assert(Same<Common_type<s, const s&>, s>(), "");
  static_assert(!Common<s, int>(), "");

  static_assert(Common<int, long>(), "");
  static_assert(Same<Common_type<int, long>, long>(), "");

  static_assert(Common<int, float>(), "");
  static_assert(Same<Common_type<int, float>, float>(), "");

  static_assert(Common<derived, base>(), "");
  static_assert(Same<Common_type<derived, base>, base>(), "");

  static_assert(Common<string, char*>(), "");
  static_assert(Same<Common_type<string, char*>, string>(), "");

  static_assert(Common<string, const char*>(), "");
  static_assert(Same<Common_type<string, const char*>, string>(), "");

  static_assert(Common<signed int, unsigned int>(), "");
  static_assert(Same<Common_type<signed char, unsigned char>, int>(), "");
  static_assert(Same<Common_type<signed short, unsigned short>, int>(), "");
  static_assert(Same<Common_type<signed int, unsigned int>, unsigned int>(), "");
  static_assert(Same<Common_type<signed long, unsigned long>, unsigned long>(), "");
  
  static_assert(Same<Common_type<int>, int>(), "");
  static_assert(Same<Common_type<char, short, int>, int>(), "");
  static_assert(Same<Common_type<short, char, int>, int>(), "");
  static_assert(Same<Common_type<char, int, short>, int>(), "");
  static_assert(Same<Common_type<short, int, char>, int>(), "");
  static_assert(Same<Common_type<int, char, short>, int>(), "");
  static_assert(Same<Common_type<int, short, char>, int>(), "");

  return 0;
}
