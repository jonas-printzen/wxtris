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
  SetBackgroundColour(wxColor(20,20,32));
  Bind( wxEVT_PAINT, &Blocks::OnPaint, this );
  Bind( wxEVT_MOTION, &Blocks::OnMouse, this );

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
  pgc->SetPen( wxColor(50,50,140) );
  pgc->DrawRectangle(rec.x-1, rec.y-1, rec.GetWidth()+1, rec.GetHeight()+1 );
  pgc->SetPen( wxColor(10,10,40) );
  pgc->DrawRectangle(rec.x, rec.y, rec.GetWidth()+1, rec.GetHeight()+1 );

  pgc->SetPen(*wxLIGHT_GREY_PEN);
  pgc->SetBrush( *wxBLUE_BRUSH );

  rec.SetSize( wxSize(_side,_side) );
  rec.Inflate(-2,-2);

  wxPoint mousePos = ScreenToClient( wxGetMousePosition() );
  wxRect mouseRec;

  for( auto [x,y] : Range2<int>( _bsz.x, _bsz.y ) ) {
    rec.SetPosition( wxPoint(1+MARGIN/2+x*_side, 1+MARGIN/2+y*_side) );
    if( cells(x,y) ) {
      pgc->DrawRectangle(rec.x, rec.y, rec.GetWidth(), rec.GetHeight() );
    }
    if( rec.Contains(mousePos) ) {
      mouseRec = rec;
    }
  }

  if( mouseRec.x ) {
    pgc->SetBrush( *wxTRANSPARENT_BRUSH );
    pgc->DrawRectangle(mouseRec.x, mouseRec.y, mouseRec.GetWidth(), mouseRec.GetHeight() );
  }

  delete pgc;
}

void Blocks::OnMouse( wxMouseEvent &evt ) {
  Refresh();
  evt.Skip();
}


wxRect Blocks::GetBlocksRect() {
  wxRect rec( 0,0,_bsz.GetWidth()*_side, _bsz.GetHeight()*_side );
  rec.width += MARGIN+1;
  rec.height += MARGIN+1;
  return rec;
}



} // namespace trix