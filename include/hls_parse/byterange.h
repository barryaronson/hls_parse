#pragma once

#include "tag.h"

/*! \class ByteRange
    \brief Parses the attributes associated with a BYTERANGE tag.
    \details Identifies each attribute and stores its value.
*/
class ByteRange : public Tag {
public:
  ByteRange(const char *attribute);

  unsigned long long lengthSubRange = 0;
  unsigned long long startSubRange = 0;
};