
#include "playlist.h"

Playlist::Playlist(const char *fileName, size_t initialBufferSize)
    : std::ifstream(fileName), readBufferSize(initialBufferSize) {
  if (is_open() != true) { // make sure playlist got opened
    throw std::runtime_error("Could not open input file.");
  }

  readBuffer = new char[readBufferSize]; // set up read buffer
}

Playlist::~Playlist() { delete readBuffer; }

std::string Playlist::readLine() {
  std::streampos position;
  int offset = 0;

  do {
    // read line and check to make sure buffer was big enough (-1 accommodates
    // for null character)
    while ((position = getline(readBuffer + offset, readBufferSize).gcount()) ==
           readBufferSize - 1) {

      // buffer was too small; double its size
      delete readBuffer;
      readBufferSize *= 2;
      readBuffer = new char[readBufferSize];

      // clean up everything for second try with larger buffer
      clear();
      seekg(-position, ios_base::cur);
    }

    // remove whitespace at end of line
    offset += static_cast<int>(position) -
              2; // converting count to offset and account for LF
    while (std::isspace(*(readBuffer + offset))) {
      --offset;
    }

    // handle line continuations
    if (*(readBuffer + offset) == '\\') { // line continuation exists
      continue; // next call to 'getline()' will overwrite '\'
    } else {
      *(readBuffer + offset + 1) = '\0'; // terminate line
      break;                             // finished reading line; go to return
    }
  } while (1);

  return std::string(readBuffer);
}