#include <cstring>
#include <iostream>

#include "byterange.h"

ByteRange::ByteRange(const char *attribute) {
  // length of sub-range
  if ((attribute = strchr(attribute, ':')) == nullptr) {
    throw std::runtime_error("BYTERANGE attribute has no value");
  }
  lengthSubRange = getUnsignedLong(++attribute); // skip ':'

  // start of sub-range (optional)
  if ((attribute = strchr(attribute, '@')) != nullptr) {
    startSubRange = getUnsignedLong(++attribute); // skip '@'
  }
}