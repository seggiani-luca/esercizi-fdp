#include <iostream>
#include "btree.h"
using namespace std;
using namespace btree;

double MAX_ITERATION_STEPS = 1000;

char* ottieni_stringa() {
    char* str = new char[500];
    char c;
    c = cin.get();
    int count = 0;
    while(c != '\n' && count <= 499){
        str[count] = c;
        c = cin.get();
        count++;
    }
    return str;
}

double bisection_step(Expression*& expr, double lower, double upper, int& steps) {
    steps++;

    //check bounds
    if(expr->Evaluate(lower) > expr->Evaluate(upper)) {
        double t = lower;
        lower = upper;
        upper = t;
    }

    double average = (lower + upper) / 2;
    if(steps > MAX_ITERATION_STEPS) {
        return average;
    }
    double val = expr->Evaluate(average);
    if(val == 0)
        return average;
    if(val < 0) {
        return bisection_step(expr, average, upper, steps);
    } else { // val > 0
        return bisection_step(expr, lower, average, steps);
    }

}

list<double> bisect(Expression*& expr, double lower, double upper) {
    list<double> solutions;
    int steps = 0;
    double solution = bisection_step(expr, lower, upper, steps);
    if(abs(expr->Evaluate(solution)) < 0.1) { //discard obviously wrong solutions
        solutions.push_front(solution);
    }
    return solutions;
}

int main() {
    cout << "Type an expression:" << endl;
    char* str = ottieni_stringa();
    Expression* expr = new Expression(str);
    delete str;

    cout << endl;

    cout << "The expression was interpreted as: " << expr << endl << endl;
    if(!expr->isParametric()) {
        cout << "The given expression isn't parametric. Computing solution..." << endl;
        cout << "The result of the given expression is: " << expr->Evaluate();
    } else {
        while(true) {
            cout << "Select an operation." << endl;
            cout << "1: Find real solutions" << endl;
            cout << "2: Calculate derivative at point" << endl;
            cout << "3: Calculate definite integral" << endl;
            cout << "4: Evaluate at point" << endl;
            cout << "5: Exit program" << endl;
            char c;
            cin >> c;
            switch(c) {
                case '1': {
                    cout << "The algorithm will attempt to find all real solutions in a given interval." << endl;
                    double lower;
                    cout << "Input lower bound:" << endl;
                    cin >> lower;
                    double upper;
                    cout << "Input upper bound:" << endl;
                    cin >> upper;

                    list<double> solutions = bisect(expr, lower, upper);
                    int size = solutions.size();
                    if(size == 0) {
                        cout << "No solutions found!" << endl;
                        break;
                    }
                    if(size == 1) {
                        cout << "1 solution found:" << endl;
                        cout << solutions.front() << " (expression evaluates to " << expr->Evaluate(solutions.front()) << ")" << endl;
                        break;
                    }
                    cout << size << " solutions found:" << endl;
                    for(int i = 0; i < size; i++) {
                        cout << (i+1) << " solution: " << solutions.front() << " (expression evaluates to " << expr->Evaluate(solutions.front()) << ")" << endl;
                        solutions.pop_front();
                    }
                    break;
                }
                case '2': {
                    break;
                }
                case '3': {
                    break;
                }
                case '4': {
                    double point;
                    cout << "Input point:" << endl;
                    cin >> point;
                    cout << "The given expression at point " << point << " evaluates to " << expr->Evaluate(point);
                    break;
                }
                case '5': {
                    cout << "See you later!" << endl;
                    exit(0);
                    break;
                }
                default:
                    cout << "ERROR: Invalid operation" << endl;
                    break;
            }
            cout << endl << endl;
        }
    }
    delete expr;
    return 0;
}
