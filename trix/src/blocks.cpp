#include <trix/blocks.hpp>
#include <trix/ranges.hpp>
#include <trix/rotate.hpp>

#include <wx/event.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>

namespace trix {

std::array<Blocks::attr_t,20> Blocks::_attrs {
  Blocks::attr_t{ wxPen(wxColor(140,140,140),3),  wxBrush(wxColor(115,115,115)) },
  Blocks::attr_t{ wxPen(wxColor(255,255,255),3),  wxBrush(wxColor(245,245,245)) },
  //RED's
  Blocks::attr_t{ wxPen(wxColor(130,20,20),3),    wxBrush(wxColor(100,10,10)) },
  Blocks::attr_t{ wxPen(wxColor(200,50,50),3),    wxBrush(wxColor(180,10,10)) },
  Blocks::attr_t{ wxPen(wxColor(250,120,120),3),  wxBrush(wxColor(250,75,75)) },
  //YELLOW's
  Blocks::attr_t{ wxPen(wxColor(130,130,20),3),   wxBrush(wxColor(100,100,10)) },
  Blocks::attr_t{ wxPen(wxColor(200,200,50),3),   wxBrush(wxColor(180,180,10)) },
  Blocks::attr_t{ wxPen(wxColor(250,250,120),3),  wxBrush(wxColor(250,250,75)) },
  //GREEN's
  Blocks::attr_t{ wxPen(wxColor(20,130,20),3),    wxBrush(wxColor(10,100,10)) },
  Blocks::attr_t{ wxPen(wxColor(50,200,50),3),    wxBrush(wxColor(10,180,10)) },
  Blocks::attr_t{ wxPen(wxColor(120,250,120),3),  wxBrush(wxColor(75,250,75)) },
  //CYAN's
  Blocks::attr_t{ wxPen(wxColor(20,120,120),3),   wxBrush(wxColor(10,100,100)) },
  Blocks::attr_t{ wxPen(wxColor(50,190,190),3),   wxBrush(wxColor(10,170,170)) },
  Blocks::attr_t{ wxPen(wxColor(120,240,240),3),  wxBrush(wxColor(75,245,245)) },
  //BLUE's
  Blocks::attr_t{ wxPen(wxColor(20,20,130),3),    wxBrush(wxColor(10,10,100)) },
  Blocks::attr_t{ wxPen(wxColor(50,50,200),3),    wxBrush(wxColor(10,10,180)) },
  Blocks::attr_t{ wxPen(wxColor(120,120,250),3),  wxBrush(wxColor(75,75,250)) },
  //MAGENTA's
  Blocks::attr_t{ wxPen(wxColor(125,20,125),3),   wxBrush(wxColor(100,10,100)) },
  Blocks::attr_t{ wxPen(wxColor(185,50,185),3),    wxBrush(wxColor(180,10,180)) },
  Blocks::attr_t{ wxPen(wxColor(250,120,250),3),  wxBrush(wxColor(250,75,250)) },
};

using tetra_t = std::array<int8_t,4*4>;

static std::array<tetra_t,7> tetras {
  tetra_t { // I_TETRO
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0
  },
  tetra_t { // J_TETRO
    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0,
  },
  tetra_t { // L_TETRO
    0,1,0,0,
    0,1,0,0,
    0,1,1,0,
    0,0,0,0,
  },
  tetra_t { // O_TETRO
    0,0,0,0,
    0,1,1,0,
    0,1,1,0,
    0,0,0,0
  },
  tetra_t { // S_TETRO
    0,0,0,0,
    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
  },
  tetra_t { // Z_TETRO
    0,0,0,0,
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
  },
  tetra_t { // T_TETRO
    0,0,0,0,
    1,1,1,0,
    0,1,0,0,
    0,0,0,0,
  },
};

static std::array<Blocks::color_t,7> tcolors {
  Blocks::CYAN,
  Blocks::BLUE,
  Blocks::DARK_YELLOW,
  Blocks::YELLOW,
  Blocks::GREEN,
  Blocks::RED,
  Blocks::MAGENTA,
};

Blocks::Blocks( wxWindow *parent, wxSize bsz, int side ) 
  : wxPanel(parent), _bsz(bsz), _side(side), cells(bsz.x,bsz.y), pinned(bsz.x,bsz.y) {

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

bool Blocks::Tetro( wxPoint p, tetro_t tet , rot_t rot ) {
  // Start by resetting to pinned
  cells = pinned;

  int tid = std::min((size_t)tet, tetras.size()-1);

  auto &shape = tetras[tid];

  // We group to handle symmetry 
  switch( tet ) {
    case I_TETRO:
      rot = rot_t((rot & 1)?3:0); // Cheat for better rotation
    case O_TETRO:
      for( auto [x,y] : Range2( {0,0}, {4,4} ) ) {
        auto [rx,ry] = Rotate<4>( {x,y}, rot );
        if( shape[4*ry+rx] ) cells( p.x+x, p.y+y ) = tcolors[tid];
      }
      break;
    case J_TETRO:
    case L_TETRO:
    case S_TETRO:
    case Z_TETRO:
    case T_TETRO:
      for( auto [x,y] : Range2( {0,0}, {3,3} ) ) {
        auto [rx,ry] = Rotate<3>( {x,y}, rot );
        if( shape[4*ry+rx] ) cells( p.x+x, p.y+y ) = tcolors[tid];
      }
  }


  return true;
}

void Blocks::Pin() {
  pinned = cells;
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

  for( auto [x,y] : Range2<int>( _bsz.x, _bsz.y ) ) {
    rec.SetPosition( wxPoint(1+MARGIN/2+x*_side, 1+MARGIN/2+y*_side) );
    size_t aid = cells(x,y);
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
  wxRect rec( 0,0,_bsz.GetWidth()*_side, _bsz.GetHeight()*_side );
  rec.width += MARGIN+1;
  rec.height += MARGIN+1;
  return rec;
}



} // namespace trix