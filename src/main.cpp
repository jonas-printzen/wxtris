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
      SetClientSize( 1024,768 );

      MenuItem( "Game", wxID_ANY, "Start", &WXTris::OnMenu,this );
      MenuItem( "Game", wxID_ANY, "Quit", &WXTris::OnMenu,this );
      CreateStatusBar(3);

      blocks = new Blocks( _frame, {10,20}, 42 );
      blocks->cells(1,1) = 1;

      buttons = new Buttons(_frame, {120,-1});
      buttons->Button("Hepp", &WXTris::OnButt, this );
      buttons->Button("Hopp", &WXTris::OnButt, this );

      wxSizer *psz = new wxBoxSizer(wxVERTICAL);
      psz->Add( blocks, 1, wxEXPAND | wxALL, 10 );
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
  }

private:
  Blocks  *blocks=nullptr;
  Buttons *buttons=nullptr;

};

IMPLEMENT_APP(WXTris)
