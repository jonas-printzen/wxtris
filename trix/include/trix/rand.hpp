#ifndef TRIX_RAND_HDR
#define TRIX_RAND_HDR

#include <trix/types.hpp>

namespace trix {

/** @brief Specialized randomizer
 *
 * This class is the base of randomization for handling of
 * difficulty and modified distribution for resources and
 * frequencies. Using simple techniques we can combine
 * ranges of values, avoid repetitions and more.
 * 
 */
class Random {
public:
  using hard_t = float;   ///< How hard is 'it'

  Random( unsigned long seed=42 );

  /** @brief Get a uniform, unfiltered value from 0.0 to 1.0 */
  static float uniform();

  /** @brief Get a weighed power-filtered value
   *
   * By mixing linear and squared, we get gravity towards lower values.
   */
  static float square( float gear=0.21 );

  // TODO: Add game-specifics

};

} // namespace trix


#endif  // TRIX_RAND_HDR
