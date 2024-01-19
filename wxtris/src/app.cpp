#include <trix/gui.hpp>
#include <wxtris/app.hpp>

#include <random>

static std::mt19937 rnd_gen;
static std::uniform_int_distribution<int> rnd_tetro(0,6);
static std::uniform_int_distribution<int> rnd_rot(0,3);

namespace wxtris {
using namespace trix;

inline std::ostream& operator << ( std::ostream&out, rotate_t rot ) {
  switch( rot ) {
  case SOUTH:  out << "SOUTH"; break;
  case WEST:   out << "WEST"; break;
  case EAST:  out << "EAST"; break;
  case NORTH:  out << "NORTH"; break;
  }
  return out;
}

enum menu_ids {
  MENU_START=wxID_HIGHEST+10,
  MENU_COLORS,
  MENU_CLEAR,
  MENU_PREVIEW,
  MENU_ROTATE
};

WXTris::WXTris() : GUI("WXTris") {}

bool WXTris::OnInit() {
  // Let base initialize
  if( GUI::OnInit() ) {
    std::cout << "WXTris::OnInit() ..." << std::endl;

    MenuItem( "Game", MENU_START,  "Start", &WXTris::OnMenu,this );
    MenuItem( "Game", MENU_CLEAR,  "Clear", &WXTris::OnMenu,this );
    MenuItem( "Game", MENU_COLORS,  "Colors", &WXTris::OnMenu,this );
    MenuItem( "Game", MENU_PREVIEW,  "Preview", &WXTris::OnMenu,this );
    MenuItem( "Game", wxID_EXIT, "Quit", &WXTris::OnMenu,this );
    CreateStatusBar(3);

    panel = new MainPanel(_frame);

    panel->buttons->Button( "Preview", MENU_PREVIEW, &WXTris::OnMenu, this );
    panel->buttons->Button( "Rotate", MENU_ROTATE, &WXTris::OnMenu, this );

    // To let panel decide main window size
    wxSizer *psz = new wxBoxSizer(wxHORIZONTAL);
    psz->Add(panel,1);
    SetSizerAndFit( psz );

    Show(true);
    std::cout << "WXTris::OnInit() done!" << std::endl;
    return true;
  }
  std::cout << "WXTris::OnInit() failed!" << std::endl;
  return false;
}

void WXTris::OnButt(wxCommandEvent &evt ) {
  wxButton *pb = (wxButton*)evt.GetEventObject();
  std::cout << "Button "<< evt.GetId() << " clicked! '" << pb->GetLabel() << "'" << std::endl;
}

void WXTris::OnMenu( wxCommandEvent&evt ) {
  std::cout << "Menu selected " << evt.GetId() << std::endl;
  switch( evt.GetId() ) {
    case MENU_CLEAR:
      panel->blocks->cells.clear(Blocks::NONE);
      _frame->Refresh();
      break;
    case MENU_COLORS:
      ShowColors();
      break;
    case MENU_PREVIEW:
      {
        last_tetro = tetro_t(rnd_tetro(rnd_gen));
        // last_rot = rot_t(rnd_rot(rnd_gen));
        last_rot = SOUTH;
        ShowPreview(last_tetro,last_rot);
      }
      break;
    case MENU_ROTATE:
      last_rot = rot_t((last_rot+1)%4);
      ShowPreview( last_tetro, last_rot );
      break;
    case wxID_EXIT:
      _frame->Close();
      break;
    default:
      std::cout << "WXTris::OnMenu(): Unknown ID " << evt.GetId() << std::endl;
  }
}

void WXTris::ShowColors() {
  if( panel && panel->blocks ) {
    panel->blocks->cells(1,1) = Blocks::GRAY;
    panel->blocks->cells(2,1) = Blocks::WHITE;

    panel->blocks->cells(1,2) = Blocks::DARK_RED;
    panel->blocks->cells(2,2) = Blocks::RED;
    panel->blocks->cells(3,2) = Blocks::LIGHT_RED;

    panel->blocks->cells(1,3) = Blocks::DARK_YELLOW;
    panel->blocks->cells(2,3) = Blocks::YELLOW;
    panel->blocks->cells(3,3) = Blocks::LIGHT_YELLOW;

    panel->blocks->cells(1,4) = Blocks::DARK_GREEN;
    panel->blocks->cells(2,4) = Blocks::GREEN;
    panel->blocks->cells(3,4) = Blocks::LIGHT_GREEN;

    panel->blocks->cells(1,5) = Blocks::DARK_BLUE;
    panel->blocks->cells(2,5) = Blocks::BLUE;
    panel->blocks->cells(3,5) = Blocks::LIGHT_BLUE;

    panel->blocks->cells(1,6) = Blocks::DARK_CYAN;
    panel->blocks->cells(2,6) = Blocks::CYAN;
    panel->blocks->cells(3,6) = Blocks::LIGHT_CYAN;

    panel->blocks->cells(1,7) = Blocks::DARK_MAGENTA;
    panel->blocks->cells(2,7) = Blocks::MAGENTA;
    panel->blocks->cells(3,7) = Blocks::LIGHT_MAGENTA;
    _frame->Refresh();
  } else {
    std::cout << "WXTris::ShowColors(): Widgets not initialized!" << std::endl;
  }
}

void WXTris::ShowPreview( tetro_t tet, rot_t rot ) {
  if( panel && panel->preview ) {
    std::cout << "WXTris::ShowPreview(): rotated " << rotate_t(rot) << std::endl;
    panel->preview->Tetro( {0,0}, last_tetro, Blocks::rot_t(rot) );
    _frame->Refresh();
  } else {
    std::cout << "WXTris::ShowPreview(): Widgets not initialized!" << std::endl;
  }
}

} // namespace wxtris

IMPLEMENT_APP(wxtris::WXTris)
