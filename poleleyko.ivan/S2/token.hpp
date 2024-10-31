#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace poleleyko {
    enum class TokenType {
        Undefined = 0,
        Bracket,
        BinaryOperator,
        Numeric
    };

    enum class BracketType {
        RoundOpen = 1,
        RoundClose = -1
    };

    enum class BinOperatorType {
        Plus,
        Minus,
        Mult,
        Div,
        Mod
    };

    union TokenValue {
        BracketType bracket;
        BinOperatorType binOperator;
        long long numeric;
    };

    struct Token {
        Token() : type(TokenType::Undefined), value() {}
        Token(TokenType type, TokenValue value) : type(type), value(value) {}
        const TokenType type;
        const TokenValue value;
    };

    bool hasLowerPrecedence(const Token& lhs, const Token& rhs);
    bool areBracketsPaired(const Token& lhs, const Token& rhs);
    long long computeBinaryOperation(const Token& operation, long long left, long long right);
}

#endif
