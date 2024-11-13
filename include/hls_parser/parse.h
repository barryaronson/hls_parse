#pragma once

#include "streaminfo.h"

class Parse {
public:
  ~Parse() {
    if (lastStreamInfo) {
      delete lastStreamInfo;
    }
  }
  void input(const char *line);
  bool EXTM3UPresent() { return EXTM3U; }

private:
  bool EXTM3U = false;
  bool associateNextLine = false;
  static constexpr int tagIdentLen = 4;
  static constexpr const char *tagIdent = "#EXT";
  StreamInfo *lastStreamInfo = nullptr;
  int version = 1;

  const char *isTag(const char *line) {
    return (strncmp(line, tagIdent, tagIdentLen) == 0) ? line + tagIdentLen
                                                       : nullptr;
  }

  const char *compareTag(const char *input, const char *tag) {
    return compareIdentifier(input, tag, TagSep);
  }

  bool processExtXTag(const char *extXTag);
};
