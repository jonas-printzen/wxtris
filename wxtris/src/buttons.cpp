#include <wxtris/buttons.hpp>

namespace wxtris {

Buttons::Buttons( wxWindow *p, const wxSize &sz, wxOrientation orient ) 
  : wxPanel(p), _sz(sz) {
  SetSizer( new wxBoxSizer(orient) );
}

} // namespace wxtris
