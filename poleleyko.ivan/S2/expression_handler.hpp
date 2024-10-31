#ifndef EXPRESSION_HANDLER_HPP
#define EXPRESSION_HANDLER_HPP

#include <stdexcept>
#include <string>
#include <queue.hpp>
#include <stack.hpp>
#include "token.hpp"

namespace poleleyko {
    class ExpressionHandler {
    public:
        explicit ExpressionHandler(const std::string& expression) {
            parseExpression(expression);
        }
        long long evaluate();
    private:
        Queue<Token> tokens;

        void parseExpression(const std::string& expression);
        Queue<Token> tokenize(const std::string& expression);
        void handleBrackets(const Token& token, Stack<Token>& operatorStack, Queue<Token>& outputQueue);
        void handleBinaryOperator(const Token& token, Stack<Token>& operatorStack, Queue<Token>& outputQueue);
        bool hasHigherPrecedence(const Token& lhs, const Token& rhs);
    };
}

#endif
