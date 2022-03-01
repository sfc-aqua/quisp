#pragma once

namespace quisp::backends::abstract {
  class IRandomNumberGenerator {
    public:
    IRandomNumberGenerator() = default;
    virtual ~IRandomNumberGenerator() {}
    virtual double doubleRandom() = 0;
  };
}
