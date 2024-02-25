#ifndef WXTRIS_APP_HDR
#define WXTRIS_APP_HDR

#include <trix/types.hpp>
#include <trix/tetrix.hpp>
#include <wxtris/main_panel.hpp>

#include <map>


namespace wxtris {
using namespace trix;

class WXTris : public wxApp {
  WXTris(const WXTris&) = delete;
  void operator = ( const WXTris& ) = delete;
public:
  static constexpr const unsigned DEFAULT_STYLE = wxDEFAULT_FRAME_STYLE;

  WXTris();

  bool OnInit() override;
  void OnCmd( wxCommandEvent&evt );
  int FilterEvent( wxEvent &evt ) override;
  bool DoKey( wxKeyEvent&evt );
  void OnStep( wxTimerEvent &evt );

  /** @brief Create/find a menu on the menu-bar
   *
   * Get a menu named as provided. If non exist with that name, it's created.
   *
   * @note First time called, a menu-bar is created to hold the menu's.
   *
   * @param title The menu title to use
   * @return Reference to the menu
   */
  wxMenu& Menu( chars_t title );

  /** @brief Create an item on given menu */
  wxMenuItem& MenuItem( chars_t title, int id, chars_t action );

  /** @brief Create or retrieve a menu 
   *
   * @param title   The name of the menu
   * @param id      The id
   * @param action  The text in the entry
   * @param targ    Binding target
   * @return The id used in binding
   */
  inline wxMenuItem& MenuItem( chars_t title, int id, chars_t action, auto&&...targ  ) {
    wxMenuItem& item = MenuItem(title,id,action);

    // Bind
    Bind( wxEVT_MENU, std::forward<decltype(targ)>(targ)..., item.GetId() );
    return item;
  }

protected:


  /** @brief Execute user-command 
   *
   * To allow execution from both wxCommandEvent and other...
   *
   * @see `cmd_ids` in app.cpp
   */
  void DoCmd( int cmd );

private:

  string _name;

  unsigned    _frame_style;
  wxFrame     *_frame=nullptr;
  wxSizer     *_sizer=nullptr;
  wxStatusBar *_statusbar=nullptr;
  wxMenuBar   *_menubar=nullptr;

  std::map<string,wxMenu*> _menus;

  MainPanel *panel = nullptr;

  Tetrix  tetrix;
  wxTimer timer;


};

} // namespace wxtris


#endif  // WXTRIS_APP_HDR
