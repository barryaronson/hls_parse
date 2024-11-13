#include "parse.h"
#include "gtest/gtest.h"

namespace {

/*
Parse a simple pseudo HLS line with a tag and its attributes
*/
TEST(Parse, Basic) {
  const char *line =
      "#EXT-X-STREAM-INF:BANDWIDTH=2483789,AVERAGE-BANDWIDTH=1762745,CODECS="
      "\"mp4a.40.2,hvc1.2.4.L90.90\",RESOLUTION=960x540,FRAME-RATE=23.97,VIDEO-"
      "RANGE=PQ,AUDIO=\"aac-128k\",CLOSED-CAPTIONS=NONE";
  Parse parse;
  parse.input(line);
}

} // namespace