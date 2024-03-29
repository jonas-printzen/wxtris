#ifndef TRIX_TETRIX_HDR
#define TRIX_TETRIX_HDR

#include <trix/tetro.hpp>

namespace trix {

/** @brief User move action */
enum move_t {
  MOVE_NONE=0,
  MOVE_UP,  
  MOVE_DOWN,  
  MOVE_LEFT,
  MOVE_RIGHT,
  FALL_DOWN,
  ROT_RIGHT,
  ROT_LEFT,
};

/** @brief Tick result
 *
 * Each call to Tick() will result in one of these side-effects.
 * There may be several calls which return TICK_NONE between
 * any side-effect, depending on speed and state. It is upp to 
 * the UI-code to interpret and visualize (and/or audio)
 */
enum tick_t {
  TICK_NONE = 0,
  TICK_NEXT,    ///< New tetro introduced
  TICK_MOVE,    ///< Tetro moved by increment
  TICK_PIN,     ///< Check if it's time to pin (HIT_BOTTOM)
  TICK_DONE     ///< This iteration done
};

/** @brief The Tetrix game 
 *
 * This class represents state and logic of the Tetrix game.
 * All you need is to implement a view to the state and call
 * the methods provided to update the game-state.
 *
 */
class Tetrix {
public:
  using size_type = tgrid_t::size_type;
  using coord_t = tgrid_t::coord_t;

  struct score_t { int score; };

  Tetrix( size_type cols, size_type rows );

  inline bool Running() const { return _running; }

  void Start();
  void Pause( bool pause=true );
  void Stop();

  /** @brief Get the points of the tetro 
   *
   * This will provide the points included in the current tetro.
   *
   * @param p   The point at which to check
   * @param tet The tetro-shape, default => show_shape 
   * @param rot The rotation, default => show_rot
   *
   * @return The points of the placed and rotated tetro
   */
  tetro_t Tetro( point_t pos, rot_t rot=NO_ROT, shape_t shape=NO_TETRO );

  /** @brief Randomize int 
   *
   * This is used to get a random int
   */
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

  /** @brief Move the active tetro 
   *
   * Move an active tetro in the direction given, report
   * a hit if move does not work. When apply is 'true' the
   * state is updated and a HIT_BOTTOM will pin the tetro.
   *
   * @param mv      Direction to move
   * @param apply   If true, the state is updated
   * @return HIT_NONE if move ok OR if nothing to move
   */
  hit_t Move( move_t mv, bool apply=true );

  /** @brief Let the tetro fall 
   *
   * Let the tetro fall until it hit something
   */
  hit_t Fall();

  /** @brief Game-state tick 
   *
   * This must be called several times every increment to update
   * the state of this game-engine. A good rate is every 20ms.
   */
  tick_t Tick();

  /** @brief Pin the cells and check for full lines */
  bool Pin();

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

  tgrid_t preview; ///< Next tetro
  tgrid_t cells;   ///< The cells shown
  score_t score;

protected:

  tgrid_t pinned;  ///< The cells pinned
  point_t show_point={0,0};
  shape_t show_shape=NO_TETRO;
  rot_t   show_rot=SOUTH;
  tick_t  _state = TICK_NONE;   ///< State of update
  hit_t   _hit=HIT_NONE;        ///< Did last move hit anything?

  shape_t pre_shape=NO_TETRO;
  bool    _running=false;
};


} // namespace trix


#endif  // TRIX_TETRIX_HDR
