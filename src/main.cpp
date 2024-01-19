#include <trix/gui.hpp>
#include <trix/buttons.hpp>
#include <trix/blocks.hpp>

using namespace trix;

class WXTris : public GUI {
public:
  using GUI::MenuItem;

  WXTris() : GUI("WXTris") {}

  bool OnInit() override {
    // Let base initialize
    if( GUI::OnInit() ) {
      std::cout << "WXTris::OnInit() ..." << std::endl;

      MenuItem( "Game", wxID_ANY,  "Start", &WXTris::OnMenu,this );
      MenuItem( "Game", wxID_EXIT, "Quit", &WXTris::OnMenu,this );
      CreateStatusBar(3);

      blocks = new Blocks( _frame, {10,20}, 42 );
      blocks->cells(1,1) = Blocks::GRAY;
      blocks->cells(2,1) = Blocks::WHITE;

      blocks->cells(1,2) = Blocks::DARK_RED;
      blocks->cells(2,2) = Blocks::RED;
      blocks->cells(3,2) = Blocks::LIGHT_RED;

      blocks->cells(1,3) = Blocks::DARK_YELLOW;
      blocks->cells(2,3) = Blocks::YELLOW;
      blocks->cells(3,3) = Blocks::LIGHT_YELLOW;

      blocks->cells(1,4) = Blocks::DARK_GREEN;
      blocks->cells(2,4) = Blocks::GREEN;
      blocks->cells(3,4) = Blocks::LIGHT_GREEN;

      blocks->cells(1,5) = Blocks::DARK_BLUE;
      blocks->cells(2,5) = Blocks::BLUE;
      blocks->cells(3,5) = Blocks::LIGHT_BLUE;

      blocks->cells(1,6) = Blocks::DARK_CYAN;
      blocks->cells(2,6) = Blocks::CYAN;
      blocks->cells(3,6) = Blocks::LIGHT_CYAN;

      blocks->cells(1,7) = Blocks::DARK_MAGENTA;
      blocks->cells(2,7) = Blocks::MAGENTA;
      blocks->cells(3,7) = Blocks::LIGHT_MAGENTA;

      buttons = new Buttons(_frame, {120,-1});
      buttons->Button("Hepp", &WXTris::OnButt, this );
      buttons->Button("Hopp", &WXTris::OnButt, this );

      wxSizer *psz = new wxBoxSizer(wxVERTICAL);
      psz->Add( new wxPanel, 1); // Pad at top
      psz->Add( blocks, 0, wxALIGN_CENTER | wxALL, 10 );
      psz->Add( new wxPanel, 1); // Pad between
      psz->Add( buttons, 0, wxBOTTOM|wxRIGHT, Buttons::MARGIN );

      SetSizerAndFit( psz );
      Show(true);
      std::cout << "WXTris::OnInit() done!" << std::endl;
      return true;
    }
    std::cout << "WXTris::OnInit() failed!" << std::endl;
    return false;
  }

  void OnButt (wxCommandEvent &evt ) {
    wxButton *pb = (wxButton*)evt.GetEventObject();
    std::cout << "Button "<< evt.GetId() << " clicked! '" << pb->GetLabel() << "'" << std::endl;
  }

  void OnMenu( wxCommandEvent&evt ) {
    std::cout << "Menu selected " << evt.GetId() << std::endl;
    if( wxID_EXIT == evt.GetId() ) {
      _frame->Close();
    }
  }

private:
  Blocks  *blocks=nullptr;
  Buttons *buttons=nullptr;

};

IMPLEMENT_APP(WXTris)
