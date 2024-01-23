#ifndef WXTRIS_MAIN_PANEL_HDR
#define WXTRIS_MAIN_PANEL_HDR

#include <trix/types.hpp>
#include <trix/blocks.hpp>
#include <trix/buttons.hpp>

namespace wxtris {

using namespace trix;

/** @brief The main panel 
 *
 * This class is a simple wrapper around the layout of the game.
 * All elements can be accessed as members.
 */
class MainPanel : public wxPanel {
public:
  static constexpr const int MARGIN = 16;

  /** @brief Designed to be main-panel in frame */
  MainPanel( wxFrame *frame, const Tetrix &tetrix );

  Blocks *blocks=nullptr;     ///< The main block for the game
  Blocks *preview=nullptr;    ///< Preview of next item
  Buttons *buttons=nullptr;
};

} // namespace wxtris



#endif  // WXTRIS_MAIN_PANEL_HDR
