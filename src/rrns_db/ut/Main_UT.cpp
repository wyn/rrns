#include "gmock/gmock.h"
#include "glog/logging.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  ::google::InitGoogleLogging(argv[0]);

  return RUN_ALL_TESTS();
}
