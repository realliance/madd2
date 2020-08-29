#include "status.h"

#include <iostream>

const Status Status::OK_RESPONSE = {StatusCode::OK, "", false};

auto StatusCodeToStr(StatusCode code) -> std::string {
  switch (code) {
    case OK:
      return "OK";
    case FAILED_TO_ADD_COMPONENT:
      return "Failed to add component";
    case FAILED_TO_REMOVE_COMPONENT:
      return "Failed to remove component";
    case SYSTEM_FAILURE:
      return "System failure";
    case NO_HEAP_ENTRY_DATA:
      return "No Heap Entry Data";
    case GENERAL_MADD_FAILURE:
      return "General Madd Failure";
    case INVALID_TYPE:
      return "Failure to cast HeapEntry to invalid type";
    default:
      return "Unknown StatusCode passed to StatusCodeToStr";
  }
}

auto operator<<(std::ostream& os, const Status& status) -> std::ostream& {
  os << "Error: " << StatusCodeToStr(status.code);
  os << " Details:" << status.details;
  if (status.fatal) {
    os << " Error is non-recoverable, exiting." << std::endl;
  }
  return os;
}
