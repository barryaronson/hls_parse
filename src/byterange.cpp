#include <cstring>
#include <iostream>

#include "byterange.h"

ByteRange::ByteRange(const char *attributeList) {
  const char *attribute = attributeList;

  // length of sub-range
  const char *attributeEnd = strchr(attribute, ':');
  if (attributeEnd == nullptr) {
    throw std::runtime_error("STREAM-INF attribute has no value");
  }

  attribute = ++attributeEnd; // skip ':'
  lengthSubRange = getUnsignedLong(attribute);

  // start of sub-range (optional)
  attributeEnd = strchr(attribute, '@');

  if (attributeEnd != nullptr) {
    attribute = ++attributeEnd; // skip '@'
    startSubRange = getUnsignedLong(attribute);
  }
}