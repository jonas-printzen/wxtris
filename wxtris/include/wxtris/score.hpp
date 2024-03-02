#ifndef WXTRIS_SCORE_HDR
#define WXTRIS_SCORE_HDR

#include <trix/types.hpp>
#include <trix/tetrix.hpp>
#include <wx/wx.h>

namespace wxtris {

using namespace trix;

class Score : public wxPanel {
public:
  using score_t = Tetrix::score_t;

  Score( wxWindow *parent, const score_t &score );

  const score_t &score;
};

} // namespace wxtris


#endif  // WXTRIS_SCORE_HDR
