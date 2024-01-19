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

  WXTris();

  bool OnInit() override;

  void OnButt (wxCommandEvent &evt );

  void OnMenu( wxCommandEvent&evt );

protected:

  /** @brief Setup main blocks to show colors */
  void ShowColors();

  void ShowPreview();

private:
  MainPanel *panel;

};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
