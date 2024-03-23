#include <wxtris/score.hpp>

#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>

namespace wxtris {

Score::Score( wxWindow *parent, const score_t &score  ) 
  : wxPanel(parent), score(score) {
  SetMinSize( wxSize(110,40) );
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetBackgroundColour(wxColor(20,20,32));
  Bind( wxEVT_PAINT, &Score::OnPaint, this );
}

void Score::DrawText() {
  wxAutoBufferedPaintDC dc(this);
  dc.Clear();
  wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  dc.SetFont(font);

  // Set text color
  dc.SetTextForeground(*wxWHITE);

  // Draw text at position (x, y)
  wxString text = wxString::Format("%13d",score.score);
  int x = 10;
  int y = 10;
  dc.DrawText(text, x, y);
}


void Score::OnPaint( wxPaintEvent &evt ) {
  DrawText();
}

} // namespace wxtris
