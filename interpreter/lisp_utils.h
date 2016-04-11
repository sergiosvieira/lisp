#ifndef lisp_utils_h
#define lisp_utils_h

#include <iostream>
#include <list>
#include "../tokens.h"

using List = std::list<std::string>;

class LispObject;

class LispUtils
{
public:
    static List listOfTokens(const std::string& str);
    static LispObject tokenize(const std::string & token);
    static LispObject tokenizeExpression(List& tokens);
    static LispObject read(const std::string & statement);
    static std::string str(LispObject& object);
private:
    static bool isValidChar(const char& symbol);
};

#endif /* lisp_utils_h */
