#ifndef lisp_functions_h
#define lisp_functions_h

#include "lisp_object.h"

class LispFunctions
{
public:
    static LispObject car(const VectorOfLispObjects& lispObjects);
    static LispObject cdr(const VectorOfLispObjects& lispObjects);
    static LispObject append(const VectorOfLispObjects& lispObjects);
    static LispObject cons(const VectorOfLispObjects& lispObjects);
    static LispObject list(const VectorOfLispObjects& lispObjects);
    static LispObject length(const VectorOfLispObjects& lispValue);
    static LispObject nullPointer(const VectorOfLispObjects& lispValue);
};

#endif /* lisp_functions_h */
