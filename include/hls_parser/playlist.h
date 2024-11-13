#pragma once

#include <fstream>

/*! \class Playlist
    \brief Reads an HLS playlist from a file.
    \details Opens an HLS playlist for parsing and does basic cleanup such as
    concatenation of continued lines.
*/
class Playlist : public std::ifstream {
public:
  Playlist(const char *fileName, size_t initialBufferSize = 512);
  ~Playlist();
  /*! \brief Reads the current line from the playlist and advances to next line.
      \return The current line in the playlist
      \details All lines continued with a `\` are concatenated into a single
      line with the `\` removed. Trailing whitespace and the CR (if present) and
      LF are removed.
  */
  std::string readLine();
  operator const char *() const { return readBuffer; };
  operator char *() const { return readBuffer; };

private:
  size_t readBufferSize;
  char *readBuffer;
  std::ifstream hlsFile;
};