#include <trix/gui.hpp>
#include <wxtris/app.hpp>

#include <random>

static std::mt19937 rnd_gen;
static std::uniform_int_distribution<int> rnd_tetro(0,6);
static std::uniform_int_distribution<int> rnd_rot(0,3);

namespace wxtris {
using namespace trix;

enum menu_ids {
  CMD_START=wxID_HIGHEST+10,
  CMD_COLORS,
  CMD_CLEAR,
  CMD_PREVIEW,
  CMD_ROTATE
};

WXTris::WXTris() : GUI("WXTris") {}

bool WXTris::OnInit() {
  // Let base initialize
  if( GUI::OnInit() ) {
    std::cout << "WXTris::OnInit() ..." << std::endl;

    MenuItem( "Game", CMD_START,  "Start", &WXTris::OnCmd,this );
    MenuItem( "Game", CMD_CLEAR,  "Clear", &WXTris::OnCmd,this );
    MenuItem( "Game", CMD_COLORS,  "Colors", &WXTris::OnCmd,this );
    MenuItem( "Game", CMD_PREVIEW,  "Preview", &WXTris::OnCmd,this );
    MenuItem( "Game", wxID_EXIT, "Quit", &WXTris::OnCmd,this );
    CreateStatusBar(3);

    panel = new MainPanel(_frame);
    panel->buttons->Button( "Preview", CMD_PREVIEW, &WXTris::OnCmd, this );
    panel->buttons->Button( "Rotate", CMD_ROTATE, &WXTris::OnCmd, this );

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

int WXTris::FilterEvent( wxEvent &evt ) {
  auto etype =  evt.GetEventType();
  auto akey = wxEVT_KEY_DOWN == etype || wxEVT_KEY_UP == etype;

  if( _running && akey && DoKey( (wxKeyEvent&)evt ) ) {
    return true;  // Ret-type is int!?!?!
  }

  return wxApp::FilterEvent(evt);
}

bool WXTris::DoKey( wxKeyEvent&evt ) {
  if( wxEVT_KEY_DOWN != evt.GetEventType() ) return false;

  auto key = evt.GetKeyCode();
  bool ret = false;

  // If we get a key, take preview-tetro to the board (POC)
  if( NO_TETRO == show_tetro ) {
    // Place
    std::cout << "WXTris::DoKey(): Moving from preview!" << std::endl;
    show_tetro = last_tetro;
    show_point = {4,0};
    show_rot = last_rot;
    ret = true;
  } else if( NO_TETRO != show_tetro ) {
    // Move
    switch( key ) {
    case WXK_DOWN:  show_point.y += 1; break;
    case WXK_LEFT:  show_point.x -= 1; break;
    case WXK_RIGHT: show_point.x += 1; break;
    case WXK_UP: show_rot = rot_t( (show_rot+1) % 4 ); break;
    case WXK_SPACE: 
      panel->blocks->Pin(); 
      show_tetro = NO_TETRO;
      break;
    }
  }

  if( NO_TETRO != show_tetro ) {
    auto hit = panel->blocks->Tetro( show_point, show_tetro, show_rot );
    if( HIT_NONE != hit ) {
      std::cout << "WXTris::DoKey(): Block hit '"<< hit <<"("<< int(hit) << "', removing!" << std::endl;
      show_tetro = NO_TETRO;
    }
    _frame->Refresh();
  }

  return ret;
}


void WXTris::OnCmd( wxCommandEvent&evt ) {
  // std::cout << "WXTris::OnCmd(): " << evt.GetId() << std::endl;
  switch( evt.GetId() ) {
    case CMD_CLEAR:
      panel->blocks->cells.clear(NONE);
      _frame->Refresh();
      break;
    case CMD_COLORS:
      ShowColors();
      break;
    case CMD_PREVIEW:
      last_tetro = tetro_t(rnd_tetro(rnd_gen));
      last_rot = SOUTH;
      ShowPreview(last_tetro,last_rot);
      break;
    case CMD_ROTATE:
      last_rot = rot_t( (last_rot+1) % 4 );
      ShowPreview( last_tetro, last_rot );
      break;
    case wxID_EXIT:
      _frame->Close();
      break;
    default:
      std::cout << "WXTris::OnCmd(): Unknown ID " << evt.GetId() << std::endl;
  }
}

void WXTris::ShowColors() {
  if( panel && panel->blocks ) {
    panel->blocks->cells(1,1) = GRAY;
    panel->blocks->cells(2,1) = WHITE;

    panel->blocks->cells(1,2) = DARK_RED;
    panel->blocks->cells(2,2) = RED;
    panel->blocks->cells(3,2) = LIGHT_RED;

    panel->blocks->cells(1,3) = DARK_YELLOW;
    panel->blocks->cells(2,3) = YELLOW;
    panel->blocks->cells(3,3) = LIGHT_YELLOW;

    panel->blocks->cells(1,4) = DARK_GREEN;
    panel->blocks->cells(2,4) = GREEN;
    panel->blocks->cells(3,4) = LIGHT_GREEN;

    panel->blocks->cells(1,5) = DARK_BLUE;
    panel->blocks->cells(2,5) = BLUE;
    panel->blocks->cells(3,5) = LIGHT_BLUE;

    panel->blocks->cells(1,6) = DARK_CYAN;
    panel->blocks->cells(2,6) = CYAN;
    panel->blocks->cells(3,6) = LIGHT_CYAN;

    panel->blocks->cells(1,7) = DARK_MAGENTA;
    panel->blocks->cells(2,7) = MAGENTA;
    panel->blocks->cells(3,7) = LIGHT_MAGENTA;
    _frame->Refresh();
  } else {
    std::cout << "WXTris::ShowColors(): Widgets not initialized!" << std::endl;
  }
}

void WXTris::ShowPreview( tetro_t tet, rot_t rot ) {
  if( panel && panel->preview ) {
    // std::cout << "WXTris::ShowPreview("<<tet<<"): rotated " << rotate_t(rot) << std::endl;
    panel->preview->Tetro( {0,0}, last_tetro, Blocks::rot_t(rot) );
    _frame->Refresh();
  } else {
    std::cout << "WXTris::ShowPreview(): Widgets not initialized!" << std::endl;
  }
}

} // namespace wxtris

IMPLEMENT_APP(wxtris::WXTris)
