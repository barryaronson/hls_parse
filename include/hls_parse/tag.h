#pragma once

#include <string>

enum Terminator : char { TagSep = ':', AttributeSep = '=' };

const char *compareIdentifier(const char *input, const char *identifier,
                              const char endChar);

class Tag {
public:
  std::string getQuotedString(const char *str);
  unsigned long getUnsignedLong(const char *str) { return atoll(str); }
  double getDouble(const char *str) { return atof(str); }
  const char *compareAttribute(const char *input, const char *attribute) {
    return compareIdentifier(input, attribute, AttributeSep);
  }
};