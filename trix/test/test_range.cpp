#include <gtest/gtest.h>

#include <trix/ranges.hpp>
using namespace trix;

#include <vector>

TEST(Range,Enumerate) {
  std::vector<uint32_t> arr{1,2,3,4};

  for( auto [i,v] : Enumerate(arr) ) {
    EXPECT_EQ( i+1, v );
    v+=1;
  }

  // Modified above to verify value by ref here
  for( auto [i,v] : Enumerate(arr) ) {
    EXPECT_EQ( i+2, v );
  }
}

TEST(Range,Bounds) {

  Bounds bounds{1,10};

  EXPECT_EQ( 1,  bounds.first );
  EXPECT_EQ( 10, bounds.last );
  EXPECT_EQ( 10, bounds.size() );

  EXPECT_EQ( 1,  bounds[-1] );
  EXPECT_EQ( 1,  bounds[0] );
  EXPECT_EQ( 5,  bounds[4] );
  EXPECT_EQ( 9,  bounds[8] );
  EXPECT_EQ( 10, bounds[9] );
  EXPECT_EQ( 10, bounds[42] );
  

  EXPECT_EQ( false, bounds == -42 );
  EXPECT_EQ( false, bounds == 0 );
  EXPECT_EQ( true,  bounds  == 1 );
  EXPECT_EQ( true,  bounds  == 5 );
  EXPECT_EQ( true,  bounds  == 10 );
  EXPECT_EQ( false, bounds == 11 );
  
  EXPECT_EQ( 1,  bounds(-17) );
  EXPECT_EQ( 1,  bounds(0) );
  EXPECT_EQ( 1,  bounds(1) );
  EXPECT_EQ( 5,  bounds(5) );
  EXPECT_EQ( 9,  bounds(9) );
  EXPECT_EQ( 10, bounds(10) );
  EXPECT_EQ( 10, bounds(42) );

  Bounds width(100);

  EXPECT_EQ( 100, width.size() );
  EXPECT_EQ( 0, width.first );
  EXPECT_EQ( 99, width.last );
}

TEST(Range,Basic) {
  Range range(2U);

  EXPECT_EQ( 0U, *range.begin() );
  EXPECT_EQ( 2U, *range.end() );

  EXPECT_EQ( 2, range.size() );

  size_t count=0U;

  // Can't have step 0!
  EXPECT_THROW( Range(0U,1U,0U), std::runtime_error );

  for( auto i : Range(0U,10U) ) {
    std::ignore = i;
    count++;
  }

  EXPECT_EQ( 10U, count );

  count = 0; // Empty range!
  for( auto i : Range(0U,0U) ) {
    std::ignore = i;
    count++;
  }

  EXPECT_EQ( 0U, count );
}

TEST(Range,Iter) {
  Range<> five(0,5);
  
  auto it = five.begin();
  EXPECT_EQ( 0, *it );
  EXPECT_NE( five.end(), it ); ++it;
  EXPECT_EQ( 1, *it );
  EXPECT_NE( five.end(), it ); ++it;
  EXPECT_EQ( 2, *it );
  EXPECT_NE( five.end(), it ); ++it;
  EXPECT_EQ( 3, *it );
  EXPECT_NE( five.end(), it ); ++it;
  EXPECT_EQ( 4, *it );
  EXPECT_NE( five.end(), it ); ++it;
  EXPECT_EQ( 5, *it );
  EXPECT_EQ( five.end(), it );
 
}

TEST(Range,Signed) {
  Range<int> range(-1,2);

  EXPECT_EQ( -1, *range.begin() );
  EXPECT_EQ( 2, *range.end() );

  size_t count=0U;

  // Can't have step 0!
  EXPECT_THROW( Range(0U,1U,0U), std::runtime_error );

  for( auto i : Range(0,10) ) {
    std::ignore = i;
    count++;
  }
  EXPECT_EQ( 10U, count );

  count = 0; // Empty range!
  for( auto i : Range<int16_t>(-1,1) ) {
    std::ignore = i;
    count++;
  }
  EXPECT_EQ( 2U, count );

  count = 0; // Empty range!
  for( auto i : Range(-1,-1) ) {
    std::ignore = i;
    count++;
  }
  EXPECT_EQ( 0U, count );
}

using U64Range2 = Range2<>;

TEST(Range2,Basic) {
  U64Range2 range({0U,0U},{1U,1U});

  {
    auto [x,y] = *range.begin();
    
    EXPECT_EQ( 0U, x );
    EXPECT_EQ( 0U, y );
  }

  {
    auto [x,y] = *range.end();
    EXPECT_EQ( 1U, x );
    EXPECT_EQ( 1U, y );
  }

  auto it = range.begin();

  EXPECT_NE( it, range.end() );

  ++it;
  EXPECT_EQ( it, range.end() );
  ++it;
  EXPECT_EQ( it, range.end() );

  size_t count = 0U;

  for( auto ab : U64Range2({0,0},{5,5}) ) {
    std::ignore = ab;
    ++count;
  }

  EXPECT_EQ( 25, count );

  count = 0;
  for( auto [a,b] : U64Range2({0,0},{10,1}) ) {
    std::ignore = a;
    std::ignore = b;
    ++count;
  }
  EXPECT_EQ( 10, count );

  // Can't have step 0!
  EXPECT_THROW( U64Range2({0,0},{10,1},{2,0}), std::runtime_error );
  EXPECT_THROW( U64Range2({0,0},{10,1},{0,2}), std::runtime_error );

  count = 0;
  for( auto ab : U64Range2({0,0},{10,1},{2,2}) ) {
    std::ignore = ab;
    ++count;
  }
 
  EXPECT_EQ( 5, count );

  count = 0;  // Legal empty range
  for( auto ab : U64Range2({0,0},{0,0},{2,2}) ) {
    std::ignore = ab;
    ++count;
  }
  EXPECT_EQ( 0, count );

  count = 0;  // Legal empty range!
  for( auto ab : U64Range2({0,0},{0,1},{2,2}) ) {
    std::ignore = ab;
    ++count;
  }
  EXPECT_EQ( 0, count );

  count = 0;  // Legal empty range!
  for( auto ab : U64Range2({5,5},{6,5},{2,2}) ) {
    std::ignore = ab;
    ++count;
  }
  EXPECT_EQ( 0, count );
}

TEST(Range2,Compact) {
  Range2 grid3(3,3);

  Range2<>::value_type t33(3,3);

  EXPECT_EQ( t33, grid3.size() );
  
  int count=0;

  for( auto [a,b] : grid3 ) {
    std::ignore = a;
    std::ignore = b;
    ++count;
  }

  EXPECT_EQ( 9, count );
  
  
}
