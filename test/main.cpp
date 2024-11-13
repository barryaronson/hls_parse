#include <iostream>

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);

  if (argc > 1 && strcmp(argv[1], "--help") == 0) {
    std::cout << "Future help message.\n";
    return EXIT_SUCCESS;
  }

  return RUN_ALL_TESTS();
}
