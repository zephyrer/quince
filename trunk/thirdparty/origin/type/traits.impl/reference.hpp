// Form an lvalue reference to T.
template <typename T>
  struct require_lvalue_reference 
    : std::add_lvalue_reference<T>
  {};

template <>
  struct require_lvalue_reference<void>
  {
    using type = subst_failure;
  };

// Form an rvalue reference to T.
template <typename T>
  struct require_rvalue_reference
    : std::add_rvalue_reference<T>
  {};

template <>
  struct require_rvalue_reference<void>
  {
    using type = subst_failure;
  };
