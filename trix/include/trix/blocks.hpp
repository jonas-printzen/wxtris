#ifndef TRIX_BLOCKS_HDR
#define TRIX_BLOCKS_HDR

#include <trix/types.hpp>
#include <trix/vecs.hpp>
#include <trix/tetro.hpp>
#include <wx/wx.h>

namespace trix {

/** @brief Blocks canvas
 *
 * A simple blocks canvas. The size of the grid is set
 * on construction and size adjusted. The cells can be
 * manipulated directly and are initially empty (0).
 *
 */
class Blocks : public wxPanel {
public:


  using rot_t = rotate_t;

  /** @brief Where to draw blocks */
  struct xy_t { 
    int16_t x=0;
    int16_t y=0;
  };

  using points_t = std::vector<xy_t>;

  static constexpr const int DEFAULT_SIDE = 10;
  static constexpr const int MARGIN = 10;

  /** @brief Construct an empty block-grid
   *
   * @param parent  The parent of this panel
   * @param bsz     The size of the grid
   * @param side    The side of each square
   *
   * @note This widget will attempt to auto-layout using parent sizer
   */
  Blocks( wxWindow *parent, wxSize bsz, int side=DEFAULT_SIDE );

  /** @brief Populate with given tetro _t
   *
   * Given the point, variant and rotation, attempt to place a tetro 
   * in the grid. If the tetro will not fit or collides with previous
   * content, fail and return false.
   *
   * @note The color of the tetro is implicit
   *
   * @param p   The point at which to put the tetro
   * @param tet The tetro-variant
   * @param rot The rotation
   * @return Returns 'true' if the tetro was placed without problem.
   */
  hit_t Tetro( wxPoint p, tetro_t tet , rot_t rot );

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
  points_t Points( wxPoint p, tetro_t tet , rot_t rot );

  /** @brief Check for collision 
   *
   * Call this to check if drawing given tetro will collide with anything.
   *
   * @param p   The point at which to check
   * @param tet The tetro-variant
   * @param rot The rotation
   * @return Returns HIT_NONE it OK to draw
   */
  hit_t Check( const points_t &points );

  /** @brief Pin the cells 
   *
   * The current state of the cells-matrix is pinned and will be used
   * as base the next time Tetro() is called.
   */
  void Pin();

  Mat<color_t> cells;   ///< The cells shown
protected:
  Mat<color_t> pinned;  ///< The cells pinned


  /** @brief Paint this custom view */
  void OnPaint( wxPaintEvent &evt );

  /** @brief React to mouse over */
  void OnMouse( wxMouseEvent &evt );

  wxRect GetBlocksRect();

private:
  wxSize  _bsz;   ///< Size of the block-grid to display
  int     _side;  ///< Pixel-size of each block
};

} // namespace trix

#endif  // TRIX_BLOCKS_HDR