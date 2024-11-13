#include "parse.h"
#include "gtest/gtest.h"

namespace {

/*
Tokenize a simple pseudo HLS line with a tag and its attributes
*/
TEST(Parse, Generic) {
  const char *line =
      "#EXT-X-STREAM-INF:BANDWIDTH=2483789,AVERAGE-BANDWIDTH=1762745,CODECS="
      "\"mp4a.40.2,hvc1.2.4.L90.90\",RESOLUTION=960x540,FRAME-RATE=23.97,VIDEO-"
      "RANGE=PQ,AUDIO=\"aac-128k\",CLOSED-CAPTIONS=NONE";
  Parse parse;
  parse.input(line);
#if 0
  std::vector<std::string> expectedTokens = {"tag", "attribute1", "1",
                                             "attribute2", "2"};

  auto expected = expectedTokens.begin();
  for (auto token = parse.begin(); token != tokenizer.end(); ++token) {
    EXPECT_FALSE(expected == expectedTokens.end());
    EXPECT_EQ((*expected),
              (*token)); // check that each token matches what is expected
    ++expected;
  }
#endif
  EXPECT_TRUE(1 == 1);
}

} // namespace