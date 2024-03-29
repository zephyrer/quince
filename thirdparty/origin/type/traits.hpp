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

// The common_type trait defines the basic mechanism by which the common type
// lattice is defined. The type trait is part of the public interface because
// it can be specialized by a user to disambiguate conversions or to derive a 
// new type that is not one of the type arguments. For example, if T and U are
// mutually convertible, common_type must be specialized to select one of those
// conversions as being dominant. If the common type C of T and U is neither of 
// those types, the common_type must be specialized to derive C. An example of
// this is std::duration.
//
// In general, it is preferable to avoid explicit specialization of this relation.
// The first approach to defining an appropriate conversion lattice is to 
// use the standard mechanisums for conversion.

template <typename... Args>
  struct common_type;

// The common type of a single type is obviously that type.
template <typename T>
  struct common_type<T>
  {
    using type = T;
  };

// The common type relation. This specialization is the primary mechanism by 
// which common type is defined, and by which it is extended.
template <typename T, typename U>
  struct common_type<T, U>
  {
  private:
    template <typename X, typename Y>
      static auto check(X&& a, Y&& b) -> decltype(true ? a : b);

      static subst_failure check(...);
      
      using C = decltype(check(std::declval<T>(), std::declval<U>()));
  public:
    using type = typename std::remove_const<
      typename std::remove_reference<C>::type
    >::type;
  };

// When the type arguments are the same, we can bypass the deduction on the 
// conditional operator.
template <typename T>
  struct common_type<T, T>
  {
    using type = typename std::remove_const<
      typename std::remove_reference<T>::type
    >::type;
  };

// The recursive definition of common type simply applies the common type
// to each pair of types in turn.
template <typename T, typename U, typename... Args>
  struct common_type<T, U, Args...>
    : common_type<typename common_type<T, U>::type, Args...>
  {};

template <typename... Args>
  using Common_type = typename common_type<Args...>::type;


