#include <cassert>
#include <iostream>

#include "parse.h"
#include "playlist.h"

bool Parse::processExtXTag(const char *extXTag) {
  const char *attributeList = nullptr;

  switch (*extXTag) {
  case 'B':
    if ((attributeList = compareTag(extXTag, "BYTERANGE")) != nullptr) {
      // todo std::cout << "BYTERANGE = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'D':
    if ((attributeList = compareTag(extXTag, "DATERANGE")) != nullptr) {
      // todo std::cout << "DATERANGE = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "DISCONTINUITY")) ==
               nullptr) { // no attributes
      // todo std::cout << "DISCONTINUITY = " << attributeList << std::endl;
    } else if ((attributeList =
                    compareTag(extXTag, "DISCONTINUITY-SEQUENCE")) != nullptr) {
      // todo std::cout << "DISCONTINUITY-SEQUENCE = " << attributeList <<
      // std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'E':
    if ((attributeList = compareTag(extXTag, "ENDLIST")) == nullptr) {
      // todo std::cout << "ENDLIST = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'I':
    if ((attributeList = compareTag(extXTag, "I-FRAME-STREAM-INF")) !=
        nullptr) {
      // todo std::cout << "I-FRAME-STREAM-INF = " << attributeList <<
      // std::endl;
    } else if ((attributeList = compareTag(extXTag, "I-FRAMES-ONLY")) ==
               nullptr) {
      // todo std::cout << "I-FRAMES-ONLY" << std::endl;
    } else if ((attributeList = compareTag(extXTag, "INDEPENDENT-SEGMENTS")) ==
               nullptr) { // no attributes
      // todo std::cout << "INDEPENDENT-SEGMENTS" << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'K':
    if ((attributeList = compareTag(extXTag, "KEY")) != nullptr) {
      // todo std::cout << "KEY = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'M':
    if ((attributeList = compareTag(extXTag, "MAP")) != nullptr) {
      // todo std::cout << "MAP = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "MEDIA")) != nullptr) {
      // todo std::cout << "MEDIA = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "MEDIA-SEQUENCE")) !=
               nullptr) {
      // todo std::cout << "MEDIA-SEQUENCE = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'P':
    if ((attributeList = compareTag(extXTag, "PLAYLIST-TYPE")) != nullptr) {
      // todo std::cout << "PLAYLIST-TYPE" << std::endl;
    } else if ((attributeList = compareTag(extXTag, "PROGRAM-DATE-TIME")) !=
               nullptr) {
      // todo std::cout << "PROGRAM-DATE-TIME = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'S':
    if ((attributeList = compareTag(extXTag, "STREAM-INF")) != nullptr) {
      StreamInf *si = lastStreamInf = new StreamInf(attributeList);
      streamInfList.push_back(si);
      return true;
    } else if ((attributeList = compareTag(extXTag, "SESSION-DATA")) !=
               nullptr) {
      // todo std::cout << "SESSION-DATA = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "SESSION-KEY")) !=
               nullptr) {
      // todo std::cout << "SESSION-KEY = " << attributeList << std::endl;
    } else if ((attributeList = compareTag(extXTag, "START")) != nullptr) {
      // todo std::cout << "START = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'T':
    if ((attributeList = compareTag(extXTag, "TARGETDURATION")) != nullptr) {
      // todo std::cout << "TARGETDURATION = " << attributeList << std::endl;
    } else {
      goto tagError;
    }
    break;
  case 'V':
    if ((attributeList = compareTag(extXTag, "VERSION")) != nullptr) {
      // todo std::cout << "VERSION = " << attributeList << std::endl;
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
    lastStreamInf->uri = tagLine;
    associateNextLine = false;
    lastStreamInf = nullptr;
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
    }
    break;
  case 'I':
    if (*++line == 'N' && *++line == 'F') {
      // todo std::cout << "INF tag\n";
    }
    break;
  }
}