#include <trix/tetro.hpp>

namespace trix {

const tetros_t tetros {
  tetro_t{      // I_TETRO
    point_t{1,0},
    point_t{1,1},
    point_t{1,2},
    point_t{1,3},
  },
  tetro_t{      // J_TETRO
    point_t{1,0},
    point_t{1,1},
    point_t{1,2},
    point_t{0,2},
  },
  tetro_t{      // L_TETRO
    point_t{1,0},
    point_t{1,1},
    point_t{1,2},
    point_t{2,2},
  },
  tetro_t{      // O_TETRO
    point_t{1,1},
    point_t{2,1},
    point_t{1,2},
    point_t{2,2},
  },
  tetro_t{      // S_TETRO
    point_t{1,1},
    point_t{2,1},
    point_t{0,2},
    point_t{1,2},
  },
  tetro_t{      // Z_TETRO
    point_t{0,1},
    point_t{1,1},
    point_t{1,2},
    point_t{2,2},
  },
  tetro_t{      // T_TETRO
    point_t{0,1},
    point_t{1,1},
    point_t{2,1},
    point_t{1,2},
  },
};

std::array<color_t,7> colors {
  CYAN,
  BLUE,
  ORANGE,
  YELLOW,
  GREEN,
  RED,
  MAGENTA,
};


std::ostream& operator << ( std::ostream&out, shape_t shape ) {
  switch( shape ) {
    case I_TETRO: out << "I_TETRO"; break;
    case J_TETRO: out << "J_TETRO"; break;
    case L_TETRO: out << "L_TETRO"; break;
    case O_TETRO: out << "O_TETRO"; break;
    case S_TETRO: out << "S_TETRO"; break;
    case Z_TETRO: out << "Z_TETRO"; break;
    case T_TETRO: out << "T_TETRO"; break;
    case NO_TETRO: out << "NO_TETR"; break;
  }
  return out;
}

std::ostream& operator << ( std::ostream&out, rot_t rot ) {
  switch( rot ) {
  case SOUTH:  out << "SOUTH"; break;
  case WEST:   out << "WEST"; break;
  case EAST:  out << "EAST"; break;
  case NORTH:  out << "NORTH"; break;
  }
  return out;
}

point_t& point_t::rot( rot_t to, rot_t from, int16_t dim ) {
  rot_t rot = rot_t((4+to-from) % 4);

  auto old_x = x;

  switch( rot ) {
    case NORTH:
      x = (dim-1)-x; 
      y = (dim-1)-y;
      break;
    case EAST:
      x = (dim-1)-y;
      y = old_x;
      break;
    case WEST: 
      x = y;
      y = (dim-1)-old_x ;
      break;
    default:;
  }

  return *this;
}

void point_t::place( int16_t dx, int16_t dy ) {
  x += dx;
  y += dy;
}


tgrid_t::tgrid_t( size_type columns, size_type rows )  
  : _cells(columns*rows), _cols(columns), _rows(rows) {
}


void tgrid_t::clear( color_t val ) {
  for( auto &cell : _cells ) {
    cell = val;
  }
}

void tgrid_t::place( const tetro_t tetro, color_t c ) {
  for( auto [x,y] : tetro ) {
    (*this)(x,y) = c;
  }
}

int tgrid_t::gaps( coord_t row ) const {
  int n=0;
  for( auto col : Range(cols()) ) {
    if( NOCOLOR == (*this)(col,row) ) ++n;
  }
  return n;
}

void tgrid_t::mark( coord_t row, color_t mark_color ) {
  for( auto col : Range(cols()) ) {
    (*this)(col,row) = mark_color;
  }
}

void tgrid_t::erase( coord_t row, color_t filler ) {
  color_t *from = &_cells.at(0);
  color_t *to   = &_cells.at(_cols);

  // Move everything one line down
  ::memmove( to, from,   sizeof(color_t) * row * _cols );
  // Fill line at the top
  ::memset(from, filler, sizeof(color_t) * _cols);
}


void tgrid_t::prune( color_t mark_color ) {
  for( auto row : Range(rows()) ) {
    if( mark_color == (*this)(0,row) ) {
      erase(row);
    }
  }
}

  void tgrid_t::operator = ( const tgrid_t &other ) {
    _cells = other._cells;
  }


std::ostream& operator << ( std::ostream&out, hit_t hit ) {
  switch( hit ) {
  case HIT_NONE:   out << "HIT_NONE"; break;
  case HIT_LEFT:   out << "HIT_LEFT"; break;
  case HIT_RIGHT:  out << "HIT_RIGHT"; break;
  case HIT_BOTTOM: out << "HIT_BOTTOM"; break;
  case HIT_BLOCK:  out << "HIT_BLOCK"; break;
  }
  return out;
}


} // namespace trix
