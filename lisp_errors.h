#ifndef lisp_errors_h
#define lisp_errors_h

enum class LispError
{
    NONE,
    UNBOUND_SYMBOL,
    FATAL_ERROR
};

#endif /* lisp_errors_h */
