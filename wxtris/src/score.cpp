#include <wxtris/score.hpp>

namespace wxtris {

Score::Score( wxWindow *parent, const score_t &score  ) 
  : wxPanel(parent), score(score) {
  SetMinSize( wxSize(-1,50) );
}

} // namespace wxtris
