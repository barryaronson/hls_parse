#include <iostream>

#include "byterange.h"

ByteRange::ByteRange(const char *attributeList) {
    std::cout << "BYTERANGE = " << attributeList << std::endl;
    const char *attribute = attributeList;

    // length of sub-range
    const char *attributeEnd = strchr(attribute, ':');
    if (attributeEnd == nullptr) {
        throw std::runtime_error("STREAM-INF attribute has no value");
    }
    lengthSubRange = getUnsignedLong(attribute);
    attribute = ++attributeEnd; // skip ':'

    // start of sub-range (optional)
    if ((attribute = strchr(attributeEnd, '@')) == nullptr) {
        ++attribute; // skip '@'
        startSubRange = getUnsignedLong(attribute);
    }
}