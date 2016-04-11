#include "lisp_utils.h"

#include <ctype.h>
#include <algorithm>
#include <regex>
#include "lisp_object.h"
#include "string_utils.h"

/** Public Methoids **/
List LispUtils::listOfTokens(const std::string& line)
{
    List result;
    std::string expression = "";
    for (auto c: line)
    {
        if (c == ' ')
        {
            if (expression.length() > 0)
            {
                result.push_back(expression);
                expression = "";
            }
            continue;
        }
        if (c == '('
            || c == ')')
        {
            if (expression.length() > 0)
            {
                result.push_back(expression);
                expression = "";
            }
            result.push_back(std::string(1, c));
        }
        else
        {
            expression += std::string(1, c);
        }
    }
    if (expression.length() > 0
        && result.size() == 0)
    {
        result.push_back(expression);
    }
    return result;
}

LispObject LispUtils::tokenize(const std::string &token)
{
    bool first = isdigit(token[0]);
    bool second = isdigit(token[1]);
    if (first == true
        || (token[0] == '-'
            && second == true))
    {
        return LispObject(TokenType::T_NUMBER, token);
    }
    return LispObject(TokenType::T_SYMBOL, token);
}

LispObject LispUtils::tokenizeExpression(List &tokens)
{
    const std::string token(tokens.front());
    tokens.pop_front();
    if (token == "(")
    {
        LispObject result(TokenType::T_LIST);
        while (tokens.front() != ")")
        {
            result.objects().push_back(tokenizeExpression(tokens));
        }
        tokens.pop_front();
        return result;
    }
    else
    {
        return tokenize(token);
    }
}

LispObject LispUtils::read(const std::string &statement)
{
    List tokens(listOfTokens(statement));
    LispObject result = tokenizeExpression(tokens);
    return result;
}

std::string LispUtils::str(LispObject &object)
{
    if (object.type() == TokenType::T_LAMBDA
        || object.type() == TokenType::T_PROC)
    {
        return "";
    }
    else if (object.type() == TokenType::T_LIST)
    {
        VectorOfLispObjects lispObjects = object.objects();
        VectorOfLispObjects::const_iterator it = lispObjects.begin();
        std::string result("(");
        for (;it != lispObjects.end(); ++it)
        {
            LispObject obj(*it);
            result += str(obj) + ' ';
        }
        if (result[result.size() - 1] == ' ')
        {
            result.erase(result.size() - 1);
        }
        return result + ')';
    }
    return object.printValue() == true ? object.value() : "";
}

/** Private Methods **/
bool LispUtils::isValidChar(const char& value)
{
    return value != ' '
           && value != '('
           && value != ')';
}
