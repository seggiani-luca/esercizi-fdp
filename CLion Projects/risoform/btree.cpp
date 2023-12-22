#include "btree.h"
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
using namespace btree;

operation_type::operation_type(char symbol, associativity_type associativity, int precedence) {
    this->symbol = symbol;
    this->associativity = associativity;
    this->precedence = precedence;
}

function_type::function_type(char *name, long double (*func)(long double)) {
    this->name = name;
    //this->aliases = aliases;
    this->func = func;
}

Term::Term(term_type type, term_data_field* data) {
    this->type = type;
    this->data = data;
}

const int OP_NUM = 7;

struct operation_type operations[OP_NUM] = {
        //parenthesis
        operation_type('(', btree::left, 0),
        operation_type(')', btree::left, 0),
        //operators
        operation_type('+', btree::left, 1),
        operation_type('-', btree::left, 1),
        operation_type('*', btree::left, 2),
        operation_type('/', btree::left, 2),
        operation_type('^', btree::right, 3)
};

operation_type* get_operation_index(char*& string) {
    for(int i = 0; i < OP_NUM; i++) {
        if(*string == operations[i].symbol) {
            //found it
            return &operations[i];
        }
    }
    cout << "ERROR: Invalid token" << endl;
    exit(1);
}

const int FUN_NUM = 8;

struct function_type functions[FUN_NUM] = {
        function_type("sin", sin),
        function_type("cos", cos),
        function_type("tan", tan),
        function_type("arcsin", asin),
        function_type("arccos", acos),
        function_type("arctan", atan),
        function_type("sqrt", sqrt),
        function_type("abs", abs)
};

function_type* get_function(char*& string) {
    for(int i = 0; i < FUN_NUM; i++) {
        if(strcmp(functions[i].name, string) == 0) {
            //found it
            return &functions[i];
        }
    }
    cout << "ERROR: Undefined function" << endl;
    exit(3);
}

long double evaluate_function(struct function* f, long double val) {
    return (*f->prototype->func)(val);
}

inline void push_operation(char*& string, list<Term*>& list) {
    term_data_field* data_field = new term_data_field();
    data_field->oper = get_operation_index(string);
    Term* term = new Term(operation, data_field);
    list.push_front(term);
}

inline void push_value(char*& string, list<Term*>& list) {
    bool negative = false;
    if(*string == '-') { //negative
        string++;
        negative = true;
    }
    long double num = *string - 48;
    int decimals = 0;
    while ((*(string + 1) >= 48 && *(string + 1) <= 57) ||
           *(string + 1) == 46) { //don't bleed into next token
        string++;
        if (*string == 46) {
            if (decimals > 0) {
                cout << "ERROR: Too many commas" << endl;
                exit(2);
            }
            decimals++;
            continue;
        }
        if (decimals > 0) {
            num += (*string - 48) / pow(10, decimals);
            decimals++;
        } else {
            num *= 10;
            num += *string - 48;
        }
    }

    //got the number
    term_data_field *data_field = new term_data_field();
    if(negative) {
        data_field->value = -num;
    } else {
        data_field->value = num;
    }
    Term *term = new Term(value, data_field);
    list.push_front(term);
}

void string_to_term_array(char* string, list<Term*>& list, bool& parametric);
void push_function(char*& string, list<Term*>& l, bool& parametric) {
    char* temp_string = new char[200];

    //first get id
    int i = 0;
    while (*string != '(') {
        if(i >= 200) {
            cout << "ERROR: Function name not found" << endl;
            exit(4);
        }
        temp_string[i] = *string;
        string++;
        i++;
    }
    temp_string[i] = '\0';
    string++; //get rid of (

    function_type* prototype = get_function(temp_string);
    term_data_field *data_field = new term_data_field;
    struct function* fun = new struct function();
    fun->prototype = prototype;

    //get argument
    i = 0;
    int nests = 0; //pesky
    while (*string != ')' || nests != 0) {
        if(i >= 200) {
            cout << "ERROR: Function argument too long" << endl;
            exit(4);
        }
        if(*string == '(') {
            nests++;
        }
        if(*string == ')') {
            nests--;
        }
        temp_string[i] = *string;
        string++;
        i++;
    }
    temp_string[i] = '\0';

    Expression* arg = new Expression(temp_string);
    fun->argument = arg;
    data_field->fun = fun;

    if(arg->isParametric()) {
        parametric = true;
    }

    delete[] temp_string;

    //push parenthesis around argument
    Term *term = new Term(function, data_field);
    l.push_front(term);
}

