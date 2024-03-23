#include <trix/tetrix.hpp>

#include <random>

static std::mt19937 rnd_gen;

namespace trix {

Tetrix::Tetrix( size_type cols, size_type rows )
  : cells(cols,rows), pinned(cols,rows), preview(4, 4) {
    std::random_device rd;
    rnd_gen.seed(rd());
}

void Tetrix::Start() {
  _running = true;
  show_point = {0,0};
  score.score = 0;
  Preview();
}

void Tetrix::Pause( bool pause ) {
  _running = !pause;
}

void Tetrix::Stop() {
  _running = false;
  show_shape = NO_TETRO;
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
        hit = HIT_BOTTOM;     // HIT_BLOCK => HIT_BOTTOM
      }
    }
  }
  return _hit = hit;
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

bool Tetrix::Pin() {
  bool ret = false;
  // Mark full lines
  for( auto row : Range(cells.rows()) ) {
    int gaps=cells.gaps(row);
    // Mark row white of no gaps!
    if( 0 == gaps ) {
      ret = true;
      cells.mark(row, GRAY);
    }
  }
  pinned = cells;
  return ret;
}

tick_t Tetrix::Tick() {
  if( !_running ) return TICK_NONE;

  switch( _state ) {
  case TICK_NONE:
    _state = TICK_NEXT; 
    score.score += 10*pinned.prune(GRAY);
    break;
  case TICK_NEXT:
    _state = TICK_MOVE;
    if( NO_TETRO == show_shape ) {
      show_shape = pre_shape;
      show_point = {2,0};
      show_rot = SOUTH;
      Preview();
    }
    break;
  case TICK_MOVE:
    // TODO: Skip if recent move?
    _state = TICK_PIN; 
    if( NO_TETRO != show_shape ) {
      Move( MOVE_DOWN );
    }
    break;
  case TICK_PIN:
    _state = TICK_DONE; 
    if( HIT_BOTTOM == _hit ) {
      Pin();
      show_shape = NO_TETRO;
    }
    break;
  case TICK_DONE:
    _state = TICK_NONE;
    break;
  }
  return _state;
}


} // namespace trix
