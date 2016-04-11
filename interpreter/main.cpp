#include <iostream>
#include <igloo/igloo_alt.h>

#include "lisp.h"
#include "lisp_interpreter.h"
#include "lisp_utils.h"
#include "string_utils.h"


using namespace igloo;

Describe (Sanity_Test)
{
    It(test_01)
    {
        //Lisp lisp;
        std::string line = "(quote (testing 1 (2.0) -3.14e159))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("(testing 1 (2.0) -3.14e159)"));
    }
    It(test_02)
    {
        std::string line = "(+ 2 2)";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("4"));
    }
    It(test_03)
    {
        std::string line = "(+ (* 2 100) (* 1 10))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("210"));
    }
    It(test_04)
    {
        std::string line = "(if (> 6 5) (+ 1 1) (+ 2 2))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("2"));
    }
    It(test_05)
    {
        std::string line = "(if (< 6 5) (+ 1 1) (+ 2 2))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("4"));
    }
    It(test_06)
    {
        std::string line = "(define x 3)";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("x");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("3"));
        input = LispUtils::read("(+ x x)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("6"));
    }
    It(test_07)
    {
        std::string line = "(begin (define x 1) (set! x (+ x 1)) (+ x 1))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("3"));
    }
    It(test_08)
    {
        std::string line = "((lambda (x) (+ x x)) 5)";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals("10"));
    }
    It(test_09)
    {
        std::string line = "(define twice (lambda (x) (* 2 x)))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("(twice 5)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("10"));
    }
    It(test_10)
    {
        std::string line = "(define twice (lambda (x) (* 2 x)))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        line = "(define compose (lambda (f g) (lambda (x) (f (g x)))))";
        input = LispUtils::read(line);
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("((compose list twice) 5)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("10"));
    }
    It(test_11)
    {
        std::string line = "(define repeat (lambda (f) (compose f f)))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("((repeat twice) 5)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("20"));
        input = LispUtils::read("((repeat (repeat twice)) 5)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("80"));
    }
    It(test_12)
    {
        
        std::string line = "(define fact (lambda (n) (if (<= n 1) 1 (* n (fact (- n 1))))))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("(fact 3)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("6"));
        input = LispUtils::read("(fact 50)");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("30414093201713378043612608166064768844377641568960512000000000000"));
        
    }
    It(test_13)
    {
        
        std::string line = "(define abs (lambda (n) ((if (> n 0) + -) 0 n)))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("(list (abs -3) (abs 0) (abs 3))");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("(3 0 3)"));
        
    }
    It(test_14)
    {
        
        std::string line = "(define combine (lambda (f) (lambda (x y) (if (null? x) (quote ())(f (list (car x) (car y))((combine f) (cdr x) (cdr y)))))))";
        LispObject input = LispUtils::read(line);
        LispObject output = LispInterpreter::evaluate(input, lisp);
        std::string result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("(define zip (combine cons))");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals(""));
        input = LispUtils::read("(zip (list 1 2 3 4) (list 5 6 7 8))");
        output = LispInterpreter::evaluate(input, lisp);
        result = LispUtils::str(output);
        Assert::That(result, Equals("((1 5) (2 6) (3 7) (4 8))"));
    }
    Lisp lisp;
};
 
int main(int argc, const char * argv[])
{
    /*
    Lisp lisp;
    std::cout << "Welcome to the fancy new Prompt LISP INTERPRETER, type in LISP commands!\n";
    LispInterpreter::run("Prompt>", lisp);
    return 0;
     */
    return TestRunner::RunAllTests();
}
