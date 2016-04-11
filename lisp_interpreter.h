#ifndef lisp_interpreter_h
#define lisp_interpreter_h

#include "lisp_object.h"

class LispInterpreter
{
public:
    static LispObject evaluate(LispObject object,
                               Lisp& lisp);
    static void run(const std::string& prompt,
                    Lisp& lisp);
protected:
private:
    static LispObject processLispSymbols(LispObject& object,
                                         Lisp &lisp);
};

#endif /* lisp_interpreter_h */
