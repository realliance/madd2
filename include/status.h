#pragma once
#include <iosfwd>
#include <string>

enum StatusCode {
  OK,
  FAILED_TO_ADD_COMPONENT,
  FAILED_TO_REMOVE_COMPONENT,
  SYSTEM_FAILURE,
  NO_HEAP_ENTRY_DATA,
  GENERAL_MADD_FAILURE,
  INVALID_TYPE,
  LAST_STATUS_CODE  // Must be last StatusCode
};

// Status is used as the system function return type to indicate the status
struct Status {
  StatusCode code;
  std::string details;
  bool fatal;
  [[nodiscard]] inline auto Ok() const -> bool {
    return code == StatusCode::OK;
  }

  // Ok, no error response.
  static const Status OK_RESPONSE;
};

auto StatusCodeToStr(StatusCode code) -> std::string;
auto operator<<(std::ostream& os, const Status& status) -> std::ostream&;
