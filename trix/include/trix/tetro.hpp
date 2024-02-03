#ifndef TRIX_TETRO_HDR
#define TRIX_TETRO_HDR

#include <trix/types.hpp>
#include <trix/ranges.hpp>

#include <tuple>
#include <array>
#include <vector>

namespace trix {

/** @brief Tetro-selection */
enum shape_t {
  I_TETRO=0,
  J_TETRO,
  L_TETRO,
  O_TETRO,
  S_TETRO,
  Z_TETRO,
  T_TETRO,
  NO_TETRO = 99
};

std::ostream& operator << ( std::ostream&out, shape_t shape );

/** @brief Tetro - rotation */
enum rot_t {
  SOUTH,
  WEST,
  NORTH,
  EAST,
  NO_ROT,
};

std::ostream& operator << ( std::ostream&out, rot_t rot );

/** @brief A point placing a tetro-block */
struct point_t {
  static constexpr const int16_t DEFAULT_DIM=3;
  static constexpr const rot_t DEFAULT_ROT=SOUTH;

  int16_t x=0;
  int16_t y=0;

  /** @brief Rotate the point in a grid 
   *
   * @param to    The target rotation
   * @param from  The starting rotation
   * @param dim   Size of the grid. (square)
   */
  point_t& rot( rot_t to, rot_t from=SOUTH, int16_t dim=DEFAULT_DIM );
  inline point_t& rot( rot_t to, int16_t dim ) { return rot(to,DEFAULT_ROT,dim); }

  /** @brief Place the point at offset */
  void place( int16_t dx, int16_t dy );
};

using tetro_t = std::array<point_t,4>;
using tetros_t = std::array<tetro_t,7>;

extern const tetros_t tetros;

/** @brief Helper to rotate 2D - vector */
template <size_t S>
inline std::tuple<int,int> Rotate( std::tuple<int,int> xy, rot_t rot ) {
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
  NOCOLOR = 0,
  GRAY,WHITE,
  DARK_RED,     RED,     LIGHT_RED,
  DARK_ORANGE,  ORANGE,  LIGHT_ORANGE,
  DARK_YELLOW,  YELLOW,  LIGHT_YELLOW,
  DARK_GREEN,   GREEN,   LIGHT_GREEN,
  DARK_CYAN,    CYAN,    LIGHT_CYAN,
  DARK_BLUE,    BLUE,    LIGHT_BLUE,
  DARK_MAGENTA, MAGENTA, LIGHT_MAGENTA,
};

extern std::array<color_t,7> colors;

/** @brief Grid of tetro-colors 
 *
 * This is the grid within which blocks are stored.
 */
class tgrid_t {
public:
  using size_type = uint16_t;
  using coord_t = uint16_t;
  // using coords_t = std::tuple<uint16_t,uint16_t>;
  using range_t = Range2<coord_t>;

  tgrid_t( size_type c, size_type r ) : _cells(c*r), _cols(c), _rows(r) {}

  inline constexpr coord_t cols() const { return _cols; }
  inline constexpr coord_t rows() const { return _rows; }

  inline color_t& operator() ( coord_t col, coord_t row ) {
    return _cells.at(col+_cols*row);
  }

  inline const color_t& operator() ( coord_t col, coord_t row ) const {
    return _cells.at(col+_cols*row);
  }

  inline range_t range() {
    return range_t{ {0,0}, {_cols,_rows} };
  }

  inline void clear( color_t val ) {
    for( auto &cell : _cells ) {
      cell = val;
    }
  }

  inline void place( const tetro_t tetro, color_t c ) {
    for( auto [x,y] : tetro ) {
      (*this)(x,y) = c;
    }
  }

  inline void operator = ( const tgrid_t &other ) {
    _cells = other._cells;
  }

#ifndef TRIX_TEST
private:
#endif

  std::vector<color_t> _cells;
  const coord_t _cols;
  const coord_t _rows;
};


} // namespace trix


#endif  // TRIX_TETRO_HDR
