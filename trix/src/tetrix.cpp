#include <trix/tetrix.hpp>

#include <random>

static std::mt19937 rnd_gen;
// static std::uniform_int_distribution<int> rnd_tetro(0,6);

namespace trix {

Tetrix::Tetrix( size_type cols, size_type rows )
  : cells(cols,rows), pinned(cols,rows), preview(4, 4) {
    std::random_device rd;
    rnd_gen.seed(rd());
}

void Tetrix::Start() {
  _running = true;
  Preview();
}

void Tetrix::Pause() {
  _running = false;
}

void Tetrix::Stop() {
  _running = false;
}

tetro_t Tetrix::Tetro( point_t pos, rot_t rot, shape_t shape ) {
  if( NO_TETRO == shape ) shape = show_shape;
  if( NO_ROT == rot ) rot = show_rot;

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

hit_t Tetrix::Move( move_t mv, bool apply ) {
  hit_t hit = HIT_NONE;
  if( NO_TETRO != show_shape ) {
    point_t next_point = show_point;
    rot_t next_rot = show_rot;
    switch( mv ) {
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
    default:;
    }
    // Need a tetro to check
    tetro_t tetro = Tetro(next_point, next_rot);
    hit = Check( tetro );
    if( apply ) {
      if( HIT_NONE == hit ) {
        show_point = next_point;
        show_rot = next_rot;
        Reset(true);
        cells.place(tetro, colors[show_shape] );
      } else if( MOVE_DOWN == mv ) {
        pinned = cells;
        show_shape = NO_TETRO;
        hit = HIT_BOTTOM;     // HIT_BLOCK => HIT_BOTTOM
      }
    }
  }
  return hit;
}

hit_t Tetrix::Fall() {
  hit_t hit=HIT_NONE;
  if( NO_TETRO != show_shape ) {
    for( int i : Range<int>(0,cells.rows()) ) {
      hit = Move( MOVE_DOWN );
      if( HIT_NONE != hit ) break;
    }
  }

  return hit;
}


void Tetrix::Preview( shape_t shape ) {
  std::cout << "Tetrix::Preview(): " << shape << std::endl;
  if( NO_TETRO == shape ) {
    pre_shape = (shape_t)Randomize(0,6);
  } else {
    pre_shape = shape;
  }

  auto tetro = Tetro( {0,0}, SOUTH, pre_shape );

  preview.clear(NOCOLOR);
  preview.place( tetro, colors[pre_shape] );
}

void Tetrix::Reset( bool to_pinned ) {
  if( !to_pinned ) {
    pinned.clear( NOCOLOR );
  }
  cells = pinned;
}

void Tetrix::Increment() {
  if( NO_TETRO != show_shape ) {
    // We have an active tetro
    auto hit = Move( MOVE_DOWN );
    std::cout << "Tetrix::Increment(): Move(DOWN)" << std::endl;
  } else if( NO_TETRO!=pre_shape ) {
    std::cout << "Tetrix::Increment(): NEW Tetro" << std::endl;
    show_shape = pre_shape;
    show_point = {2,0};
    show_rot = SOUTH;
    Move(MOVE_UP);
    Preview();
  }
}



} // namespace trix
