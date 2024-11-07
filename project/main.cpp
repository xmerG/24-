#include<iostream>
#include"expression_evaluator.hpp"
using namespace std;

int main(){
    string expression1="(2+5)*7.1/(1+(-2))";
    expression_evaluator e1(expression1);
    double solution=e1.evaluate();
    cout<<"the solution is"<<solution<<endl;
    return 0;
}