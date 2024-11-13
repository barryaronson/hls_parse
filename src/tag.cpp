#include <cstring>

#include "tag.h"

const char *compareIdentifier(const char *input, const char *identifier,
                              const char endChar) {
  const char *result = input;

  while (*result == *identifier && *identifier) {
    ++result;
    ++identifier;
  }

  return (*result == endChar && *identifier == '\0') ? ++result : nullptr;
}

std::string Tag::getQuotedString(const char *str) {
  std::string result = "";

  // find beginning of quoted string
  if ((str = strchr(str, '\"')) == nullptr) {
    return result;
  }
  const char *beg = ++str; // skip '\"'

  // find end of quoted string
  if ((str = strchr(str, '\"')) == nullptr) {
    return result;
  }
  const char *end = str;

  // create result
  result.append(beg, end - beg);

  return result;
}
