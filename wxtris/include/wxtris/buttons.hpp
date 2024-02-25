#ifndef TRIX_BUTTONS_HDR
#define TRIX_BUTTONS_HDR

#include <trix/types.hpp>
#include <wx/wx.h>

namespace wxtris {

using namespace trix;

class Buttons : public wxPanel {
public:
  static constexpr const int MARGIN=5;

  Buttons( wxWindow *parent, const wxSize &sz=wxDefaultSize, wxOrientation orient=wxHORIZONTAL );

  /** @brief Add a button 
   *
   * Add a button and bind a handler
   *
   * @param label  The text that go in the button
   * @param target The binding for event-callback
   */
  template <class B=wxButton>
  B& Button( chars_t label, wxWindowID id, auto&&... target ) {
    return XButton(label,id,0,std::forward<decltype(target)>(target)...);
  }

  /** @brief Add a styled button 
   *
   * @param label  The text that go in the button
   * @param target The binding for event-callback
   */
  template <class B=wxButton>
  B& XButton( chars_t label, wxWindowID id, long style, auto&&... target ) {
    B *pButton = new B(this,id,label.data(),wxDefaultPosition, _sz, style);
    wxSizer *psz = GetSizer();
    if( nullptr != psz ) {
      psz->Add(pButton,0, wxTOP|wxLEFT, MARGIN);
    }
    pButton->Bind(wxEVT_BUTTON, std::forward<decltype(target)>(target)...);
    return *pButton;
  }

protected:
  wxSize _sz;         ///< Default size for buttons in this panel
};

} // namespace trix

#endif  // TRIX_BUTTONS_HDR
