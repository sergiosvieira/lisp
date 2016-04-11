#include "lisp_comparison_operators.h"

#include <cstdlib>

LispObject LispComparisonOperators::greaterThan(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        if (result <= std::atol(current.value().c_str()))
        {
            return LispObject::kFalse;
        }
    }
    return LispObject::kTrue;
}

LispObject LispComparisonOperators::lessThan(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        if (result <= std::atol(current.value().c_str()))
        {
            return LispObject::kTrue;
        }
    }
    return LispObject::kFalse;
}

LispObject LispComparisonOperators::lessOrEqualThan(const VectorOfLispObjects &lispObjects)
{
    VectorOfLispObjects::const_iterator it = lispObjects.begin();
    LispObject first = *it++;
    long result = std::atol(first.value().c_str());
    for (; it != lispObjects.end(); ++it)
    {
        LispObject current = *it;
        if (result > std::atol(current.value().c_str()))
        {
            return LispObject::kTrue;
        }
    }
    return LispObject::kFalse;
}
