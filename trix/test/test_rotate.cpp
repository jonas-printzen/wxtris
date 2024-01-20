#include <gtest/gtest.h>

#include <trix/rotate.hpp>
using namespace trix;

TEST( Rotate, 4by4 ) {
  int x=0,y=0;

  // No rotation
  std::tie(x,y) = Rotate<4>( {0,0}, SOUTH );
  EXPECT_EQ( 0, x );
  EXPECT_EQ( 0, y );

  std::tie(x,y) = Rotate<4>( {1,2}, SOUTH );
  EXPECT_EQ( 1, x );
  EXPECT_EQ( 2, y );

  // Both axis mirrored
  std::tie(x,y) = Rotate<4>( {0,0}, NORTH );
  EXPECT_EQ( 3, x );
  EXPECT_EQ( 3, y );

  std::tie(x,y) = Rotate<4>( {3,0}, NORTH );
  EXPECT_EQ( 0, x );
  EXPECT_EQ( 3, y );

  // Both axis mirrored
  std::tie(x,y) = Rotate<4>( {0,0}, EAST );
  EXPECT_EQ( 3, x );
  EXPECT_EQ( 0, y );

  std::tie(x,y) = Rotate<4>( {3,0}, EAST );
  EXPECT_EQ( 3, x );
  EXPECT_EQ( 3, y );

  std::tie(x,y) = Rotate<4>( {1,2}, EAST );
  EXPECT_EQ( 1, x );
  EXPECT_EQ( 1, y );

  std::tie(x,y) = Rotate<4>( {1,2}, WEST );
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 2, y );
}


TEST( Rotate, 3by3 ) {
  int x=0, y=0;

  // No rotation
  std::tie(x,y) = Rotate<3>( {0,0}, SOUTH );
  EXPECT_EQ( 0, x );
  EXPECT_EQ( 0, y );

  std::tie(x,y) = Rotate<3>( {1,2}, SOUTH );
  EXPECT_EQ( 1, x );
  EXPECT_EQ( 2, y );

  // Both axis mirrored
  std::tie(x,y) = Rotate<3>( {0,0}, NORTH );
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 2, y );

  std::tie(x,y) = Rotate<3>( {2,0}, NORTH );
  EXPECT_EQ( 0, x );
  EXPECT_EQ( 2, y );

  // Both axis mirrored
  std::tie(x,y) = Rotate<3>( {0,0}, EAST );
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 0, y );

  std::tie(x,y) = Rotate<3>( {2,0}, EAST );
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 2, y );

  std::tie(x,y) = Rotate<3>( {1,2}, EAST );
  EXPECT_EQ( 0, x );
  EXPECT_EQ( 1, y );

  std::tie(x,y) = Rotate<3>( {1,2}, WEST );
  EXPECT_EQ( 2, x );
  EXPECT_EQ( 1, y );
}
