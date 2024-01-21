#include <wxtris/main_panel.hpp>

namespace wxtris {

MainPanel::MainPanel( wxFrame *frame ) 
  : wxPanel(frame,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS) {
  wxSizer *topSz = new wxBoxSizer( wxHORIZONTAL );

  blocks = new Blocks( this, {10,21}, 42 );
  topSz->Add( blocks, 0, wxALIGN_CENTER | wxALL, 10 );

  wxSizer *rightSz = new wxBoxSizer( wxVERTICAL );
  topSz->Add(rightSz,1,wxALL, MARGIN );

  preview = new Blocks( this, {4,4}, 32 );
  rightSz->Add( preview, 0, wxALL, 5 );

  buttons = new Buttons( this, {100,-1}, wxVERTICAL );
  rightSz->Add( buttons, 0, wxALL, 5 );

  SetSizerAndFit( topSz );
}

} // namespace wxtris
