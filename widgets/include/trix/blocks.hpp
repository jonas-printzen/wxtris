#ifndef TRIX_BLOCKS_HDR
#define TRIX_BLOCKS_HDR

#include <trix/types.hpp>
#include <trix/vecs.hpp>
#include <wx/wx.h>

namespace trix {

/** @brief Blocks canvas
 *
 * A simple square-blocks canvas with auto-layout.
 *
 */
class Blocks : public wxPanel {
public:

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

  Mat<uint8_t> cells;


protected:
  void OnPaint( wxPaintEvent &evt );

  void OnMouse( wxMouseEvent &evt );

  wxRect GetBlocksRect();

private:
  wxSize  _bsz;
  int     _side;
};

} // namespace trix

#endif  // TRIX_BLOCKS_HDR