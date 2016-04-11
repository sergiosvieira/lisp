#ifndef lisp_comparison_operators_h
#define lisp_comparison_operators_h

#include "lisp_object.h"

class LispComparisonOperators
{
public:
    static LispObject greaterThan(const VectorOfLispObjects& lispObjects);
    static LispObject lessThan(const VectorOfLispObjects& lispObjects);
    static LispObject lessOrEqualThan(const VectorOfLispObjects& lispObjects);    
};
#endif /* lisp_comparison_operators_h */
