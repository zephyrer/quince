// Deduce the result of the expression t == u.
template <typename T, typename U>
  struct get_equal_result
  {
  private:
    template <typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x == y);

    static subst_failure check(...);

  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };

// Deduce the result type of the expression t != u.
template <typename T, typename U>
  struct get_not_equal_result
  {
  private:
    template <typename X, typename Y>
      static auto check(X&& x, Y&& y) -> decltype(x != y);
    
    static subst_failure check(...);
  public:
    using type = decltype(check(std::declval<T>(), std::declval<U>()));
  };
  
