#include "lisp_aritmetic_operators.h"

#include <cstdlib>

/** Public Methods **/
LispObject LispAritmeticOperations::add(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        result += std::atol(current.value().c_str());
    }
    return LispObject(TokenType::T_NUMBER, std::to_string(result));
}

LispObject LispAritmeticOperations::sub(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        result -= std::atol(current.value().c_str());
    }
    return LispObject(TokenType::T_NUMBER, std::to_string(result));
}

LispObject LispAritmeticOperations::mul(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        result *= std::atol(current.value().c_str());
    }
    return LispObject(TokenType::T_NUMBER, std::to_string(result));
}

LispObject LispAritmeticOperations::div(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        result /= std::atol(current.value().c_str());
    }
    return LispObject(TokenType::T_NUMBER, std::to_string(result));
}