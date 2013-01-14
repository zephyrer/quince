// Returns the signed version of T if T is an Integer type.
template <typename T, bool = Integer<T>()>
  struct make_signed;

template <typename T>
  struct make_signed<T, true> : std::make_signed<T> {};

template <typename T>
  struct make_signed<T, false>  { using type = subst_failure; };

// Return the unsigned version of T if T is an Integer type.
template <typename T, bool = Integer<T>()>
  struct make_unsigned;

template <typename T>
  struct make_unsigned<T, true> : std::make_unsigned<T> {};

template <typename T>
  struct make_unsigned<T, false> { using type = subst_failure; };
