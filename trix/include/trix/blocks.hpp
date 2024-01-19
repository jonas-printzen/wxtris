#ifndef TRIX_BLOCKS_HDR
#define TRIX_BLOCKS_HDR

#include <trix/types.hpp>
#include <trix/vecs.hpp>
#include <trix/rotate.hpp>
#include <wx/wx.h>

#include <array>

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

  using rot_t = rotate_t;

  enum tetro_t {
    I_TETRO=0,
    J_TETRO,
    L_TETRO,
    O_TETRO,
    S_TETRO,
    Z_TETRO,
    T_TETRO
  };

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
  bool Tetro( wxPoint p, tetro_t tet , rot_t rot );

  /** @brief Pin the cells 
   *
   * The current state of the cells-matrix is pinned and will be used
   * as base the next time Tetro() is called.
   */
  void Pin();

  Mat<color_t> cells;   ///< The cells shown
protected:
  Mat<color_t> pinned;  ///< The cells pinned


  void OnPaint( wxPaintEvent &evt );

  void OnMouse( wxMouseEvent &evt );

  wxRect GetBlocksRect();

private:
  wxSize  _bsz;
  int     _side;

  struct attr_t {
    wxPen   pen;
    wxBrush brush;
  };

  static std::array<attr_t,20> _attrs;
};

} // namespace trix

#endif  // TRIX_BLOCKS_HDR