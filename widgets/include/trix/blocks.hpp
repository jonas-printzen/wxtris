#ifndef TRIX_BLOCKS_HDR
#define TRIX_BLOCKS_HDR

#include <trix/types.hpp>
#include <trix/vecs.hpp>
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

  Mat<color_t> cells;


protected:
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