template <std::size_t N, typename... Args>
  struct selection;

template <std::size_t N, typename T, typename... Args>
  struct selection<N, T, Args...>
    : selection<N - 1, Args...>
  {};

template <typename T, typename... Args>
  struct selection<0, T, Args...>
  {
    using type = T;
  };
