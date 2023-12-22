#include <list>
#include <iostream>

#ifndef RISOFORM_BTREE_H
#define RISOFORM_BTREE_H

namespace btree {

    enum associativity_type {
        left, right
    };

    struct operation_type {
        char symbol;
        associativity_type associativity;
        int precedence;

        operation_type(char symbol, associativity_type associativity, int precedence);
    };

    struct function_type {
        char* name;
        //char* aliases;
        long double (*func)(long double);

        function_type(char* name, long double (*func)(long double));
    };

    class Expression; //fuck c++
    struct function {
        Expression* argument = nullptr;
        function_type* prototype;
    };

    union term_data_field {
        long double value;
        operation_type* oper = nullptr;
        function* fun;
    };

    enum term_type {
        value, operation, function, parameter
    };

    struct Term {
        term_type type;
        term_data_field *data;
        Term *left;
        Term *right;

        Term(term_type type, term_data_field *data);
        ~Term();
    };

    class Expression {
    private:
        Term *root;
        int size;
        long double eval(Term* term, const float& param);
        char* string;
        bool parametric;
    public:
        Expression(char *string);
        ~Expression();
        long double Evaluate(float param = 0);

        //access members
        bool isParametric() {
            return parametric;
        }

        //friends!!!
        friend std::ostream& operator<<(std::ostream& s, Expression*& expr);
        friend void precalculate_string(std::list<Term*> terms, char*& str);
    };

    std::ostream& operator<<(std::ostream& s, Expression*& expr);
    void precalculate_string(std::list<Term*> terms, char*& str);

}

#endif //RISOFORM_BTREE_H
