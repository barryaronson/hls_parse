#include <iostream>

#include "byterange.h"

ByteRange::ByteRange(const char *attributeList) {
    std::cout << "BYTERANGE = " << attributeList << std::endl;
    const char *attribute = attributeList;
    while (*attribute) {
        const char *attributeEnd = strchr(attribute, ':');
        if (attributeEnd == nullptr) {
            throw std::runtime_error("STREAM-INF attribute has no value");
        }
        attribute = ++attributeEnd; // skip ':'
        unsigned long long lengthSubRange = getUnsignedLong(attribute);
    }
    // #EXT-X-BYTERANGE:82112@752321
}