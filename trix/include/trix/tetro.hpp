#ifndef TRIX_TETRO_HDR
#define TRIX_TETRO_HDR

#include <trix/types.hpp>

#include <tuple>

namespace trix {

/** @brief Tetro-selection */
enum tetro_t {
  I_TETRO=0,
  J_TETRO,
  L_TETRO,
  O_TETRO,
  S_TETRO,
  Z_TETRO,
  T_TETRO,
  NO_TETRO = 99
};

std::ostream& operator << ( std::ostream&out, tetro_t tet );

/** @brief Tetro - rotation */
enum rotate_t {
  SOUTH,
  WEST,
  NORTH,
  EAST
};

std::ostream& operator << ( std::ostream&out, rotate_t rot );

/** @brief Helper to rotate 2D - vector */
template <size_t S>
inline std::tuple<int,int> Rotate( std::tuple<int,int> xy, rotate_t rot ) {
  auto [x,y] = xy;
  switch( rot ) {
    case NORTH: return {(S-1)-x,(S-1)-y};
    case EAST: return {(S-1)-y,x};
    case WEST: return {y,(S-1)-x};
    default: return {x,y};
  }
}

/** @brief Collision detection */
enum hit_t {
  HIT_NONE=0,   // No collision was detected
  HIT_LEFT,     // Left border was hit
  HIT_RIGHT,    // Right border was hit
  HIT_BOTTOM,   // Bottom was hit
  HIT_BLOCK     // Another block was hit
};

std::ostream& operator << ( std::ostream&out, hit_t hit );

/** @brief Colors for tetro's*/
enum color_t {
  NONE = 0,
  GRAY,WHITE,
  DARK_RED,     RED,     LIGHT_RED,
  DARK_YELLOW,  YELLOW,  LIGHT_YELLOW,
  DARK_GREEN,   GREEN,   LIGHT_GREEN,
  DARK_CYAN,    CYAN,    LIGHT_CYAN,
  DARK_BLUE,    BLUE,    LIGHT_BLUE,
  DARK_MAGENTA, MAGENTA, LIGHT_MAGENTA,
};

} // namespace trix


#endif  // TRIX_TETRO_HDR
