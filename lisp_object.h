#ifndef lisp_object_h
#define lisp_object_h

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "tokens.h"

class LispObject;
class Lisp;

using VectorOfLispObjects = std::vector<LispObject>;
using ProcedureType = std::function<LispObject(const VectorOfLispObjects&)>;
using MapOfLispObjects = std::map<std::string, LispObject>;

class LispObject
{
public:
    static const LispObject kTrue;
    static const LispObject kFalse;
    static const LispObject kNil;
    LispObject(TokenType type = TokenType::T_SYMBOL);
    LispObject(TokenType type, const std::string& value);
    LispObject(ProcedureType procedure);
    void value(const std::string& value);
    std::string value() const;
    TokenType type() const;
    void type(const TokenType &type);
    std::size_t valuesSize();
    bool isEmpty();
    void clear();
    VectorOfLispObjects& objects()
    {
        return m_lispObjects;
    }
    void objects(VectorOfLispObjects& lispObjects)
    {
        m_lispObjects = lispObjects;
    }
    Lisp *lisp() const;
    void lisp(Lisp *lisp);
    bool printValue() const
    {
        return m_printValue;
    }
    void printValue(bool flag)
    {
        m_printValue = flag;
    }
    ProcedureType& procedure();
protected:
    TokenType m_type;
    std::string m_value = "";
    VectorOfLispObjects m_lispObjects;
    ProcedureType m_procedure;
    Lisp* m_lisp = nullptr;
    bool m_printValue = true;
};

#endif /* lisp_object_h */
