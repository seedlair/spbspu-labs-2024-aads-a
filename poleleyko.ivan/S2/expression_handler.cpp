#include "expression_handler.hpp"

void poleleyko::ExpressionHandler::parseExpression(const std::string& expression) {
    Queue<Token> rawTokens = tokenize(expression);
    Stack<Token> operatorStack;
    Queue<Token> outputQueue;

    while (!rawTokens.empty()) {
        const Token& token = rawTokens.front();
        switch (token.type) {
            case TokenType::Bracket:
                handleBrackets(token, operatorStack, outputQueue);
                break;
            case TokenType::BinaryOperator:
                handleBinaryOperator(token, operatorStack, outputQueue);
                break;
            case TokenType::Numeric:
                outputQueue.push(token);
                break;
            default:
                throw std::runtime_error("Invalid token encountered");
        }
        rawTokens.pop();
    }
    while (!operatorStack.empty()) {
        if (operatorStack.top().type == TokenType::BinaryOperator) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        } else {
            throw std::runtime_error("Mismatched expression");
        }
    }
    tokens = std::move(outputQueue);
}

long long poleleyko::ExpressionHandler::evaluate() {
    Queue<Token> tokenQueue = tokens;
    Stack<long long> valueStack;

    while (!tokenQueue.empty()) {
        const Token& token = tokenQueue.front();
        switch (token.type) {
            case TokenType::Numeric:
                valueStack.push(token.value.numeric);
                break;
            case TokenType::BinaryOperator:
                if (valueStack.size() < 2) {
                    throw std::runtime_error("Insufficient values for operation");
                }
                long long operand2 = valueStack.top(); valueStack.pop();
                long long operand1 = valueStack.top(); valueStack.pop();
                valueStack.push(computeBinaryOperation(token, operand1, operand2));
                break;
            default:
                throw std::runtime_error("Invalid token during evaluation");
        }
        tokenQueue.pop();
    }
    if (valueStack.size() != 1) {
        throw std::runtime_error("Final value count mismatch");
    }
    return valueStack.top();
}

poleleyko::Queue<Token> poleleyko::ExpressionHandler::tokenize(const std::string& expression) {
    Queue<Token> tokens;
    size_t position = 0;
    while (position < expression.size()) {
        size_t start = position;
        while (position < expression.size() && expression[position] != ' ') {
            position++;
        }
        if (start < position) {
            std::string tokenStr = expression.substr(start, position - start);
            tokens.push(createTokenFromString(tokenStr));
        }
        position++;
    }
    return tokens;
}

void poleleyko::ExpressionHandler::handleBrackets(const Token& token, Stack<Token>& operatorStack, Queue<Token>& outputQueue) {
    if (token.value.bracket == BracketType::RoundOpen) {
        operatorStack.push(token);
    } else {
        while (!operatorStack.empty() && operatorStack.top().type != TokenType::Bracket) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }
        if (operatorStack.empty() || operatorStack.top().type != TokenType::Bracket) {
            throw std::runtime_error("Unmatched closing bracket");
        }
        operatorStack.pop(); // Pop the opening bracket
    }
}

void poleleyko::ExpressionHandler::handleBinaryOperator(const Token& token, Stack<Token>& operatorStack, Queue<Token>& outputQueue) {
    while (!operatorStack.empty() && operatorStack.top().type == TokenType::BinaryOperator &&
           !hasHigherPrecedence(operatorStack.top(), token)) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }
    operatorStack.push(token);
}

bool poleleyko::ExpressionHandler::hasHigherPrecedence(const Token& lhs, const Token& rhs) {
    return getOperatorPrecedence(lhs) > getOperatorPrecedence(rhs);
}
