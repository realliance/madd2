#pragma once
#include <utility>
#include <variant>

#include "status.h"

template <typename T>
concept isMonoState = std::is_same_v<T, std::monostate>;
template <typename T>
concept isNotStatus = std::negation_v<std::is_same<T, std::monostate>>;

template <isNotStatus T = std::monostate>
class Maybe {
  std::variant<Status, T> status, data;

 public:
  template <typename S>
  // NOLINTNEXTLINE(google-explicit-constructor)
  operator Maybe<S>() requires isMonoState<T> {
    return Maybe<S>(status);
  }

  // NOLINTNEXTLINE(google-explicit-constructor)
  Maybe(T data) : data(data) {}
  // NOLINTNEXTLINE(google-explicit-constructor)
  Maybe(Status const& status) : status(status){};
  [[nodiscard]] auto Ok() const -> bool {
    return std::holds_alternative<T>(data);
  }
  auto Status() -> Status { return std::get<Status>(status); }
  auto Unwrap() -> T { return std::get<T>(data); }
};