void string_to_term_array(char* string, list<Term*>& list, bool& parametric) {
    bool expecting_value = true;
    while(*string != '\0') {
        if(*string == ' ') {
            string++;
            continue;
        }

        if(*string >= 48 && *string <= 57) { //value
            push_value(string, list);
            string++;
            expecting_value = false;

            //hack to allow for things like "2x"
            if(*string == 'x') { //push x as a parameter
                //push multiplication
                term_data_field* oper_field = new term_data_field();
                oper_field->oper = &operations[4];
                Term* oper_term = new Term(operation, oper_field);
                list.push_front(oper_term);

                //push parameter
                term_data_field *data_field = new term_data_field();
                Term *term = new Term(parameter, data_field);
                list.push_front(term);
                string++;

                parametric = true;
            }

            continue;
        }

        if(*string == 'x') { //push x as a parameter
            term_data_field *data_field = new term_data_field();
            Term *term = new Term(parameter, data_field);
            list.push_front(term);
            string++;

            parametric = true;

            continue;
        }

        if(*string >= 97 && *string <= 122) { //function
            push_function(string, list, parametric);
            string++;
            expecting_value = false;
            continue;
        }

        if(*string == '-' && expecting_value && (*(string + 1) >= 48 && *(string + 1) <= 57 )) { //! special case for negative numbers!
            push_value(string, list);
            string++;
            continue;
        }

        //operator
        push_operation(string, list);
        string++;
        expecting_value = true;
    }
}

void term_array_to_postfix(list<Term*>& terms, list <Term*>& postfix) {
    int size = terms.size();

    //define operator stack
    list <Term*> operator_stack;

    for(int i = 0; i < size; i++) {
        Term* term = terms.back();
        terms.pop_back();
        switch(term->type) {
            case value: {
                postfix.push_front(term);
                break;
            }
            case parameter: {
                postfix.push_front(term);
                break;
            }
            case function: {
                postfix.push_front(term);
                break;
            }
            case operation: {
                //special clauses for parenthesis
                if(term->data->oper->symbol == '(') { //left parenthesis
                    operator_stack.push_front(term);
                    break;
                }
                if(term->data->oper->symbol == ')') { //right parenthesis
                    Term* next_oper = operator_stack.front();
                    operator_stack.pop_front();
                    while(!(next_oper->type == operation && next_oper->data->oper->symbol == '(')) {
                        if(operator_stack.size() <= 0) {
                            cout << "ERROR: Mismatched parenthesis" << endl;
                            exit(5);
                        }
                        postfix.push_front(next_oper);
                        next_oper = operator_stack.front();
                        operator_stack.pop_front();
                    }
                    if(next_oper->data->oper->symbol == '(') {
                        delete next_oper;
                    }
                    delete term;
                    //operator_stack.pop_front(); //pop parenthesis
                    if(operator_stack.size() <= 0) {
                        break;
                    }
                    next_oper = operator_stack.front();
                    /*
                    if(next_oper->type == function) {
                        postfix.push_front(next_oper);
                        operator_stack.pop_front();
                    }
                     */
                    break;
                }
                //first check for parenthesis and operator associativity
                while(operator_stack.size() > 0) {
                    Term* next_oper = operator_stack.front();
                    //the next condition basically checks if the next operation is either a
                    // parenthesis or an operator with higher precedence than the current one
                    if(!(next_oper->type == operation && next_oper->data->oper->symbol == '(')
                       && (next_oper->data->oper->precedence > term->data->oper->precedence ||
                           (next_oper->data->oper->precedence == term->data->oper->precedence &&
                            term->data->oper->associativity == btree::left))) {
                        //pop operator onto postfix string and remove it from stack
                        postfix.push_front(next_oper);
                        operator_stack.pop_front();
                    } else {
                        break;
                    }
                }
                operator_stack.push_front(term);
                break;
            }
        }
    }
    //unload operator stack
    size = operator_stack.size();
    for(int i = 0; i < size; i++) {
        Term* oper = operator_stack.front();
        if(oper->type == operation && (oper->data->oper->symbol == '(' ||  oper->data->oper->symbol == ')')) {
            cout << "ERROR: Too many parenthesis" << endl;
            exit(6);
        }
        operator_stack.pop_front();
        postfix.push_front(oper);
    }
}

//std::ostream operator<<(std::ostream& s, Expression& expr) {
void print_terms(list<Term*> terms) {
    int size = terms.size();
    for(int i = 0; i < size; i++) {
        Term* term = terms.back();
        terms.pop_back();
        if(term->type == value) {
            cout << term->data->value << " ";
        }
        if(term->type == parameter) {
            cout << "x ";
        }
        if(term->type == operation) {
            cout << term->data->oper->symbol << " ";
        }
        if(term->type == function) {
            cout << term->data->fun->prototype->name << "(";
            cout << term->data->fun->argument << ")";
        }
    }
    cout << endl;
}

