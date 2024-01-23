#include <trix/tetrix.hpp>

#include <random>

static std::mt19937 rnd_gen;
// static std::uniform_int_distribution<int> rnd_tetro(0,6);

namespace trix {

std::ostream& operator << (std::ostream&out, act_t act ) {
  switch( act ) {
  case STILL: out << "STILL"; break;
  case NEW_TETRO: out << "NEW_TETRO"; break;
  case MOVE_DOWN: out << "MOVE_DOWN"; break;
  case MOVE_LEFT: out << "MOVE_LEFT"; break;
  case MOVE_RIGHT: out << "MOVE_RIGHT"; break;
  case ROT_RIGHT: out << "ROT_RIGHT"; break;
  case ROT_LEFT: out << "ROT_LEFT"; break;
  case FALL: out << "FALL"; break;
  }
  return out;
}


Tetrix::Tetrix( size_type cols, size_type rows )
  : cells(cols,rows), pinned(cols,rows), preview(4, 4) {
}


tetro_t Tetrix::Tetro( point_t pos, shape_t shape , rot_t rot ) {

  tetro_t tetro = tetros[shape];
  int16_t dim=3;

  // Cheat for better rotation
  switch( shape ) {
  case I_TETRO:
    rot = (rot & 1)?EAST:SOUTH;
  case O_TETRO:
    dim = 4;
    break;
  case S_TETRO:
  case Z_TETRO:
    rot = (rot & 1)?WEST:SOUTH;
  default:; // No modification
  };

  for( auto &p : tetro ) {
    p.rot( rot, dim );
    p.place(pos.x, pos.y);
  }

  return tetro;
}

int Tetrix::Randomize( int from, int to ) {
  std::uniform_int_distribution<int> dist(from,to);
  return dist(rnd_gen);
}

hit_t Tetrix::Check( const tetro_t &tetro ) {
  for( auto [x,y] : tetro ) {
    if( x <  0 ) return HIT_LEFT;
    if( x >= pinned.cols() ) return HIT_RIGHT;
    if( y >= pinned.rows() ) return HIT_BOTTOM;
    if( pinned(x,y) ) return HIT_BLOCK;
  }

  return HIT_NONE;
}

void Tetrix::Preview( shape_t shape ) {
  if( NO_TETRO == shape ) {
    pre_shape = (shape_t)Randomize(0,6);
  } else {
    pre_shape = shape;
  }

  auto tetro = Tetro( {0,0}, pre_shape, SOUTH );

  preview.clear(NOCOLOR);

  for( auto [x,y] : tetro ) {
    preview(x,y) = colors[pre_shape];
  }
}

void Tetrix::Place( const tetro_t&tetro, color_t color ) {
  Reset();
  for( auto [x,y] : tetro ) {
    cells(x,y) = color;
  }
}

void Tetrix::Pin() {
  pinned = cells;
}

void Tetrix::Reset( bool to_pinned ) {
  if( !to_pinned ) {
    pinned.clear( NOCOLOR );
  }
  cells = pinned;
}

void Tetrix::Action( act_t act ) {
  std::cout << "Tetrix::Action(): " << act << std::endl;
  if( !running ) return;

  point_t next_point = show_point;
  rot_t  next_rot    = show_rot;
  tetro_t new_tetro;

  if( NO_TETRO != show_shape ) {
    std::cout << "Tetrix::Action(): In-action " << act << std::endl;
    switch( act ) {
    case MOVE_DOWN:
      next_point.y += 1;
      break;
    case MOVE_LEFT:
      next_point.x -= 1;
      break;
    case MOVE_RIGHT:
      next_point.x += 1;
      break;
    case ROT_RIGHT:
      next_rot = rot_t( (next_rot+1) % 4 );
      break;
    case ROT_LEFT:
      next_rot = rot_t( (next_rot+3) % 4 );
      break;
    case FALL:
      // TODO: Implement actual fall
      Pin();
      show_shape = NO_TETRO;
      break;
    default:;
    }

    if( NO_TETRO != show_shape ) {
      std::cout << "Tetrix::Action(): Show-action " << act << std::endl;
      new_tetro = Tetro(next_point,show_shape,next_rot);
      hit_t hit = Check(new_tetro);
      if( HIT_NONE == hit ) {
        // Just update
        show_point = next_point;
        show_rot   = next_rot;
        Place( new_tetro, colors[show_shape] );
      } else {
        // Either just block action, or forward game
        switch( act ) {
        case MOVE_LEFT:
        case MOVE_RIGHT:
        case ROT_LEFT:
        case ROT_RIGHT:
          std::cout << "Tetrix::Action(): Blocked movement!" << std::endl;
          break;
        case MOVE_DOWN:
          // At bottom
          std::cout << "Tetrix::Action(): Bottom-action!" << std::endl;
          Pin();
          show_shape = NO_TETRO;
          break;
        default:
          std::cout << "Tetrix::Action(): Unknown re-action!" << std::endl;
        }
      }
    }
  } else if( NEW_TETRO == act ) {
    std::cout << "Tetrix::Action(): New-action " << act << std::endl;
    show_point = {3,0};
    show_shape = pre_shape;
    show_rot = SOUTH;
    new_tetro = Tetro(show_point,show_shape,show_rot);
    Place( new_tetro, colors[show_shape] );
    Preview();
  }

}


} // namespace trix
