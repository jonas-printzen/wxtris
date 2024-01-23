#ifndef TRIX_TETRIX_HDR
#define TRIX_TETRIX_HDR

#include <trix/tetro.hpp>

namespace trix {

/** @brief User movement 
 *
 * User requested action
 */
enum act_t {
  STILL=0,
  NEW_TETRO,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  ROT_RIGHT,
  ROT_LEFT,
  FALL,
};

extern std::ostream& operator << (std::ostream&out, act_t act );

/** @brief The Tetrix game 
 *
 * This class represents state and logic of the Tetrix game.
 * All you need is to implement a vew to the state and call
 * the methods provided to update the game-state.
 *
 */
class Tetrix {
public:
  using size_type = tgrid_t::size_type;
  using coord_t = tgrid_t::coord_t;

  Tetrix( size_type cols, size_type rows );

  /** @brief Get the points of the tetro 
   *
   * This will provide the points included in the current tetro.
   *
   * @param p   The point at which to check
   * @param tet The tetro-variant
   * @param rot The rotation
   *
   * @return The points of the placed and rotated tetro
   */
  tetro_t Tetro( point_t pos, shape_t shape , rot_t rot );

  int Randomize( int from, int to );

  /** @brief Check for collision 
   *
   * Call this to check if drawing given tetro will collide with anything.
   *
   * @param tetro  The rotated and moved tetro
   * @return Returns HIT_NONE if OK to draw
   */
  hit_t Check( const tetro_t &tetro );

  /** @brief Populate preview with shape */
  void Preview( shape_t shape=NO_TETRO );

  /** @brief Populate with given tetro _t
   *
   * Given the point, variant and rotation, attempt to place a tetro 
   * in the grid. If the tetro will not fit or collides with previous
   * content, fail and return false.
   *
   * @note The color of the tetro is implicit
   *
   * @param p   The point at which to put the tetro
   * @param shape The tetro-variant
   * @param rot The rotation
   * @return Returns 'true' if the tetro was placed without problem.
   */
  inline hit_t Place( point_t p, shape_t shape , rot_t rot ) {
    // Reset to pinned ...
    Reset();
    auto tetro = Tetro( p, shape, rot );
    // Will this tetro hit anything?
    hit_t hit = Check( tetro );

    if( HIT_NONE == hit ) Place( tetro, colors[shape] );
    return hit;
  }

  /** @brief Populate grid with tetro 
   *
   * Plance a prepared tetro on grid
   *
   * @param tetro   The prepared tetro points
   * @param color   Color to use placing the tetor
   */
  void Place( const tetro_t&tetro, color_t color );

  /** @brief Pin the cells 
   *
   * The current state of the cells-matrix is pinned and will be used
   * as base the next time Place() is called.
   */
  void Pin();

  /** @brief Restore cells
   *
   * @note When setting to_pinned=false, you may have to do Pin().
   *
   * @parame to_pinned If true, the pinned blocks will be used, else cleared.
   */
  void Reset( bool to_pinned=true );

  inline coord_t cols() const { return cells.cols(); }
  inline coord_t rows() const { return cells.rows(); }

  inline color_t& operator () ( coord_t col, coord_t row ) {
    return cells(col,row);
  }

  inline const color_t& operator () ( coord_t col, coord_t row ) const {
    return cells(col,row);
  }

  /** @brief User action 
   *
   * This handles user-actions and return if it hit something.
   */
  void Action( act_t act );

  tgrid_t preview; ///< Next tetro
  tgrid_t cells;   ///< The cells shown
  tgrid_t pinned;  ///< The cells pinned

  point_t show_point={0,0};
  shape_t show_shape=NO_TETRO;
  rot_t   show_rot=SOUTH;

  shape_t pre_shape=NO_TETRO;
  bool    running=true;
};


} // namespace trix


#endif  // TRIX_TETRIX_HDR
