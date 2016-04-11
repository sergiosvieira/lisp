#include "lisp_object.h"

const LispObject LispObject::kTrue = LispObject(TokenType::T_SYMBOL, "#t");
const LispObject LispObject::kFalse = LispObject(TokenType::T_SYMBOL, "#f");
const LispObject LispObject::kNil = LispObject(TokenType::T_SYMBOL, "nil");

/** Public Methods **/
LispObject::LispObject(TokenType type): m_type(type) {}

LispObject::LispObject(TokenType type,
                     const std::string& value): m_type(type), m_value(value) {}

LispObject::LispObject(ProcedureType procedure): m_type(TokenType::T_PROC), m_procedure(procedure) {}

void LispObject::value(const std::string& value)
{
    m_value = value;
}

std::string LispObject::value() const
{
    return m_value;
}

std::size_t LispObject::valuesSize()
{
    return m_lispObjects.size();
}

bool LispObject::isEmpty()
{
    return m_lispObjects.empty();
}

void LispObject::clear()
{
    m_lispObjects.erase(m_lispObjects.begin());
}

Lisp *LispObject::lisp() const
{
    return m_lisp;
}

void LispObject::lisp(Lisp *lisp)
{
    m_lisp = lisp;
}

ProcedureType &LispObject::procedure() 
{
    return m_procedure;
}

TokenType LispObject::type() const
{
    return m_type;
}

void LispObject::type(const TokenType &type)
{
    m_type = type;
}
