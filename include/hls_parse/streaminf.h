#pragma once

#include <cstring>
#include <iostream>

#include "tag.h"

class StreamInf : public Tag {
public:
  StreamInf(const char *attributeList);
  enum HDCPLevel { TYPE_0, TYPE_1, NONE };
  enum VideoRange { SDR, HLG, PQ };
  const char *getHDCPLevel(const char *attribute);
  const char *getVideoRange(const char *attribute);
  const std::string &getURI() const { return uri; }
  void setURI(const char *assetURI) { uri = assetURI; }

  // private:
  std::string uri;
  unsigned long bandwidth = 0;
  unsigned long averageBandwidth = 0;
  double score = 0.0;
  std::string codecs;
  std::string supplementalCodecs;
  std::string resolution;
  double frameRate = 0.0;
  HDCPLevel hdcpLevel = NONE;
  std::string allowedCPC;
  VideoRange videoRange;
  std::string reqVideoLayout;
  std::string stableVariantID;
  std::string audio;
  std::string video;
  std::string subtitles;
  std::string closedCaptions;
  std::string pathwayID;
};