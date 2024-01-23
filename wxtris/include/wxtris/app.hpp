#ifndef WXTRIS_APP_HDR
#define WXTRIS_APP_HDR

#include <trix/types.hpp>
#include <trix/gui.hpp>
#include <trix/tetrix.hpp>
#include <wxtris/main_panel.hpp>

#include <map>

namespace wxtris {
using namespace trix;

class WXTris : public GUI {
public:
  using GUI::MenuItem;

  WXTris();

  bool OnInit() override;

  void OnCmd( wxCommandEvent&evt );

  int FilterEvent( wxEvent &evt ) override;

  bool DoKey( wxKeyEvent&evt );

protected:

  /** @brief Setup main blocks to show colors */
  void ShowColors();

private:

  Tetrix  tetrix;

  MainPanel *panel;
};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
