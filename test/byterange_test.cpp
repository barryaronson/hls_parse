#include "byterange.h"
#include "gtest/gtest.h"

namespace {

class ByteRangeTest : public ::testing::Test {
protected:
  void SetUp() override { }
  void TearDown() override { }
};

/*
Test capability to expand input buffer if it is too small for the length of the
line being read.
*/
TEST_F(ByteRangeTest, ProcessFullTag) {

  ASSERT_TRUE(outfile.is_open());
  std::string line = "#EXT-X-BYTERANGE:82112@752321";

  ByteRange br(line.c_str());

  EXPECT_EQ(br.lengthSubRange, 82112);
  EXPECT_EQ(br.startSubRange, 752321);
}

} // namespace