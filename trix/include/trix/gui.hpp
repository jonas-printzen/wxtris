#ifndef TRIX_GUI_HDR
#define TRIX_GUI_HDR

#include <trix/types.hpp>
#include <wx/wx.h>

#include <map>

namespace trix {

/** @brief The GUI agent
 *
 * Representing an application and it's main-window.
 *
 */
class GUI : public wxApp {
  GUI(const GUI&) = delete;
  void operator = ( const GUI& ) = delete;
public:

  static constexpr const unsigned DEFAULT_STYLE = wxDEFAULT_FRAME_STYLE;

  GUI( chars_t name, unsigned style=DEFAULT_STYLE );
  ~GUI();

protected:

  /** @brief Setup the GUI-Application 
   *
   * This must always be called first when overriden, and will initialize a
   * plain top-level wxFrame to populate from the subclass Setup().
   */
  bool OnInit() override;

  inline wxFrame& frame() { return *_frame; }

  /** @brief Set clientsize on main-window (frame) */
  inline void SetClientSize( auto&&...args ) {
    _frame->SetClientSize( std::forward<decltype(args)>(args)... );
  }

  /** @brief Create statusbar */
  inline wxStatusBar& CreateStatusBar( auto&&...args ) {
    _statusbar = _frame->CreateStatusBar( std::forward<decltype(args)>(args)... );
    return *_statusbar;
  }

  inline bool Show( bool show ) {
    return _frame->Show(show);
  }

  inline void SetSizerAndFit( wxSizer *psz ) {
    _sizer = psz;
    _frame->SetSizerAndFit( _sizer );
  }

  /** @brief Create/find a menu on the menu-bar. */
  wxMenu& Menu( chars_t title );

  /** @brief Create an item on given menu */
  wxMenuItem& MenuItem( chars_t title, int id, chars_t action );

  /** @brief Get menu-item... */
  wxMenuItem& MenuItem( int id );

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

  inline chars_t name() const { return _name; }

protected:
  wxFrame *_frame=nullptr;  // The main window
  wxSizer *_sizer=nullptr;
  wxMenuBar *_menubar=nullptr;
  wxStatusBar *_statusbar=nullptr;
  std::map<string,wxMenu*> _menus;
  string _name;
  unsigned _frame_style;
};

} // namespace trix


#endif  // TRIX_GUI_HDR
