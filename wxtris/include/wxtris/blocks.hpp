#ifndef TRIX_BLOCKS_HDR
#define TRIX_BLOCKS_HDR

#include <trix/types.hpp>
#include <trix/tetrix.hpp>
#include <wx/wx.h>

namespace wxtris {

using namespace trix;

/** @brief Blocks canvas
 *
 * A simple blocks canvas. The size of the grid is set
 * on construction and size adjusted. The cells can be
 * manipulated directly and are initially empty (0).
 *
 */
class Blocks : public wxPanel {
public:
  static constexpr const int DEFAULT_SIDE = 32;
  static constexpr const int MARGIN = 10;

  /** @brief Construct an empty block-grid
   *
   * @param parent  The parent of this panel
   * @param bsz     The size of the grid
   * @param side    The side of each square
   *
   * @note This widget will attempt to auto-layout using parent sizer
   */
  Blocks( wxWindow *parent, const tgrid_t &grid, int side=DEFAULT_SIDE );

  const tgrid_t &grid;

protected:

  /** @brief Paint this custom view */
  void OnPaint( wxPaintEvent &evt );

  /** @brief React to mouse over */
  void OnMouse( wxMouseEvent &evt );

  wxRect GetBlocksRect();

private:
  int     _side;  ///< Pixel-size of each block
};

} // namespace wxtris

#endif  // TRIX_BLOCKS_HDR