template <typename... Args>
  constexpr bool Common()
  {
    return Subst_succeeded<Common_type<Args...>>();
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

#include "traits.impl/reference.hpp"

// Returns true if T is an lvalue reference to some type U.
template <typename T>
  constexpr bool Rvalue_reference()
  {
    return std::is_rvalue_reference<T>::value;
  };

// Return true if T is either an lvalue or rvalue reference to some type U.
template <typename T>
  constexpr bool Reference() 
  {
    return std::is_reference<T>::value;
  };

// An alias to an lvalue-reference-to-T.
template <typename T>
  using Add_lvalue_reference = typename std::add_lvalue_reference<T>::type;

// An alias to an rvalue-reference-to-T.
template <typename T>
  using Add_rvalue_reference = typename std::add_rvalue_reference<T>::type;

// Refers to an lvalue-reference-to-T if it can be formed.
template <typename T>
  using Require_lvalue_reference =
    typename require_lvalue_reference<T>::type;

// Refers to an rvalue-reference-to-T if it can be formed.
template <typename T>
  using Require_rvalue_reference =
    typename require_rvalue_reference<T>::type;

// Returns true if T is a class or struct
template <typename T>
  constexpr bool Class() { return std::is_class<T>::value; }

// Returns true if T is a union.
template <typename T>
  constexpr bool Union() { return std::is_union<T>::value; }

// Returns true if T has no member variables.
template <typename T>
  constexpr bool Empty() { return std::is_empty<T>::value; }

// Returns true if T has at least one virtual method.
template <typename T>
  constexpr bool Polymorphic() { return std::is_polymorphic<T>::value; }

// Returns true if T has at least one pure virtual method.
template <typename T>
  constexpr bool Abstract() { return std::is_abstract<T>::value; }

// Returns true if T is an enum or enum class.
template <typename T>
  constexpr bool Enum() { return std::is_enum<T>::value; }

// An alias to the integer type that stores the values of the enum T.
template <typename T>
  using Underlying_type = typename std::underlying_type<T>::type;

///////////////////////////////////////////////////////////////////////
// Composite categories
// 
// These traits query the composite categories of primary types. Note that
// there are other categories (e.g. Reference), but these do not belong to 
// any more obvious grouping.
//

// Returns true if T is an object type. An object type is any type that can
// be placed in a region of memory. Void, reference, and function types are
// not object types.
template <typename T>
  constexpr bool Object() { return std::is_object<T>::value; }

// Returns true if T is a scalar type. A scalar type is an object type that is 
// an integer type, floating point type, or pointer. Compound types (classes,
// unions, and arrays) are not scalar.
template <typename T>
  constexpr bool Scalar() { return std::is_scalar<T>::value; }

// Returns true if T is a compound type. Compound types are class types,
// union types, and arrays.
template <typename T>
  constexpr bool Compound() { return std::is_compound<T>::value; }

// Returns true if T is a built-in type
template <typename T>
  constexpr bool Fundamental() { return std::is_fundamental<T>::value; }

// Returns true if T is an arithmetic type. Integer and floating point types
// are arithmetic types.
template <typename T>
  constexpr bool Arithmetic() { return std::is_arithmetic<T>::value; }

////////////////////////////////////////////////////////////////////////////////
// Qualifiers
//
// The following type traits implement queries and transformations for const
// and volatile qualifiers.
////////////////////////////////////////////////////////////////////////////////

// Returns true if T is const-qualified
template <typename T>
  constexpr bool Const() { return std::is_const<T>::value; }

// Returns true if T is volatile-qualified
template <typename T>
  constexpr bool Volatile() { return std::is_volatile<T>::value; }

// Returns true if T is cv-qualified.
template <typename T>
  constexpr bool Qualified() { return Const<T>() || Volatile<T>(); }

// An alias to const-qualified T
template <typename T>
  using Add_const = typename std::add_const<T>::type;

// An alias to const-volatile-qualified T
template <typename T>
  using Add_volatile = typename std::add_volatile<T>::type;

// An alias to const volatile qualified T
template <typename T>
  using Add_cv = typename std::add_cv<T>::type;

// An alias to U if T has type const U, otherwise T.
template <typename T>
  using Remove_const = typename std::remove_const<T>::type;

// An alias to U if T has type volatile U, otherwise T.
template <typename T>
  using Remove_volatile = typename std::remove_volatile<T>::type;

// An alias to U if T is cv-qualified or T otherwise.
template <typename T>
  using Remove_cv = typename std::remove_cv<T>::type;

// Decay an array into a pointer or a function into a function pointer
template <typename T>
  using Decay = typename std::decay<T>::type;

////////////////////////////////////////////////////////////////////////////
// Layout, initialization, and assignment
//
// These traits describe properties of a type's layout, properties of its
// destructor, constructors, and assignment operators.
//
// Many of the traits in this section deal with triviality of an operation.
// A constructor or destructor is trivial if:
// 
// - It is generated by the compiler, either implicitly or because of an 
//   '= default' annotation, and:
// - The class has no virtual functions or virtual bases.
// - All of the corresponding operations in the direct bases of the class
//   are also trivial.
// - The corresponding operations in all non-static data members of the class
//   are also trivial.
//
////////////////////////////////////////////////////////////////////////////

// Returns true if T is a standard layout type
// A standard-layout class is a class that
// 1. has no non-static data members that aren't standard-layout
// 2. has no virtual functions and no virtual base classes
// 3. has the same access control for all non-static data members
// 4. has no base classes that aren't standard-layout
// 5. either has no base class with non-static data members or has no
//    non-static data members in the most derived class and only one base with them
// 6. has no base classes of the same type as the first non-static data member
template <typename T>
  constexpr bool Standard_layout() { return std::is_standard_layout<T>::value; }

// Return true if T has a destructor.
template <typename T>
  constexpr bool Destructible() { return std::is_destructible<T>::value; }

// Returns true if T has a trivial destructor.
//
template <typename T>
  constexpr bool Trivially_destructible()
  {
    return std::is_trivially_destructible<T>::value;
  }

// Returns true if T has a destructor that does not propagate exceptions.
template <typename T>
  constexpr bool Nothrow_destructible()
  {
    return std::is_nothrow_destructible<T>::value;
  }

// Returns true if T has a virtual destructor
template <typename T>
  constexpr bool Has_virtual_destructor()
  {
    return std::has_virtual_destructor<T>::value;
  }

///////////////////////////////////////////////////////////////////////////
template <typename T, typename... Args>
  constexpr bool Constructible()
  {
    return std::is_constructible<T, Args...>::value;
  }

template <typename T, typename... Args>
  constexpr bool Trivially_constructible()
  {
    return std::is_trivially_constructible<T, Args...>::value;
  }

// Returns true if T has a constructor for Args that does not propagate exceptions.
template <typename T, typename... Args>
  constexpr bool Nothrow_constructible()
  {
    return std::is_nothrow_constructible<T, Args...>::value;
  }

//////////////////////////////////////////////////////////////////////////////
// Default construction

// Returns true if T has a default constructor.
template <typename T>
  constexpr bool Default_constructible()
  {
    return std::is_default_constructible<T>::value;
  }

// Returns true if T has a trivial default constructor.
template <typename T>
  constexpr bool Trivially_default_constructible()
  {
    return std::is_trivially_default_constructible<T>::value;
  }

// Returns true if T can be default constructed, and the constructor doesn't
// propagate exceptions.
template <typename T>
  constexpr bool Nothrow_default_constructible()
  {
    return std::is_nothrow_default_constructible<T>::value;
  }
