#pragma once

#include "tag.h"

/*! \class ByteRange
    \brief Parses the attributes associated with a BYTERANGE tag.
    \details Identifies each attribute and stores its value.
*/
class ByteRange : public Tag {
public:
  ByteRange(const char *attributeList);

    unsigned long long lengthSubRange;
    unsigned long long startSubRange;
};