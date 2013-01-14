template <typename... Args> struct front_type;

template <typename T, typename... Args>
  struct front_type<T, Args...>
  {
    using type = T;
  };

template <typename... Args> struct back_type;

template <typename T>
  struct back_type<T>
  { 
    using type = T;
  };

template <typename T, typename... Args>
  struct back_type<T, Args...> : back_type<Args...>
  {};

// Returns true if all of the type are the same, or if Args... is an empty 
// sequence of types. Evaluation is of type equality is performed left-to-right,
// and the operation will not instantiate arguments after a non-equal pair is 
// found.
template <typename... Args> struct are_same;

template <>
  struct are_same<> : std::true_type {};

template <typename T>
  struct are_same<T> : std::true_type {};

template <typename T, typename U, typename... Args>
  struct are_same<T, U, Args...>
    : boolean_constant<std::is_same<T, U>::value &&
      are_same<U, Args...>::value>
  {};

template <typename T>
  struct identity
  {
    using type = T;
  };
