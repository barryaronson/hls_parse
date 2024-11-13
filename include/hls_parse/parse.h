#pragma once

#include <vector>

#include "streaminf.h"

/*! \class Parse
    \brief Parses a single line from an HLS playlist.
    \details Identifies the tag and sends the associated attributes to the
   appropriate tag class for processing.
*/
class Parse {
public:
  void input(const char *line);
  bool EXTM3UPresent() { return EXTM3U; }
  std::vector<StreamInf *> streamInfList;

private:
  bool EXTM3U = false;
  bool associateNextLine = false;
  static constexpr int tagIdentLen = 4;
  static constexpr const char *tagIdent = "#EXT";
  StreamInf *lastStreamInf = nullptr;
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
