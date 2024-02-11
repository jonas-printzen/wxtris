#ifndef WXTRIS_APP_HDR
#define WXTRIS_APP_HDR

#include <trix/types.hpp>
#include <trix/gui.hpp>
#include <trix/tetrix.hpp>
#include <wxtris/main_panel.hpp>

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
  void OnStep( wxTimerEvent &evt );

protected:

  /** @brief Execute user-command 
   *
   * To allow execution from both wxCommandEvent and other...
   *
   * @see `cmd_ids` in app.cpp
   */
  void DoCmd( int cmd );

private:

  Tetrix  tetrix;

  wxTimer timer;

  MainPanel *panel = nullptr;
};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
