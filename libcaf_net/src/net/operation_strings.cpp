// clang-format off
// DO NOT EDIT: this file is auto-generated by caf-generate-enum-strings.
// Run the target update-enum-strings if this file is out of sync.
#include "caf/config.hpp"
#include "caf/string_view.hpp"

CAF_PUSH_DEPRECATED_WARNING

#include "caf/net/operation.hpp"

#include <string>

namespace caf {
namespace net {

std::string to_string(operation x) {
  switch(x) {
    default:
      return "???";
    case operation::none:
      return "none";
    case operation::read:
      return "read";
    case operation::write:
      return "write";
    case operation::read_write:
      return "read_write";
    case operation::shutdown:
      return "shutdown";
  };
}

bool from_string(string_view in, operation& out) {
  if (in == "none") {
    out = operation::none;
    return true;
  } else if (in == "read") {
    out = operation::read;
    return true;
  } else if (in == "write") {
    out = operation::write;
    return true;
  } else if (in == "read_write") {
    out = operation::read_write;
    return true;
  } else if (in == "shutdown") {
    out = operation::shutdown;
    return true;
  } else {
    return false;
  }
}

bool from_integer(std::underlying_type_t<operation> in,
                  operation& out) {
  auto result = static_cast<operation>(in);
  switch(result) {
    default:
      return false;
    case operation::none:
    case operation::read:
    case operation::write:
    case operation::read_write:
    case operation::shutdown:
      out = result;
      return true;
  };
}

} // namespace net
} // namespace caf

CAF_POP_WARNINGS
