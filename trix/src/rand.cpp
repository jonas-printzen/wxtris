#include <trix/rand.hpp>

#include <random>

// The basic uniform randomizer, almost never used without filtering
static std::mt19937 rnd_gen;
static std::uniform_real_distribution<float> rnd_real(0.f,1.0f);

namespace trix {

Random::Random( unsigned long seed ) {
  // There should be only one ...
  rnd_gen.seed(seed);
}

float Random::uniform() {
  return rnd_real(rnd_gen);
}

float square( float gear ) {
  float base = rnd_real(rnd_gen);
  return 0.5f * (gear*base + (1.0-gear)*base*base);
}


} // namespace trix
