#include "playlist.h"
#include "gtest/gtest.h"

namespace {

class PlaylistFile : public ::testing::Test {
protected:
  std::string tempFilename = "temp_test_file.txt";

  void SetUp() override { tempFilename; }
  void TearDown() override { std::remove(tempFilename.c_str()); }
};

/*
Test capability to expand input buffer if it is too small for the length of the
line being read.
*/
TEST_F(PlaylistFile, BufferExpansion) {
  std::ofstream outfile(tempFilename);

  ASSERT_TRUE(outfile.is_open());
  std::string line =
      "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  outfile << line << std::endl;
  outfile.close();

  Playlist pl(tempFilename.c_str(),
              16); // 16 for a buffer size is too small for length of 'line'
  std::string read = pl.readLine();

  EXPECT_EQ(line, read);
}

/*
Test that continued lines (using '\') are properly concatenated.
*/
TEST_F(PlaylistFile, LineContinuation) {
  // output to a file a continued line
  std::ofstream outfile(tempFilename);
  ASSERT_TRUE(outfile.is_open());
  std::string line = "0123456789ABCDEF";
  outfile << line << '\\' << std::endl;
  outfile << line << '\\' << std::endl;
  outfile << line << std::endl;
  outfile.close();

  // read from the file
  Playlist pl(tempFilename.c_str());
  std::string read = pl.readLine();
  std::string lineShouldNowBe = line + line + line;

  // test that the continued line was concatenated
  EXPECT_EQ(lineShouldNowBe, read);
}

/*
Test that lines with trailing space are properly cleaned up.
*/
TEST_F(PlaylistFile, LineWithTrailingSpace) {
  // make a file with a single line with trailing spaces
  std::ofstream outfile(tempFilename);
  ASSERT_TRUE(outfile.is_open());
  std::string lineShouldBe =
      "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  std::string lineWithTrailingSpace = lineShouldBe + "  ";
  outfile << lineWithTrailingSpace << std::endl;
  outfile.close();

  // read the same line from the file
  Playlist pl(tempFilename.c_str());
  std::string read = pl.readLine();

  // test that the trailing spaces have be removed
  EXPECT_EQ(lineShouldBe, read);
}

/*
Test that lines with a carriage return (CR or '\r') are properly cleaned up.
*/
TEST_F(PlaylistFile, LineWithCR) {
  // make a file with a single line with trailing spaces
  std::ofstream outfile(tempFilename);
  ASSERT_TRUE(outfile.is_open());
  std::string lineShouldBe =
      "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  std::string lineWithTrailingSpace = lineShouldBe + "  ";
  outfile << lineWithTrailingSpace << '\r' << std::endl;
  outfile.close();

  // read the same line from the file
  Playlist pl(tempFilename.c_str());
  std::string read = pl.readLine();

  // test that the carriage return has been removed
  EXPECT_EQ(lineShouldBe, read);
}

/*
Test reading multiple lines.
*/
TEST_F(PlaylistFile, MultipleLines) {
  // create multiple, different lines
  std::string hexChars = "0123456789ABCDEF";
  std::string line1 = hexChars;
  std::string line2 = line1 + hexChars;
  std::string line3 = line2 + hexChars;
  std::string line4 = line3 + hexChars;

  // write the lines to a file
  std::ofstream outfile(tempFilename);
  ASSERT_TRUE(outfile.is_open());
  outfile << line1 << std::endl;
  outfile << line2 << std::endl;
  outfile << line3 << std::endl;
  outfile << line4 << std::endl;
  outfile.close();

  // read each line and check against the original
  Playlist pl(tempFilename.c_str());
  EXPECT_EQ(line1, pl.readLine());
  EXPECT_EQ(line2, pl.readLine());
  EXPECT_EQ(line3, pl.readLine());
  EXPECT_EQ(line4, pl.readLine());
}

} // namespace