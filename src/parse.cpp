#include <cassert>
#include <iostream>

#include "parse.h"
#include "playlist.h"

bool Parse::processExtXTag(const char *extXTag) {
  const char *attributeList = nullptr;

  switch (*extXTag) {
  case 'B':
    if ((attributeList = compareTag(extXTag, "BYTERANGE")) != nullptr) {
      std::cout << "BYTERANGE = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'D':
    if ((attributeList = compareTag(extXTag, "DATERANGE")) != nullptr) {
      std::cout << "DATERANGE = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "DISCONTINUITY")) ==
               nullptr) { // no attributes
      std::cout << "DISCONTINUITY = " << attributeList << std::endl;
    } else if ((attributeList =
                    compareTag(extXTag, "DISCONTINUITY-SEQUENCE")) != nullptr) {
      std::cout << "DISCONTINUITY-SEQUENCE = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'E':
    if ((attributeList = compareTag(extXTag, "ENDLIST")) == nullptr) {
      std::cout << "ENDLIST = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'I':
    if ((attributeList = compareTag(extXTag, "I-FRAME-STREAM-INF")) !=
        nullptr) {
      std::cout << "I-FRAME-STREAM-INF = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "I-FRAMES-ONLY")) ==
               nullptr) {
      std::cout << "I-FRAMES-ONLY" << std::endl;
    } else if ((attributeList = compareTag(extXTag, "INDEPENDENT-SEGMENTS")) ==
               nullptr) { // no attributes
      std::cout << "INDEPENDENT-SEGMENTS" << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'K':
    if ((attributeList = compareTag(extXTag, "KEY")) != nullptr) {
      std::cout << "KEY = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'M':
    if ((attributeList = compareTag(extXTag, "MAP")) != nullptr) {
      std::cout << "MAP = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "MEDIA")) != nullptr) {
      std::cout << "MEDIA = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "MEDIA-SEQUENCE")) !=
               nullptr) {
      std::cout << "MEDIA-SEQUENCE = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'P':
    if ((attributeList = compareTag(extXTag, "PLAYLIST-TYPE")) != nullptr) {
      std::cout << "PLAYLIST-TYPE" << std::endl;
    } else if ((attributeList = compareTag(extXTag, "PROGRAM-DATE-TIME")) !=
               nullptr) {
      std::cout << "PROGRAM-DATE-TIME = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'S':
    if ((attributeList = compareTag(extXTag, "STREAM-INF")) != nullptr) {
      if (lastStreamInfo) {
        delete lastStreamInfo;
      }
      StreamInfo *si = lastStreamInfo = new StreamInfo(attributeList);
      return true;
    } else if ((attributeList = compareTag(extXTag, "SESSION-DATA")) !=
               nullptr) {
      std::cout << "SESSION-DATA = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "SESSION-KEY")) !=
               nullptr) {
      std::cout << "SESSION-KEY = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "START")) != nullptr) {
      std::cout << "START = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'T':
    if ((attributeList = compareTag(extXTag, "TARGETDURATION")) != nullptr) {
      std::cout << "TARGETDURATION = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'V':
    if ((attributeList = compareTag(extXTag, "VERSION")) != nullptr) {
      std::cout << "VERSION = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  tagError:
  default:
    throw std::runtime_error("Bad tag.");
  }

  return false;
}

void Parse::input(const char *tagLine) {
  assert(tagLine);

  if (*tagLine == '\0') { // skip blank lines
    return;
  }

  if (associateNextLine) {
    lastStreamInfo->uri = tagLine;
    associateNextLine = false;
    lastStreamInfo = nullptr;
    return;
  }

  const char *line = isTag(tagLine);
  if (line == nullptr) {
    throw std::runtime_error("Not a tag.");
  }

  switch (*line) {
  case '-':
    if (*++line == 'X' && *++line == '-') {
      associateNextLine = processExtXTag(++line);
    }
    break;
  case 'M':
    if (*++line == '3' && *++line == 'U') {
      EXTM3U = true;
      std::cout << "M3U tag\n";
    }
    break;
  case 'I':
    if (*++line == 'N' && *++line == 'F') {
      std::cout << "INF tag\n";
    }
    break;
  }
}