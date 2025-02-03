#include <algorithm>
#include <iostream>

#include "parse.h"
#include "playlist.h"

void help() {
  std::cout << "Usage: hls_parse_example [OPTION]... [FILE]\n"
            << "Parse HLS playlist FILE and sort EXT-X-STREAM-INF tags by "
               "BANDWIDTH attribute value.\n\n"
            << "  -h, --help        print help\n";
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    help();
    return EXIT_FAILURE;
  }

  int fileNameIndex = 1;

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    help();
    return EXIT_SUCCESS;
  }

  try {
    Parse parse;
    Playlist pl(argv[fileNameIndex]);

    // make sure this is an HLS playlist
    pl.readLine();
    parse.input((char *)pl);
    if (parse.EXTM3UPresent() == false) {
      std::cerr << "EXTM3U tag not first line of playlist.\n";
      return EXIT_FAILURE;
    }

    // read the playlist and parse each line
    while (!pl.eof()) {
      pl.readLine();
      parse.input((char *)pl);
    }
    parse.printStreamInf();

  } catch (std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }
}