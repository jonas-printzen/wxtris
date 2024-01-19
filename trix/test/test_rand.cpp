#include <gtest/gtest.h>

#include <trix/rand.hpp>
using namespace trix;

TEST( Rand, Basic ) {
  float f = Random::uniform();
  EXPECT_TRUE( 0.0 <= f );
  EXPECT_TRUE( 1.0 >= f );
}
