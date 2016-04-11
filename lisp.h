#ifndef lisp_hpp
#define lisp_hpp

#include "lisp_object.h"
#include "lisp_errors.h"

class Lisp
{
public:
    Lisp(Lisp* next = nullptr);
    Lisp(Lisp* next,
         const VectorOfLispObjects& parameters,
         const VectorOfLispObjects& arguments);
    MapOfLispObjects& search(LispError& error,
                            const std::string& value);
    LispObject& operator[] (const std::string& value);
protected:
    Lisp* m_next = nullptr;
    MapOfLispObjects m_lispObjects;
private:
    void initialize();
};

#endif /* lisp_hpp */
