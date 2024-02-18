#include <gtest/gtest.h>

#define TRIX_TEST

#include <trix/tetro.hpp>
using namespace trix;

TEST(Tetro,Point) {
  point_t p{1,1};

  p.rot( WEST ); // dim=3
  // At center, no change
  EXPECT_EQ( 1, p.x );  EXPECT_EQ( 1, p.y );

  p.rot( NORTH, 4 );
  EXPECT_EQ( 2, p.x );  EXPECT_EQ( 2, p.y );

  p = point_t{1,2};
  p.rot( NORTH );
  EXPECT_EQ( 1, p.x );  EXPECT_EQ( 0, p.y );

  // Return to original
  p.rot( SOUTH, NORTH );
  EXPECT_EQ( 1, p.x );  EXPECT_EQ( 2, p.y );
  
  p = point_t{0,0};

  p.rot( EAST, 4 );
  EXPECT_EQ( 3, p.x );  EXPECT_EQ( 0, p.y );

  p.rot( EAST, 4 );
  EXPECT_EQ( 3, p.x );  EXPECT_EQ( 3, p.y );
  // And back ...
  p.rot( SOUTH, EAST, 4 );
  EXPECT_EQ( 3, p.x );  EXPECT_EQ( 0, p.y );
  // ... and back ...
  p.rot( SOUTH, EAST, 4 );
  EXPECT_EQ( 0, p.x );  EXPECT_EQ( 0, p.y );

  // No change rotation to same
  p.rot(SOUTH, SOUTH, 4);
  EXPECT_EQ( 0, p.x );  EXPECT_EQ( 0, p.y );
}

#include <sstream>

TEST( Tetro, Shape ) {
  std::stringstream out;
  shape_t shape = I_TETRO;

  out << shape;
  EXPECT_EQ( "I_TETRO", out.str() );
  point_t p = tetros[shape].at(0);
  EXPECT_EQ( 1, p.x ); EXPECT_EQ( 0, p.y );

  out.str("");
  shape = J_TETRO;
  out << shape;
  EXPECT_EQ( "J_TETRO", out.str() );
  p = tetros[shape].at(3);
  EXPECT_EQ( 0, p.x ); EXPECT_EQ( 2, p.y );

  out.str("");
  shape = L_TETRO;
  out << shape;
  EXPECT_EQ( "L_TETRO", out.str() );
  p = tetros[shape].at(3);
  EXPECT_EQ( 2, p.x ); EXPECT_EQ( 2, p.y );

  out.str("");
  shape = O_TETRO;
  out << shape;
  EXPECT_EQ( "O_TETRO", out.str() );
  p = tetros[shape].at(0);
  EXPECT_EQ( 1, p.x ); EXPECT_EQ( 1, p.y );

  out.str("");
  shape = S_TETRO;
  out << shape;
  EXPECT_EQ( "S_TETRO", out.str() );
  p = tetros[shape].at(2);
  EXPECT_EQ( 0, p.x ); EXPECT_EQ( 2, p.y );

  out.str("");
  shape = Z_TETRO;
  out << shape;
  EXPECT_EQ( "Z_TETRO", out.str() );
  p = tetros[shape].at(2);
  EXPECT_EQ( 1, p.x ); EXPECT_EQ( 2, p.y );

  out.str("");
  shape = T_TETRO;
  out << shape;
  EXPECT_EQ( "T_TETRO", out.str() );
  p = tetros[shape].at(2);
  EXPECT_EQ( 2, p.x ); EXPECT_EQ( 1, p.y );
}

TEST( Tetro, Rot ) {
  std::stringstream out;

  rot_t rot = SOUTH;
  out << rot;
  EXPECT_EQ( "SOUTH", out.str() );
  out.str("");

  rot = NORTH;
  out << rot;
  EXPECT_EQ( "NORTH", out.str() );
  out.str("");

  rot = WEST;
  out << rot;
  EXPECT_EQ( "WEST", out.str() );
  out.str("");

  rot = EAST;
  out << rot;
  EXPECT_EQ( "EAST", out.str() );
  out.str("");
}

TEST( Tetro, Hit ) {
  std::stringstream out;

  hit_t hit = HIT_NONE;
  EXPECT_EQ( false, hit );
  

}

TEST( Tetro, Grid ) {
  EXPECT_EQ( 2, sizeof(tgrid_t::coord_t)  );

  tgrid_t grid(8,8);

  EXPECT_EQ( 64, grid._cells.size() );
  EXPECT_EQ( 0, grid(0,0) );

  auto range = grid.range();
  EXPECT_EQ( 8, std::get<0>(range.size()) );
  EXPECT_EQ( 8, std::get<1>(range.size()) );

  for( auto&[col,row] : grid.range() ) {
    grid(col,row) = color_t(row*10 + col);
  }

  EXPECT_EQ( 0, grid(0,0) );
  EXPECT_EQ( 1, grid(1,0) );
  EXPECT_EQ( 2, grid(2,0) );
  EXPECT_EQ( 10, grid(0,1) );
  EXPECT_EQ( 12, grid(2,1) );
  EXPECT_EQ( 22, grid(2,2) );
  EXPECT_EQ( 07, grid(7,0) );
  EXPECT_EQ( 77, grid(7,7) );

  // Erase next-to-last row
  grid.erase(6);
  // First line cleared
  EXPECT_EQ( 0, grid(0,0) );
  EXPECT_EQ( 0, grid(1,0) );
  EXPECT_EQ( 0, grid(2,0) );
  // Second line from previous first
  EXPECT_EQ( 1, grid(1,1) );
  EXPECT_EQ( 07, grid(7,1) );
  // Last line untouched
  EXPECT_EQ( 77, grid(7,7) );
}

