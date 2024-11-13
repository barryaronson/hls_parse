#pragma once

#include <cstring>
#include <iostream>

#include "tag.h"

class StreamInfo : public Tag {
public:
  StreamInfo(const char *attributeList);
  enum HDCPLevel { TYPE_0, TYPE_1, NONE };
  const char *getHDCPLevel(const char *attribute);
  const std::string &getURI() const { return uri; }
  void setURI(const char *assetURI) { uri = assetURI; }

private:
  std::string uri;
  HDCPLevel hdcpLevel = NONE;
};