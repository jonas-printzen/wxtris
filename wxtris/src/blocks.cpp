#include <trix/ranges.hpp>

#include <wxtris/blocks.hpp>

#include <wx/event.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>

#include <array>

namespace wxtris {

struct attr_t {
  wxPen   pen;
  wxBrush brush;
};

/** @brief Colors used for blocks 
 *
 * @see tetros.hpp: `color_t`
 *
 * Dark, Middle, Light variants for tetros
 */
std::array<attr_t,23> _attrs {
  // GRAY's
  attr_t{ wxPen(wxColor(140,140,140),3),  wxBrush(wxColor(115,115,115)) },
  attr_t{ wxPen(wxColor(255,255,255),3),  wxBrush(wxColor(245,245,245)) },
  // RED's
  attr_t{ wxPen(wxColor(130,20,20),3),    wxBrush(wxColor(100,10,10)) },
  attr_t{ wxPen(wxColor(200,50,50),3),    wxBrush(wxColor(180,10,10)) },
  attr_t{ wxPen(wxColor(250,120,120),3),  wxBrush(wxColor(250,75,75)) },
  // ORANGE's
  attr_t{ wxPen(wxColor(130,80,20),3),   wxBrush(wxColor(110,80,10)) },
  attr_t{ wxPen(wxColor(200,110,50),3),   wxBrush(wxColor(190,110,10)) },
  attr_t{ wxPen(wxColor(250,160,120),3),  wxBrush(wxColor(250,160,75)) },
  // YELLOW's
  attr_t{ wxPen(wxColor(130,130,20),3),   wxBrush(wxColor(100,100,10)) },
  attr_t{ wxPen(wxColor(200,200,50),3),   wxBrush(wxColor(180,180,10)) },
  attr_t{ wxPen(wxColor(250,250,120),3),  wxBrush(wxColor(250,250,75)) },
  // GREEN's
  attr_t{ wxPen(wxColor(20,130,20),3),    wxBrush(wxColor(10,100,10)) },
  attr_t{ wxPen(wxColor(50,200,50),3),    wxBrush(wxColor(10,180,10)) },
  attr_t{ wxPen(wxColor(120,250,120),3),  wxBrush(wxColor(75,250,75)) },
  // CYAN's
  attr_t{ wxPen(wxColor(20,120,120),3),   wxBrush(wxColor(10,100,100)) },
  attr_t{ wxPen(wxColor(50,190,190),3),   wxBrush(wxColor(10,170,170)) },
  attr_t{ wxPen(wxColor(120,240,240),3),  wxBrush(wxColor(75,245,245)) },
  // BLUE's
  attr_t{ wxPen(wxColor(20,20,130),3),    wxBrush(wxColor(10,10,100)) },
  attr_t{ wxPen(wxColor(50,50,200),3),    wxBrush(wxColor(10,10,180)) },
  attr_t{ wxPen(wxColor(120,120,250),3),  wxBrush(wxColor(75,75,250)) },
  // MAGENTA's
  attr_t{ wxPen(wxColor(125,20,125),3),   wxBrush(wxColor(100,10,100)) },
  attr_t{ wxPen(wxColor(185,50,185),3),    wxBrush(wxColor(180,10,180)) },
  attr_t{ wxPen(wxColor(250,120,250),3),  wxBrush(wxColor(250,75,250)) },
};

Blocks::Blocks( wxWindow *parent, const tgrid_t &grid, int side ) 
  : wxPanel(parent), grid(grid), _side(side) {

  SetBackgroundStyle(wxBG_STYLE_PAINT);
  SetBackgroundColour(wxColor(20,20,32));
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
  pgc->SetPen( wxColor(50,50,140) );
  pgc->DrawRectangle(rec.x-1, rec.y-1, rec.GetWidth()+1, rec.GetHeight()+1 );
  pgc->SetPen( wxColor(10,10,40) );
  pgc->DrawRectangle(rec.x, rec.y, rec.GetWidth()+1, rec.GetHeight()+1 );

  rec.SetSize( wxSize(_side,_side) );
  rec.Inflate(-1,-1);

  wxPoint mousePos = ScreenToClient( wxGetMousePosition() );
  wxRect mouseRec;

  for( auto [x,y] : Range2<int>( grid.cols(), grid.rows() ) ) {
    rec.SetPosition( wxPoint(1+MARGIN/2+x*_side, 1+MARGIN/2+y*_side) );
    size_t aid = grid(x,y);
    if( aid ) {
      aid = std::min(aid,_attrs.size()) - 1;
      attr_t &attr = _attrs[aid];
      pgc->SetPen( attr.pen );
      pgc->SetBrush( attr.brush );
      pgc->DrawRoundedRectangle(rec.x, rec.y, rec.GetWidth(), rec.GetHeight(), 5 );
    }
    if( rec.Contains(mousePos) ) {
      mouseRec = rec;
    }
  }

  if( mouseRec.x ) {
    pgc->SetPen( *wxLIGHT_GREY_PEN );
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
  wxRect rec( 0,0,grid.cols()*_side, grid.rows()*_side );
  rec.width += MARGIN+1;
  rec.height += MARGIN+1;
  return rec;
}



} // namespace wxtris
