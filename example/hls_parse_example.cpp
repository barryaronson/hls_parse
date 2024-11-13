#include <iostream>

#include "parse.h"
#include "playlist.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }

  Parse parse;
  Playlist pl(argv[1]);
  pl.readLine();
  parse.input((char *)pl);
  if (parse.EXTM3UPresent() == false) {
    std::cerr << "EXTM3U tag not first line of playlist.\n";
    return EXIT_FAILURE;
  }

  while (!pl.eof()) {
    pl.readLine();
    std::cout << (char *)pl << std::endl;
    parse.input((char *)pl);
  }
}