#include <trix/gui.hpp>
#include <wxtris/app.hpp>

namespace wxtris {
using namespace trix;

enum cmd_ids {
  CMD_START=wxID_HIGHEST+10,
  CMD_PAUSE,
  CMD_STOP,
  CMD_CLEAR,
  CMD_PREVIEW,
  CMD_STEP,   // When running, timer sends this command
  CMD_UP,  
  CMD_DOWN,  
  CMD_LEFT,
  CMD_RIGHT,
  CMD_ROT_LEFT,
  CMD_ROT_RIGHT,
  CMD_FALL,
  CMD_EXIT
};

WXTris::WXTris() : GUI("WXTris"), tetrix(10,21), timer(this,CMD_STEP) {}

bool WXTris::OnInit() {
  // Let base initialize
  if( GUI::OnInit() ) {
    std::cout << "WXTris::OnInit() ..." << std::endl;

    CreateStatusBar(3);

    panel = new MainPanel(_frame, tetrix);
    panel->buttons->Button( "Start", CMD_START, &WXTris::OnCmd, this );
    panel->buttons->Button( "Pause", CMD_PAUSE, &WXTris::OnCmd, this );
    panel->buttons->Button( "Stop", CMD_STOP, &WXTris::OnCmd, this );

    // To let panel decide main window size
    wxSizer *psz = new wxBoxSizer(wxHORIZONTAL);
    psz->Add(panel,1);
    SetSizerAndFit( psz );

    Show(true);

    Bind( wxEVT_TIMER, &WXTris::OnStep, this );

    std::cout << "WXTris::OnInit() done!" << std::endl;
    return true;
  }
  std::cout << "WXTris::OnInit() failed!" << std::endl;
  return false;
}

int WXTris::FilterEvent( wxEvent &evt ) {
  auto etype =  evt.GetEventType();
  auto isakey = wxEVT_KEY_DOWN == etype || wxEVT_KEY_UP == etype;

  if( isakey && DoKey( (wxKeyEvent&)evt ) ) {
    return true;  // Ret-type is int!?!?!
  }

  return wxApp::FilterEvent(evt);
}

void WXTris::DoCmd( int cmd ) {
  hit_t hit = HIT_NONE;

  switch( cmd ) {
    case CMD_STEP:
      tetrix.Increment();
      break;
    case CMD_START:
      tetrix.Start();
      timer.Start(1000);
      break;
    case CMD_PAUSE:
      tetrix.Pause( tetrix.Running() );
      break;
    case CMD_STOP:
      tetrix.Stop();
      tetrix.Reset(false);
      timer.Stop();
      break;
    case CMD_CLEAR:
      tetrix.Reset(false);
      break;
    case CMD_PREVIEW:
      tetrix.Preview();
      break;
    case CMD_UP:        break; // ???
    case CMD_DOWN:      hit = tetrix.Move( MOVE_DOWN ); break;  
    case CMD_LEFT:      hit = tetrix.Move( MOVE_LEFT ); break;
    case CMD_RIGHT:     hit = tetrix.Move( MOVE_RIGHT ); break;
    case CMD_ROT_LEFT:  hit = tetrix.Move( ROT_LEFT ); break;
    case CMD_ROT_RIGHT: hit = tetrix.Move( ROT_RIGHT ); break;
    case CMD_FALL:      hit = tetrix.Fall(); break;
    case wxID_EXIT:
      _frame->Close();
      break;
  }

  _frame->Refresh();
}


bool WXTris::DoKey( wxKeyEvent&evt ) {
  if( wxEVT_KEY_DOWN != evt.GetEventType() ) return false;

  auto key = evt.GetKeyCode();
  bool ret = true;

  switch( key ) {
  case WXK_DOWN:  DoCmd( CMD_DOWN ); break;
  case WXK_LEFT:
  case 'A':
  case 'a':
    DoCmd( CMD_LEFT );  
    break;
  case WXK_RIGHT: 
  case 'D':
  case 'd':
    DoCmd( CMD_RIGHT );
    break;
  case WXK_UP:    DoCmd( CMD_ROT_LEFT ); break;
  case WXK_SPACE: DoCmd( CMD_FALL ); break;
  case 'P':
  case 'p':
  case WXK_ESCAPE:
    DoCmd( CMD_PAUSE );
    break;
  case 'Q':
  case 'q':
    DoCmd( CMD_ROT_RIGHT );
    break;
  case 'E':
  case 'e':
    DoCmd( CMD_ROT_LEFT );
    break;
  default:
    ret = false;
  }

  return ret;
}

void WXTris::OnStep( wxTimerEvent &evt ) {
  DoCmd( CMD_STEP );
}

void WXTris::OnCmd( wxCommandEvent&evt ) {
  DoCmd( evt.GetId() );
}


} // namespace wxtris

IMPLEMENT_APP(wxtris::WXTris)
