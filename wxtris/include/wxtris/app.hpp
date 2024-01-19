#ifndef WXTRIS_APP_HDR
#define WXTRIS_APP_HDR

#include <trix/types.hpp>
#include <trix/gui.hpp>
#include <wxtris/main_panel.hpp>

namespace wxtris {
using namespace trix;

class WXTris : public GUI {
public:
  using GUI::MenuItem;
  using tetro_t = Blocks::tetro_t;
  using rot_t = rotate_t;

  WXTris();

  bool OnInit() override;

  void OnButt (wxCommandEvent &evt );

  void OnMenu( wxCommandEvent&evt );

protected:

  /** @brief Setup main blocks to show colors */
  void ShowColors();

  void ShowPreview( tetro_t tet, rot_t rot );

private:
  MainPanel *panel;

  tetro_t last_tetro=Blocks::O_TETRO;
  rot_t   last_rot=SOUTH;
};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
