#include "lisp_interpreter.h"

#include <iostream>
#include <stdexcept>
#include "lisp_errors.h"
#include "lisp_utils.h"
#include "lisp.h"


LispObject LispInterpreter::evaluate(LispObject body, Lisp& lisp)
{
    if (body.type() == TokenType::T_NUMBER)
    {
        return body;
    }
    else if (body.type() == TokenType::T_SYMBOL)
    {
        LispError error = LispError::NONE;
        MapOfLispObjects values = lisp.search(error, body.value());
        if (error == LispError::NONE)
        {
            values[body.value()].printValue(true);
            return values[body.value()];
        }
        else
        {
            throw std::runtime_error("Error searching values!");
        }
    }
    else if (body.isEmpty())
    {
        return LispObject::kNil;
    }
    LispObject head = body.objects()[0];
    if (head.type() == TokenType::T_SYMBOL)
    {
        if (head.value() == "quote")
        {
            // (quote exp)
            LispObject exp = body.objects()[1];
            return exp;
        }
        else if (head.value() == "if")
        {
            // (if test conseq [alt])
            LispObject test = body.objects()[1];
            std::string testResult = evaluate(test, lisp).value();
            if (testResult == "#f")
            {
                if (body.objects().size() < 4)
                {
                    return evaluate(LispObject::kNil, lisp);
                }
                else
                {
                    LispObject alt = body.objects()[3];
                    return evaluate(alt, lisp);
                }
            }
            else
            {
                LispObject conseq = body.objects()[2];
                return evaluate(conseq, lisp);
            }
        }
        else if (head.value() == "set!")
        {
            // (set! var exp)
            LispObject var = body.objects()[1];
            LispObject exp = body.objects()[2];
            LispError error = LispError::NONE;
            MapOfLispObjects& mapValues = lisp.search(error, var.value());
            if (error == LispError::NONE)
            {
                LispObject resultObject = evaluate(exp, lisp);
                mapValues[var.value()] = resultObject;
                return mapValues[var.value()];
            }
        }
        else if (head.value() == "define")
        {
            // (define var exp)
            LispObject var = body.objects()[1];
            LispObject exp = body.objects()[2];
            LispError error = LispError::NONE;
            MapOfLispObjects& mapValues = lisp.search(error, var.value());
            if (error == LispError::NONE)
            {
                LispObject resultObject = evaluate(exp, lisp);
                resultObject.printValue(false);
                mapValues[var.value()] = resultObject;
                return mapValues[var.value()];
            }
        }
        else if (head.value() == "lambda")
        {
            // (lambda (var*) exp)
            body.type(TokenType::T_LAMBDA);
            body.lisp(&lisp);
            return body;
        }
        else if (head.value() == "begin")
        {
            // (begin exp*)
            std::size_t size = body.objects().size() - 1;
            for (std::size_t i = 1; i < size; ++i)
            {
                evaluate(body.objects()[i], lisp);
            }
            LispObject exp = body.objects()[size];
            return evaluate(exp, lisp);
        }

    }
    LispObject procedure(evaluate(head, lisp));
    VectorOfLispObjects expression;
    VectorOfLispObjects::iterator it = body.objects().begin();
    ++it;
    for (; it != body.objects().end(); ++it)
    {
        expression.push_back(evaluate(*it, lisp));
    }
    if (procedure.type() == TokenType::T_LAMBDA)
    {
        Lisp* newLisp = new Lisp(&lisp, procedure.objects()[1].objects(), expression);
        return evaluate(procedure.objects()[2], *newLisp);
    }
    else if (procedure.type() == TokenType::T_PROC)
    {
        ProcedureType& proc = procedure.procedure();
        return proc(expression);
    }
    //std::cout << "not a function\n";
    //exit(1);
    return LispObject::kNil;
}

LispObject LispInterpreter::processLispSymbols(LispObject& object,
                                               Lisp& lisp)
{
    LispObject keyword = object;
    return LispObject::kNil;
}

void LispInterpreter::run(const std::string &prompt,
                          Lisp &lisp)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = "";
        std::getline(std::cin, line);
        if (line.length() == 0) continue;
        LispObject input = LispUtils::read(line);
        LispObject output = evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        if (result.length() > 0)
        {
            std::cout << result << '\n';
        }
    }
}
