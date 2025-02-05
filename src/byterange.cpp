#include <cstring>
#include <iostream>

#include "byterange.h"

ByteRange::ByteRange(const char *attribute) {
  std::cout << __FILE__ << '@' << __LINE__ << ": BYTERANGE attribute = " << attribute << std::endl;

  lengthSubRange = getUnsignedLong(attribute); // length of sub-range

  if ((attribute = strchr(attribute, '@')) != nullptr) { // start of sub-range (optional)
    startSubRange = getUnsignedLong(++attribute); // skip '@'
  }
}