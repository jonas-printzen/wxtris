#ifndef TRIX_VECS_HDR
#define TRIX_VECS_HDR

#include <trix/types.hpp>
#include <trix/ranges.hpp>

#include <vector>
#include <tuple>

namespace trix {

template <typename T>
class Mat {
public:
  using coord_t = uint16_t;
  using coords_t = std::tuple<uint16_t,uint16_t>;
  using value_type = T;
  using reference = T&;
  using range_t = Range2<value_type>;

  Mat( coord_t c, coord_t r ) : _cells(c*r), _cols(c), _rows(r) {}

  inline constexpr coord_t cols() const { return _cols; }
  inline constexpr coord_t rows() const { return _rows; }

  inline reference operator() ( coord_t col, coord_t row ) {
    return _cells.at(col+_cols*row);
  }

  inline reference operator [] ( const coords_t&col_row ) {
    return _cells.at(std::get<0>(col_row)+_cols*std::get<1>(col_row));
  }

  inline range_t range() {
    return range_t{ {0,0}, {_cols,_rows} };
  }

  inline void clear( value_type val ) {
    for( auto &cell : _cells ) {
      cell = val;
    }
  }

  inline void operator = ( const Mat &other ) {
    _cells = other._cells;
  }

#ifndef TRIX_TEST
private:
#endif
  inline const coord_t& arow( const coord_t&row ) const {
    if( row >= _rows ) throw std::out_of_range("bad row");
    return row;
  }

  inline const coord_t& acol( const coord_t&col ) const {
    if( col >= _cols ) throw std::out_of_range("bad col");
    return col;
  }

  inline const coord_t& arow( const coords_t&col_row ) const {
    if( std::get<1>(col_row) >= _rows ) throw std::out_of_range("bad row");
    return std::get<1>(col_row);
  }

  inline const coord_t& acol( const coords_t&col_row ) const {
    if( std::get<0>(col_row) >= _rows ) throw std::out_of_range("bad col");
    return std::get<0>(col_row);
  }

  std::vector<value_type> _cells;
  const coord_t _cols;
  const coord_t _rows;
};

using MatI = Mat<int>;

} // namespace trix


#endif  // TRIX_VECS_HDR
