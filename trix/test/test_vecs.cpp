#include <gtest/gtest.h>

#define TRIX_TEST

#include <trix/vecs.hpp>
using namespace trix;

TEST( Vecs, Basic) {
  EXPECT_EQ( 2, sizeof(MatI::coord_t)  );

  MatI m3(3,3);

  EXPECT_NO_THROW( m3.acol(0) );
  EXPECT_NO_THROW( m3.acol(1) );
  EXPECT_NO_THROW( m3.acol(2) );
  EXPECT_THROW( m3.acol(3), std::out_of_range );
  EXPECT_THROW( m3.acol(-1), std::out_of_range );
  EXPECT_NO_THROW( m3.arow(0) );
  EXPECT_NO_THROW( m3.arow(1) );
  EXPECT_NO_THROW( m3.arow(2) );
  EXPECT_THROW( m3.arow(3), std::out_of_range );
  EXPECT_THROW( m3.arow(-1), std::out_of_range );

  EXPECT_EQ( 9, m3._cells.size() );
  EXPECT_EQ( 0, m3(0,0) );

  auto range = m3.range();
  EXPECT_EQ( 3, std::get<0>(range.size()) );
  EXPECT_EQ( 3, std::get<1>(range.size()) );

  for( auto&[col,row] : m3.range() ) {
    m3[{col,row}] = row*100 + col;
  }

  EXPECT_EQ( 0, m3(0,0) );
  EXPECT_EQ( 1, m3(1,0) );
  EXPECT_EQ( 2, m3(2,0) );
  EXPECT_EQ( 100, m3(0,1) );
  EXPECT_EQ( 102, m3(2,1) );
  EXPECT_EQ( 202, m3(2,2) );
}