ostream& btree::operator<<(ostream& s, Expression*& expr) {
    cout << expr->string;
    return s;
}

void remove_trailing(char*& str) {
    bool dot = false;
    int zeroes = 0;
    int count = 0;
    for(int i = 0; *(str + i) != '\0'; i++) {
        if(*(str + i) == '.') {
            dot = true;
        }
        if(dot) {
            if(*(str + i) == '0') {
                zeroes++;
            } else {
                zeroes = 0;
            }
        }
        count++;
    }
    str[count - zeroes] = '\0';
    if(*(str + (count-zeroes-1)) == '.') {
        str[count-zeroes-1] = '\0';
    }
}

void btree::precalculate_string(list<Term*> terms, char*& str) {
    str = new char[500];
    int size = terms.size();
    for (int i = 0; i < size; i++) {
        if(size >= 499) {
            cout << "ERROR: String too long" << endl;
            exit(7);
        }
        Term *term = terms.back();
        terms.pop_back();
        switch (term->type) {
            case value: {
                char* number = const_cast<char*>(to_string(term->data->value).c_str());
                remove_trailing(number);
                strcat(str, number); //ehhh
                break;
            }
            case parameter: {
                strcat(str, "x");
                break;
            }
            case function: {
                strcat(str, term->data->fun->prototype->name);
                char* substring = new char[200];
                strcat(str, "(");
                strcat(str, term->data->fun->argument->string);
                strcat(str, ")");
                break;
            }
            case operation: {
                char* ptr = &term->data->oper->symbol;
                strcat(str, ptr);
            }
        }
        if(i != size-1) {
            strcat(str, " ");
        }
    }
}

Expression::Expression(char *string) {
    parametric = false;
    //tokenize string
    list<Term*> terms;
    string_to_term_array(string, terms, parametric);

    //set expression string
    precalculate_string(terms, this->string); //use well formatted string


    cout << "Infix terms before conversion: " << endl;
    print_terms(terms);
    cout << endl;


    //convert term array to post-fix notation using the shunting yard algorithm
    //first define operator stack and output tree
    list<Term*> postfix_terms;
    term_array_to_postfix(terms, postfix_terms);


    cout << "Postfix terms before conversion: " << endl;
    print_terms(postfix_terms);
    cout << endl;


    //throw the postfix expression in the binary tree
    size = postfix_terms.size();
    list <Term*> stack;
    for(int i = 0; i < size; i++) {
        Term* term = postfix_terms.back();
        postfix_terms.pop_back();
        if(term->type == operation) {
            if(stack.size() <= 0) {
                cout << "ERROR: Malformed expression" << endl;
                exit(8);
            }
            term->right = stack.front();
            stack.pop_front();
            if(stack.size() <= 0) {
                cout << "ERROR: Malformed expression" << endl;
                exit(8);
            }
            term->left = stack.front();
            stack.pop_front();
            stack.push_front(term);
        } else {
            stack.push_front(term);
        }
    }
    root = stack.front();
    this->size = size;
    if(stack.size() <= 0) {
        cout << "ERROR: Empty expression" << endl;
        exit(9);
    }
    stack.pop_front();
}

//messy memory management

void delete_term(Term* term) {
    delete term->left;
    delete term->right;
    delete term;
}

Expression::~Expression() {
    delete_term(root);
}

Term::~Term() {
    if(type == function) {
        delete data->fun->argument;
    }
}

//evaluation

long double operate(operation_type* oper, long double l, long double r) {
    switch(oper->symbol) {
        case '+': {
            return l+r;
        }
        case '-': {
            return l-r;
        }
        case '*': {
            return l*r;
        }
        case '/': {
            return l/r;
        }
        case '^': {
            return pow(l, r);
        }
        default:
            return 0;
    }
}

long double Expression::eval(Term* term, const float& param) {
    if(term == nullptr) {
        return 0;
    }
    if(term->type == value) {
        return term->data->value;
    }
    if(term->type == parameter) {
        return param;
    }
    if(term->type == function) {
        return evaluate_function(term->data->fun, term->data->fun->argument->eval(term->data->fun->argument->root, param));
    }
    long double l = eval(term->left, param);
    long double r = eval(term->right, param);
    return operate(term->data->oper, l, r);
}

long double Expression::Evaluate(float param) {
    return eval(root, param);
}
