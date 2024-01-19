#ifndef TRIX_RANGES_HDR
#define TRIX_RANGES_HDR

#include <trix/types.hpp>

#include <algorithm>
#include <tuple>

namespace trix {

using std::min;
using std::max;
using std::clamp;

/** @brief Enumerate container
 *
 * Enumerate container generating `tuple<index,value-ref>` from 0 to size.
 */
template<class C>
struct Enumerate {
  using size_type = typename C::size_type;
  Enumerate( C &on ) : c(on) {}

  struct iterator {
    using size_type = typename C::size_type;
    using value_type = std::tuple<const size_type,typename C::value_type&>;

    iterator( C &from, size_type i ) : c(from), i(i) {}

    inline value_type operator* () { return {i,c[i]}; }

    inline void operator ++ () { ++i; }

    inline bool operator != ( const iterator &other ) const { return i != other.i; }

    C &c;
    size_type i;
  };

  inline iterator begin() { return {c,0}; }
  inline iterator end() { return {c,c.size()}; }

  C &c;
};

template <typename T>
inline constexpr void Clamp( T low, T&val, T high ) noexcept {
  val = std::clamp(val,low,high);
}

/** @brief Representation of bounds
 *
 * Bounds is a range of integers that can be both iterated and verified.
 * Use this to check or clamp to a pre-calculated range of values.
 */
template <typename T=int_fast64_t>
struct Bounds {
  static_assert(std::is_integral_v<T>, "Bound only for integers");
  using value_type = T;

  Bounds( value_type from, value_type to ) : first(from), last(to) {
    if( last<first ) throw std::runtime_error("Bounds reversed not supported!");;
  }
  Bounds( value_type to ) : first(0), last(to-1) {}

  /** @brief Check if value is in range */
  inline bool operator == ( value_type val ) const { return last >= val && val >= first;  }
  /** @brief Clamp value to range */
  inline value_type operator () ( value_type val ) const { return std::clamp(val,first,last); }
  /** @brief Get n'th value in range, clamped */
  inline value_type operator [] ( value_type val ) const { return std::clamp(first+val,first,last); }

  /** @brief Number of values in range */
  inline size_t size() const { return 1+last-first; }

  value_type first, last;
};

/** @brief A simple iteration on integers  */
template <typename T=int_fast64_t>
class Range {
public:
  using value_type = T;

  Range( value_type end ) : _step(1),  _end(end), _beg(0) {}

  Range( value_type beg, value_type end, value_type step={1} ) 
    : _step(step),  _end(end), _beg(beg) {
    if( !step ) throw std::runtime_error("Range with step 0!");
    if( end<=beg ) _end = _beg;
  }

  struct iter { 
    value_type _idx;
    const Range &_ctx;
    inline void operator ++() { _idx = std::min<value_type>(_idx+_ctx._step,_ctx._end); }
    inline const value_type& operator *() const { return _idx; }
    inline bool operator == ( const iter&other ) const {
      return _idx == other._idx;
    }
  };

  inline iter begin() { return {_beg,*this}; }
  inline iter end() { return {_end,*this}; }

  inline size_t size() const { return _end-_beg; }

private:
  value_type  _step;
  value_type  _end, _beg;
};

/** @brief A 2D (X,Y) - iteration 
 *
 * 
 */
template <typename T=int_fast64_t>
class Range2 {
public:
  using type_t = T;
  using value_type = std::tuple<type_t,type_t>;

  constexpr Range2( value_type beg, value_type end, value_type step = value_type{1,1} ) 
    :  _step(step), _end(end), _beg(beg) {
    if( !std::get<0>(step) || !std::get<1>(step) ) throw std::runtime_error("IRange2 with step 0!");
    if( (std::get<0>(end)<=std::get<0>(beg)) || (std::get<1>(end)<=std::get<1>(beg)) ) _end = _beg;
  }

  constexpr Range2( type_t d0, type_t d1 ) 
    :  _step({1,1}), _end({d0,d1}), _beg({0,0}) {
    if( (0 > d0) || (0 > d1) ) throw std::runtime_error("IRange2 Bad params!");
  }

  struct iter {
    value_type _idx; 
    const Range2 &_ctx;

    iter( const iter& ) = default;
    iter( const value_type&idx ,const Range2 &ctx )
      : _idx(idx), _ctx(ctx) {}

    inline void operator ++() {
      std::get<0>(_idx) = std::min<type_t>(std::get<0>(_idx)+std::get<0>(_ctx._step),std::get<0>(_ctx._end));
      if( std::get<0>(_idx) == std::get<0>(_ctx._end) ) {
        std::get<1>(_idx) = std::min<type_t>(std::get<1>(_idx)+std::get<1>(_ctx._step),std::get<1>(_ctx._end));
        if( std::get<1>(_idx) < std::get<1>(_ctx._end) ) {
          std::get<0>(_idx) = std::get<0>(_ctx._beg);
        }
      }
    }

    inline const value_type& operator *() const { return _idx; }

    inline bool operator == ( const iter&other ) const {
      return _idx == other._idx;
    }
  };

  inline iter begin() { return {_beg,*this}; }
  inline iter  end() { return {_end,*this}; }

  inline value_type size() const { 
    return {std::get<0>(_end)-std::get<0>(_beg), std::get<1>(_end)-std::get<1>(_beg)}; 
  }

private:
  value_type _step, _end, _beg;
};

/**
 * @}
 */

} // namespace trix

#endif  // TRIX_RANGES_HDR