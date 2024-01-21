#include <trix/tetro.hpp>

namespace trix {

std::ostream& operator << ( std::ostream&out, tetro_t tet ) {
  switch( tet ) {
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

std::ostream& operator << ( std::ostream&out, rotate_t rot ) {
  switch( rot ) {
  case SOUTH:  out << "SOUTH"; break;
  case WEST:   out << "WEST"; break;
  case EAST:  out << "EAST"; break;
  case NORTH:  out << "NORTH"; break;
  }
  return out;
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
