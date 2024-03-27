#ifndef BINARYOPERATOR_HPP
#define BINARYOPERATOR_HPP

#include "primaryType.hpp"

namespace zhalilov
{
  class Operand;

  class BinOperator
  {
  public:
    enum class Type
    {
      Add,
      Subtraction,
      Multiply,
      Division,
      Mod
    };

    explicit BinOperator(Type);
    Operand operator()(const Operand &, const Operand &) const;
    PrimaryType getPrimaryType() const;

  private:
    Type type_;
  };
}

#endif
