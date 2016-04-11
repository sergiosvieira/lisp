#include "lisp.h"

#include "lisp_aritmetic_operators.h"
#include "lisp_comparison_operators.h"
#include "lisp_functions.h"


/** Public Methods **/
Lisp::Lisp(Lisp* next): m_next(next)
{
    initialize();
}

Lisp::Lisp(Lisp* next,
           const VectorOfLispObjects& parameters,
           const VectorOfLispObjects& arguments): m_next(next)
{
    initialize();
    VectorOfLispObjects::const_iterator argIt = arguments.begin();
    for (auto object: parameters)
    {
        m_lispObjects[object.value()] = *argIt++;
    }
}

MapOfLispObjects& Lisp::search(LispError& error,
                              const std::string& value)
{
    bool found = m_lispObjects.find(value) != m_lispObjects.end();
    if (found)
    {
        return m_lispObjects;
    }
    else
    {
    if (m_next != nullptr)
    {
        return m_next->search(error, value);
    }
    }
    return m_lispObjects;
}

LispObject& Lisp::operator[] (const std::string& value)
{
    return m_lispObjects[value];
}

/** Private Methods **/
void Lisp::initialize()
{
    m_lispObjects = {
        {"+", LispObject(LispAritmeticOperations::add)},
        {"-", LispObject(LispAritmeticOperations::sub)},
        {"*", LispObject(LispAritmeticOperations::mul)},
        {"/", LispObject(LispAritmeticOperations::div)},
        {">", LispObject(LispComparisonOperators::greaterThan)},
        {"<", LispObject(LispComparisonOperators::lessThan)},
        {"<=", LispObject(LispComparisonOperators::lessOrEqualThan)},
        {"nil", LispObject::kNil},
        {"#f", LispObject::kFalse},
        {"#t", LispObject::kTrue},
        {"append", LispObject(LispFunctions::append)},
        {"car", LispObject(LispFunctions::car)},
        {"cdr", LispObject(LispFunctions::cdr)},
        {"cons", LispObject(LispFunctions::cons)},
        {"length", LispObject(LispFunctions::length)},
        {"list", LispObject(LispFunctions::list)},
        {"null?", LispObject(LispFunctions::nullPointer)},
    };
}