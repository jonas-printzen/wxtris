#include <trix/gui.hpp>
#include <wxtris/app.hpp>

namespace wxtris {
using namespace trix;

enum menu_ids {
  CMD_START=wxID_HIGHEST+10,
  CMD_COLORS,
  CMD_CLEAR,
  CMD_PREVIEW,
  CMD_ROTATE
};

WXTris::WXTris() : GUI("WXTris"), tetrix(10,21) {}

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

    panel = new MainPanel(_frame, tetrix);
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

  if( tetrix.Running() && akey && DoKey( (wxKeyEvent&)evt ) ) {
    return true;  // Ret-type is int!?!?!
  }

  return wxApp::FilterEvent(evt);
}

bool WXTris::DoKey( wxKeyEvent&evt ) {
  if( wxEVT_KEY_DOWN != evt.GetEventType() ) return false;


  auto key = evt.GetKeyCode();
  bool ret = true;
  hit_t hit = HIT_NONE;


  switch( key ) {
  case WXK_DOWN:  hit = tetrix.Move( MOVE_DOWN ); break;
  case WXK_LEFT:  hit = tetrix.Move( MOVE_LEFT );  break;
  case WXK_RIGHT: hit = tetrix.Move( MOVE_RIGHT ); break;
  case WXK_UP:    hit = tetrix.Move( ROT_LEFT ); break;
  case WXK_SPACE: hit = tetrix.Fall(); break;
  default: tetrix.Increment();
  }

  _frame->Refresh();

  std::cout << "WXTris::DoKey(): " << hit << std::endl;

  return ret;
}

void WXTris::OnCmd( wxCommandEvent&evt ) {
  // std::cout << "WXTris::OnCmd(): " << evt.GetId() << std::endl;
  switch( evt.GetId() ) {
    case CMD_START:
      tetrix.Start();
      break;
    case CMD_CLEAR:
      tetrix.Reset(false);
      break;
    case CMD_COLORS:
      ShowColors();
      break;
    case CMD_PREVIEW:
      tetrix.Preview();
      break;
    case wxID_EXIT:
      _frame->Close();
      break;
    default:
      std::cout << "WXTris::OnCmd(): Unknown ID " << evt.GetId() << std::endl;
  }
  _frame->Refresh();
}

void WXTris::ShowColors() {
  if( panel && panel->blocks ) {
    tetrix(1,1) = GRAY;
    tetrix(2,1) = WHITE;

    tetrix(1,2) = DARK_RED;
    tetrix(2,2) = RED;
    tetrix(3,2) = LIGHT_RED;

    tetrix(1,3) = DARK_ORANGE;
    tetrix(2,3) = ORANGE;
    tetrix(3,3) = LIGHT_ORANGE;

    tetrix(1,4) = DARK_YELLOW;
    tetrix(2,4) = YELLOW;
    tetrix(3,4) = LIGHT_YELLOW;

    tetrix(1,5) = DARK_GREEN;
    tetrix(2,5) = GREEN;
    tetrix(3,5) = LIGHT_GREEN;

    tetrix(1,6) = DARK_BLUE;
    tetrix(2,6) = BLUE;
    tetrix(3,6) = LIGHT_BLUE;

    tetrix(1,7) = DARK_CYAN;
    tetrix(2,7) = CYAN;
    tetrix(3,7) = LIGHT_CYAN;

    tetrix(1,8) = DARK_MAGENTA;
    tetrix(2,8) = MAGENTA;
    tetrix(3,8) = LIGHT_MAGENTA;
    _frame->Refresh();
  } else {
    std::cout << "WXTris::ShowColors(): Widgets not initialized!" << std::endl;
  }
}

} // namespace wxtris

IMPLEMENT_APP(wxtris::WXTris)
