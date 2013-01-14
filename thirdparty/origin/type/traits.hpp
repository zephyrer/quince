#include <type_traits>
#include <utility>

template <bool B>
  using boolean_constant = std::integral_constant<bool, B>;

using True_type = std::true_type;
using False_type = std::false_type;

template <std::size_t N>
  using size_constant = std::integral_constant<std::size_t, N>;

template <typename... Ts>
  struct type_list {};

#include "traits.impl/meta.hpp"

// Refers to T, only if B is true.
// If B is false, the alias results in a substitution failure, eliminateing 
// an overload or specialization from a candidate set.
// For example:
// template <typename T>
//   Requires<Integer<T>(), T> odd(T n) { return T & 1; }
// Here, the operation, odd, is only a viable candidate when the expression
// Integer<T>() evaluates to true.

template <bool B, typename T = void> 
  using Requires = typename std::enable_if<B, T>::type;

// The If alias refers to T when B is true and F otherwise. 
// For example:
// 
// template<typename T>
//   using Ptr = If<Const<T>(), const T*, T*>;
//
// Ptr<int>  // is int*
// Ptr<const int> // is const int*

template <bool B, typename T, typename F>
  using If = typename std::conditional<B, T, F>::type;

#include "traits.impl/select.hpp"

// The Select alias refers to the Nth type is a sequence of Args.
// It is a generalization of if If, to N values.
// For example:
//
// Select<0, char, short, int, long> // is char
// Select<1, char, short, int, long> // is short

template <std::size_t N, typename... Args>
  using Select = typename selection<N, Args...>::type;

template <typename... Args>
  constexpr bool Same()
  {
    return are_same<Args...>::value;
  }

template <typename... Args>
  constexpr bool Different()
  {
    return !Same<Args...>();
  }

// An alias to the first type in a non-empty sequence of type arguments.
// For example:
//
//   Front_type<char, short, int> // is char
template <typename... Args>
  using Front_type = typename front_type<Args...>::type;

// An alias to the last type in a non-empty sequence of type arguments.
// For example:
//
//   Back_type<char, short, int> // is int
template <typename T, typename... Args>
  using Back_type = typename back_type<T, Args...>::type;

// The Structural_type alias identifies the structure or value type in a 
// cv-qualified reference type T. The structural type of a cv-qualified or
// reference type is the underlying type of the cv-qualifiers or reference.
// That is, it describes the structure of the object being constrained.
// For example:
//
//     Structural_type<int>       // is int
//     Structural_type<const int> // is int
//     Structural_type<const int&>// is int
//     Structural_type<int*>      // is int*
//     Structural_type<int[3]>    // is int[3]
// Many type functions in this library operate only on or return only structural// types. This alias is provided specifically to derive structural types from 
// cv-qualified or reference type expressions.
template <typename T>
  using Structural_type
    = typename std::remove_cv<
        typename std::remove_reference<T>::type
      >::type;

// Provide a small set of types and type functions that are used to provide
// a framework for managing substitution failure in lookup.
// The primary features of this component is the subst_failure class, a type that
// indicates when a lookup has failed.
//
// There are two associated type predicates that can be used to determine
// whether a result type indicates substitution failure.
//
// Subst_failed<T>()       -- True if T indicates substitution failure
// Subst_succeeded<T>()    -- True if T is not a substitution failure
 
struct subst_failure {};

template <typename T>
  constexpr bool Subst_failed()
  {
    return std::is_same<T, subst_failure>::value;
  }

template <typename T>
  constexpr bool Subst_succeeded()
  {
    return !std::is_same<T, subst_failure>::value;
  }

#include "traits.impl/operators.hpp"

// Returns true if every argument is true of if no arguments are given
constexpr bool All() { return true; }
template <typename... Args>
  constexpr bool All(bool b, Args... args)
  {
    return b && All(args...);
  }

// Returns true if some argument is true.
constexpr bool Some() { return false; }

template <typename... Args>
  constexpr bool Some(bool b, Args... args)
  {
    return b || Some(args...);
  }

// Returns true if every argument is false or if no arguments are given
constexpr bool None() { return true; }

template <typename... Args>
  constexpr bool None(bool b, Args... args)
  {
    return !b && None(args...);
  }

template <typename T>
  constexpr bool Void() 
  {
    return std::is_void<T>::value;
  }

// Returns true if T is a signed or unsigned, possibly cv-qualified, bool,
// char, short, int, long or long long.
template <typename T>
  constexpr bool Integer() 
  {
    return std::is_integral<T>::value; 
  }

//Returns true if T is a signed type. Note that floating point values
// are signed.
template <typename T>
  constexpr bool Signed() { return std::is_signed<T>::value; }

// Returns true if T is an unsigned type.
template <typename T>
  constexpr bool Unsigned() { return std::is_unsigned<T>::value; }

#include "traits.impl/integer.hpp"


// An alias for the unsigned integral type with the same width as T.
template <typename T>
  using Make_unsigned = typename make_unsigned<T>::type;

// An alias for the signed integral type with the same width as T.
template <typename T>
  using Make_signed = typename make_signed<T>::type;

// Returns true if T is a float, double, or long double.
template <typename T>
  constexpr bool Floating_point() { return std::is_floating_point<T>::value; }

// Return true if T is an array type of type U[N]
template <typename T>
  constexpr bool Array() { return std::is_array<T>::value; }

// Returns the number of dimensions of the array type T. 
// If T is not an array, it has 0 dimensions. 
// For example:
//
// using A1 = int[3][2];
// static_assert(Rank<A1>() == 2);
//
// using A2 = int[5];
// static_assert(Rank<A2>() == 1);
//
// using A3 = int;
// static_assert(Rank<A3>() == 0);
//
template <typename T>
  constexpr unsigned Rank() { return std::rank<T>::value; }

// Returns the extent of the array type T in the Ith dimension. 
// The extent of an array is the number of subobjects allocated in that dimensions.
// For example:
//
// using A = int[3][2];
// static_assert(Extent<A, 0>() == 3, "");
// static_assert(Extent<A, 1>() == 2, "");
//
// If the dimension I is not given, it defaults to 0.
template <typename T, unsigned I = 0>
  constexpr std::size_t Extent() { return std::extent<T, I>::value; }

// An alias to the underlying value type of the array type T.
// For example:
// 
// using A = int[3][2];
// using B = Remove_extent<A>;
// static_assert(Same<B, int[3]>(), "");
template <typename T>
  using Remove_extent = typename std::remove_extent<T>::type;

// An alias to the underlying value type of the array type T.
// For example:
//
// using A = int[3][2];
// using B = Remove_all_extents<A>;
// static_assert(Same<B, int>(), "");
template <typename T>
  using Remove_all_extents = typename std::remove_all_extents<T>::type;

// Returns true if T is a pointer.
template <typename T>
  constexpr bool Pointer() { return std::is_pointer<T>::value; }

// An alias to a pointer-to-T.
template <typename T>
  using Add_pointer = typename std::add_pointer<T>::type;

// An alias to the underlying type U if T is a pointer to U.
template <typename T>
  using Remove_pointer = typename std::remove_pointer<T>::type;



