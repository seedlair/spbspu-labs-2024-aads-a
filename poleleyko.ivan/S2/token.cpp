#include "token.hpp"
#include <stdexcept>

namespace poleleyko {
    
    bool areBracketsPaired(const Token& lhs, const Token& rhs) {
        bool both_brackets = (lhs.type_ == token_type::bracket && rhs.type_ == token_type::bracket);
        return (both_brackets && (static_cast<int>(lhs.value_.bracket_) + static_cast<int>(rhs.value_.bracket_) == 0));
    }

    size_t getOperatorPrecedence(const Token& token) {
        switch (token.value_.bin_operator_) { // Убедитесь, что доступ к членам правильный
            case BinOperatorType::plus:
            case BinOperatorType::minus:
                return 1;
            case BinOperatorType::mult:
            case BinOperatorType::div:
            case BinOperatorType::mod:
                return 2;
            default:
                return 0;
        }
    }

    bool lessBinOperatorPriority(const Token& lhs, const Token& rhs) {
        return getOperatorPrecedence(lhs) < getOperatorPrecedence(rhs);
    }

    long long binOperatorResult(const Token& bin_operator, long long a, long long b) {
        switch (bin_operator.value_.bin_operator_) {
            case BinOperatorType::plus:
                return safePlus(a, b);
            case BinOperatorType::minus:
                return safeMinus(a, b);
            case BinOperatorType::mult:
                return safeMult(a, b);
            case BinOperatorType::div:
                return safeDiv(a, b);
            case BinOperatorType::mod:
                return safeMod(a, b);
            default:
                throw std::invalid_argument("Invalid operator");
        }
    }
}
