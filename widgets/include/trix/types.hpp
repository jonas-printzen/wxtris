#ifndef TRIX_TYPES_HDR
#define TRIX_TYPES_HDR

#include <stdint.h>
#include <wx/wx.h>

#include <string>
#include <string_view>
#include <map>

namespace trix {

using std::string;
using chars_t = std::string_view;

inline std::ostream& operator << ( std::ostream&out, const wxPoint &p ) {
  out << p.x << "," << p.y;
  return out;
}

inline std::ostream& operator << ( std::ostream&out, const wxSize &sz ) {
  out << sz.x << "," << sz.y;
  return out;
}

inline std::ostream& operator << ( std::ostream&out, const wxRect &rec ) {
  out << rec.GetPosition() << ", " << rec.GetSize();
  return out;
}

inline int operator | (int i, wxDirection d) {
  return i | (int)d;
}

} // namespace trix

#endif  // TRIX_TYPES_HDR
