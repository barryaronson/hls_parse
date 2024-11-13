#include <algorithm>
#include <iostream>

#include "parse.h"
#include "playlist.h"

class ParseUtility : public Parse {
public:
  void printStreamInf();
  void sortStreamInfByBandwidth(bool ascending = true);
};

void ParseUtility::printStreamInf() {
  for (auto si : streamInfList) {
    std::cout << "#EXT-X-STREAM-INF: " << "BANDWIDTH = " << si->bandwidth
              << std::endl;
  }
}

void ParseUtility::sortStreamInfByBandwidth(bool ascending) {
  std::function<bool(StreamInf *, StreamInf *)> bandwidthComp;

  if (ascending) {
    bandwidthComp = [](StreamInf *a, StreamInf *b) {
      return a->bandwidth < b->bandwidth;
    };
  } else {
    bandwidthComp = [](StreamInf *a, StreamInf *b) {
      return a->bandwidth > b->bandwidth;
    };
  }

  std::sort(streamInfList.begin(), streamInfList.end(), bandwidthComp);
}

void help() {
  std::cout << "Usage: hls_parse_example [OPTION]... [FILE]\n"
            << "Parse HLS playlist FILE and sort EXT-X-STREAM-INF tags by "
               "BANDWIDTH attribute value.\n\n"
            << "  -r, --reverse     sort by descending order\n"
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

  bool ascending = true;
  if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--reverse") == 0) {
    ascending = false;
    fileNameIndex = 2;
  }

  try {
    ParseUtility parse;
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

    parse.sortStreamInfByBandwidth(ascending);
    parse.printStreamInf();

  } catch (std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
  }
}