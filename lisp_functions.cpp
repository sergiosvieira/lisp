#include "lisp_functions.h"


LispObject LispFunctions::car(const VectorOfLispObjects &lispObjects)
{
    LispObject lvalue = lispObjects[0];
    return lvalue;
}

LispObject LispFunctions::cdr(const VectorOfLispObjects &lispObjects)
{
    LispObject lvalue = lispObjects[0];
    if (lvalue.valuesSize() < 2)
    {
        return LispObject::kNil;
    }
    LispObject result(lvalue);
    result.clear();
    return result;
}

LispObject LispFunctions::append(const VectorOfLispObjects &lispObjects)
{
    LispObject result(TokenType::T_LIST);
    LispObject head = lispObjects[0];
    LispObject tail = lispObjects[1];
    VectorOfLispObjects::const_iterator it = tail.objects().begin();
    for (; it != tail.objects().end(); ++it)
    {
        result.objects().push_back(*it);
    }
    return result;
}

LispObject LispFunctions::cons(const VectorOfLispObjects &lispObjects)
{
    LispObject result(TokenType::T_LIST);
    LispObject head = lispObjects[0];
    LispObject tail = lispObjects[1];
    result.objects().push_back(head);
    VectorOfLispObjects::const_iterator it = tail.objects().begin();
    for (; it != tail.objects().end(); ++it)
    {
        result.objects().push_back(*it);
    }
    return result;
}

LispObject LispFunctions::list(const VectorOfLispObjects &lispObjects)
{
    LispObject result(TokenType::T_LIST);
    VectorOfLispObjects values(lispObjects);
    result.objects(values);
    return result;
}

LispObject LispFunctions::length(const VectorOfLispObjects &lispObjects)
{
    LispObject lvalue = lispObjects[0];
    return LispObject(TokenType::T_NUMBER, std::to_string(lvalue.valuesSize()));
}

LispObject LispFunctions::nullPointer(const VectorOfLispObjects &lispObjects)
{
    LispObject lvalue = lispObjects[0];
    return lvalue.isEmpty() ? LispObject::kTrue : LispObject::kFalse;
}
