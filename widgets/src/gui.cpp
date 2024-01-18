
#include <trix/gui.hpp>

namespace trix {

GUI::GUI( chars_t name, unsigned style ) : _name(name) {
  std::cout << "GUI::GUI()" << std::endl;
  _frame_style = style;
}

GUI::~GUI() {
}

wxMenu& GUI::Menu( chars_t title ) {
  // Make sure we have a menu-bar
  if( nullptr == _menubar ) {
    _menubar = new wxMenuBar();
    _frame->SetMenuBar(_menubar);
  }

  // Make sure the menu exists
  string name(title);
  wxMenu *pMenu=nullptr;
  if( _menus.contains(name) ) {
    pMenu = _menus[name];
  } else {
    pMenu = new wxMenu();
    _menubar->Append( pMenu, title.data() );
    _menus[name] = pMenu;
  }

  return *pMenu;
}


wxMenuItem& GUI::MenuItem( chars_t title, int id, chars_t action ) {
    wxMenu &menu=Menu(title);

    // Create and insert the entry
    wxMenuItem *pItem = nullptr;
    if( action.empty() ) {
      pItem = menu.Append(id);
    } else {
      pItem = menu.Append(id,action.data());
    }

    return *pItem;
}

wxMenuItem& GUI::MenuItem( int id ) {
  throw std::runtime_error("Not implemented!");
}

bool GUI::OnInit() {
  if( wxApp::OnInit() ) {
    std::cout << "GUI::OnInit(): wxApp::OnInit() OK ..." << std::endl;
    _frame = new wxFrame( nullptr, wxID_ANY, _name.data(), wxDefaultPosition, wxDefaultSize, _frame_style );
    // TODO: Add more if generic
    std::cout << "GUI::OnInit(): done!" << std::endl;
    return true;
  }
  std::cout << "GUI::OnInit(): wxApp::OnInit() FAILED!" << std::endl;
  return false;
}

} // namespace trix
