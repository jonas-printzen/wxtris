#include <trix/blocks.hpp>
#include <trix/ranges.hpp>

#include <wx/event.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>

namespace trix {

Blocks::Blocks( wxWindow *parent, wxSize bsz, int side ) 
  : wxPanel(parent), _bsz(bsz), _side(side), cells(bsz.x,bsz.y) {

  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetBackgroundColour(wxColor(20,20,25));
  Bind( wxEVT_PAINT, &Blocks::OnPaint, this );

  wxSize sz = GetBlocksRect().GetSize();
  sz.IncBy(1,1);
  std::cout << "Block::MinSize(" << sz << ")" << std::endl;
  SetMinSize( sz );

  wxSizer *psz = parent->GetSizer();
  if( psz ) {
    psz->Add(this,5, wxEXPAND |wxALL, MARGIN);
  }
}

void Blocks::OnPaint( wxPaintEvent &evt ) {
  wxAutoBufferedPaintDC dc(this);
  dc.Clear();

  wxGraphicsContext *pgc = wxGraphicsContext::Create(dc);

  // Outline the area
  wxRect rec = GetBlocksRect();
  pgc->SetBrush( *wxTRANSPARENT_BRUSH );
  pgc->SetPen(*wxBLACK);
  pgc->DrawRectangle(rec.x, rec.y, rec.GetWidth(), rec.GetHeight() );

  pgc->SetPen(*wxLIGHT_GREY_PEN);
  pgc->SetBrush( *wxBLUE_BRUSH );

  rec.SetSize( wxSize(_side,_side) );
  rec.Inflate(-2,-2);

  for( auto [x,y] : Range2<int>( _bsz.x, _bsz.y ) ) {
    if( cells(x,y) ) {
      rec.SetPosition( wxPoint(1+MARGIN/2+x*_side, 1+MARGIN/2+y*_side) );
      pgc->DrawRectangle(rec.x, rec.y, rec.GetWidth(), rec.GetHeight() );
    }
  }

  delete pgc;
}

wxRect Blocks::GetBlocksRect() {
  wxRect rec( 0,0,_bsz.GetWidth()*_side, _bsz.GetHeight()*_side );
  rec.width += MARGIN+1;
  rec.height += MARGIN+1;
  return rec;
}



} // namespace trix