#ifndef TRIX_ROTATE_HDR
#define TRIX_ROTATE_HDR

#include <trix/types.hpp>

#include <tuple>

namespace trix {

enum rotate_t {
  SOUTH,
  WEST,
  NORTH,
  EAST
};

template <size_t S>
inline std::tuple<int,int> Rotate( std::tuple<int,int> xy, rotate_t rot ) {
  auto [x,y] = xy;
  switch( rot ) {
    case NORTH: return {(S-1)-x,(S-1)-y};
    case EAST: return {(S-1)-y,x};
    case WEST: return {y,(S-1)-x};
    default: return {x,y};
  }
}

} // namespace trix


#endif  // TRIX_ROTATE_HDR
