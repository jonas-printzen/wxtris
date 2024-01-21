#include <trix/blocks.hpp>
#include <trix/ranges.hpp>

#include <wx/event.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>

#include <array>

namespace trix {

struct attr_t {
  wxPen   pen;
  wxBrush brush;
};

std::array<attr_t,20> _attrs {
  attr_t{ wxPen(wxColor(140,140,140),3),  wxBrush(wxColor(115,115,115)) },
  attr_t{ wxPen(wxColor(255,255,255),3),  wxBrush(wxColor(245,245,245)) },
  //RED's
  attr_t{ wxPen(wxColor(130,20,20),3),    wxBrush(wxColor(100,10,10)) },
  attr_t{ wxPen(wxColor(200,50,50),3),    wxBrush(wxColor(180,10,10)) },
  attr_t{ wxPen(wxColor(250,120,120),3),  wxBrush(wxColor(250,75,75)) },
  //YELLOW's
  attr_t{ wxPen(wxColor(130,130,20),3),   wxBrush(wxColor(100,100,10)) },
  attr_t{ wxPen(wxColor(200,200,50),3),   wxBrush(wxColor(180,180,10)) },
  attr_t{ wxPen(wxColor(250,250,120),3),  wxBrush(wxColor(250,250,75)) },
  //GREEN's
  attr_t{ wxPen(wxColor(20,130,20),3),    wxBrush(wxColor(10,100,10)) },
  attr_t{ wxPen(wxColor(50,200,50),3),    wxBrush(wxColor(10,180,10)) },
  attr_t{ wxPen(wxColor(120,250,120),3),  wxBrush(wxColor(75,250,75)) },
  //CYAN's
  attr_t{ wxPen(wxColor(20,120,120),3),   wxBrush(wxColor(10,100,100)) },
  attr_t{ wxPen(wxColor(50,190,190),3),   wxBrush(wxColor(10,170,170)) },
  attr_t{ wxPen(wxColor(120,240,240),3),  wxBrush(wxColor(75,245,245)) },
  //BLUE's
  attr_t{ wxPen(wxColor(20,20,130),3),    wxBrush(wxColor(10,10,100)) },
  attr_t{ wxPen(wxColor(50,50,200),3),    wxBrush(wxColor(10,10,180)) },
  attr_t{ wxPen(wxColor(120,120,250),3),  wxBrush(wxColor(75,75,250)) },
  //MAGENTA's
  attr_t{ wxPen(wxColor(125,20,125),3),   wxBrush(wxColor(100,10,100)) },
  attr_t{ wxPen(wxColor(185,50,185),3),    wxBrush(wxColor(180,10,180)) },
  attr_t{ wxPen(wxColor(250,120,250),3),  wxBrush(wxColor(250,75,250)) },
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

static std::array<color_t,7> tcolors {
  CYAN,
  BLUE,
  DARK_YELLOW,
  YELLOW,
  GREEN,
  RED,
  MAGENTA,
};

Blocks::Blocks( wxWindow *parent, wxSize bsz, int side ) 
  : wxPanel(parent), cells(bsz.x,bsz.y), pinned(bsz.x,bsz.y), _bsz(bsz), _side(side) {

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

Blocks::points_t Blocks::Points( wxPoint p, tetro_t tet , rot_t rot ) {
  int tid = std::min((size_t)tet, tetras.size()-1);
  auto &shape = tetras[tid];

  points_t points;

  // We group to handle symmetry 
  switch( tet ) {
    case I_TETRO:
      rot = (rot & 1)?EAST:SOUTH; // Cheat for better rotation
    case O_TETRO:
      for( auto [x,y] : Range2( {0,0}, {4,4} ) ) {
        auto [rx,ry] = Rotate<4>( {x,y}, rot );
        if( shape[4*ry+rx] ) {
          points.push_back( {uint8_t(p.x+x), uint8_t(p.y+y)} );
        }
      }
      break;
    //-------------------------------------------------------
    case S_TETRO:
    case Z_TETRO:
      rot = (rot & 1)?WEST:SOUTH; // Cheat for better rotation
    case J_TETRO:
    case L_TETRO:
    case T_TETRO:
      for( auto [x,y] : Range2( {0,0}, {3,3} ) ) {
        auto [rx,ry] = Rotate<3>( {x,y}, rot );
        if( shape[4*ry+rx] ) points.emplace_back( p.x+x, p.y+y );;
      }
      break;
    default:;
  }
  
  return points;
}

hit_t Blocks::Check( const points_t &points ) {
  for( auto [x,y] : points ) {
    if( x <  0 ) return HIT_LEFT;
    if( x >= _bsz.GetWidth() ) return HIT_RIGHT;
    if( y >= _bsz.GetHeight() ) return HIT_BOTTOM;
    if( cells(x,y) ) return HIT_BLOCK;
  }

  return HIT_NONE;
}

hit_t Blocks::Tetro( wxPoint p, tetro_t tet , rot_t rot ) {
  // Reset to pinned ...
  cells = pinned;
  auto points = Points( p, tet, rot );
  // Will this tetro hit anything?
  hit_t hit = Check( points );

  if( HIT_NONE == hit ) {
    // What color for this tetra
    color_t color = tcolors[std::min((size_t)tet, tetras.size()-1)];
    // Fill the grid
    for( auto [x,y] : Points(p,tet,rot) ) {
      cells(x,y) = color;
    }
  }

  return hit;
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