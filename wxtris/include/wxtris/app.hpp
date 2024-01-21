#ifndef WXTRIS_APP_HDR
#define WXTRIS_APP_HDR

#include <trix/types.hpp>
#include <trix/gui.hpp>
#include <wxtris/main_panel.hpp>

#include <map>

namespace wxtris {
using namespace trix;

class WXTris : public GUI {
public:
  using GUI::MenuItem;
  using rot_t = rotate_t;

  WXTris();

  bool OnInit() override;

  void OnCmd( wxCommandEvent&evt );

  int FilterEvent( wxEvent &evt ) override;

  bool DoKey( wxKeyEvent&evt );

protected:

  /** @brief Setup main blocks to show colors */
  void ShowColors();

  void ShowPreview( tetro_t tet, rot_t rot );

private:
  MainPanel *panel;

  wxPoint show_point={0,0};
  tetro_t show_tetro=NO_TETRO;
  rot_t   show_rot=SOUTH;

  tetro_t last_tetro=NO_TETRO;
  rot_t   last_rot=SOUTH;
  bool _running=true;
};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
