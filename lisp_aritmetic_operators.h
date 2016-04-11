#ifndef lisp_aritmetic_operators_h
#define lisp_aritmetic_operators_h

#include "lisp_object.h"

class LispAritmeticOperations
{
public:
    static LispObject add(const VectorOfLispObjects& lispValue);
    static LispObject sub(const VectorOfLispObjects& lispValue);
    static LispObject mul(const VectorOfLispObjects& lispValue);
    static LispObject div(const VectorOfLispObjects& lispValue);
};



#endif /* lisp_aritmetic_operators_h */
