#include <gtest/gtest.h>

#include "./utils/test_utils.cxx"
#include "./utils/test_math.cxx"

#include "./mesh/test_mesh.cxx"
#include "./ChessGame/test_chessgame.cxx"

int main(int argc, char **argv) {::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
