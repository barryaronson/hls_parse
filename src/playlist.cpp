#include <curl/curl.h>
#include <filesystem>

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

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

std::string createFileFromURL(const char *url, const char *path) {
    std::filesystem::path urlPath = url;

    if (urlPath.extension() != ".m3u8") {
        throw std::runtime_error("Not an m3u8 file");
    }

    // return `url` unchanged if it doesn't point to a web server
    const auto urlBegin = urlPath.begin();
    if (!(*urlBegin == "https:" || *urlBegin == "http:")) {
        return url;
    }

    // otherwise, fetch the `url` and save it as a file

    // create the output file name and path
    std::filesystem::path filePath = path;
    filePath += '/';
    filePath += urlPath.filename();

    // create the output file
    FILE *fp = fopen(filePath.c_str(), "w");
    if (fp == nullptr) {
        throw std::runtime_error("Error creating output file");
    }

    // download the file
    CURL *curl = curl_easy_init(); // TODO: curl_global_init
    if (curl == nullptr) {
        filePath = "";
    } else {
        if (curl_easy_setopt(curl, CURLOPT_URL, url) != CURLE_OK ||
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data) != CURLE_OK ||
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp) != CURLE_OK ||
            curl_easy_perform(curl) != CURLE_OK) { // download the .m3u8 file
            filePath = "";
        }
        curl_easy_cleanup(curl);
    }

    fclose(fp);

    if (filePath == "") {
        throw std::runtime_error("curl error");
    }

    return filePath; // prexisting file or newly created file from download
}
