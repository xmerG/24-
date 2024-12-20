#include<iostream>
#include"expression_evaluator.hpp"
using namespace std;

void testModify() {
    // 创建一个包含负数的表达式
    expression_evaluator expr1("((-3) + 4) * 5");
    cout << "Test modify : ((-3)+4)*5 " << expr1.evaluate() << endl;  // 预期输出: 5
}
void testIsLegal() {
    expression_evaluator expr1("3 + 4");
    expression_evaluator expr2("+3 + 4");
    expression_evaluator expr3("3 + + 4");
    expression_evaluator expr4("3 + (4 * 2");
    expression_evaluator expr5("3 + 4) * 2");
    expression_evaluator expr6("3 + 4 * 2 +");
    expression_evaluator expr7("/3 + 4 * 2 +");
    expression_evaluator expr8("1..2+2");
    expression_evaluator expr9("(2+3).5");
    expression_evaluator expr10("1.(2-1)");
    expression_evaluator expr11("3+()+2");

    cout << "Test isLegal for valid expression 3 + 4 " << (expr1.isLegal() ? "Pass" : "Fail") << endl;  // Pass
    cout << "Test isLegal for invalid expression +3 + 4 " << (expr2.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression 3 + + 4 " << (expr3.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression 3 + (4 * 2 " << (expr4.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression 3 + 4) * 2 " << (expr5.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression 3 + 4 * 2 +: " << (expr6.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression /3 + 4 * 2 + " << (expr7.isLegal() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isLegal for invalid expression 1..2+2 " << (expr8.isLegal() ? "Pass" : "Fail") <<endl;  //Fail
    cout << "Test isLegal for invalid expression (2+3).5 " << (expr9.isLegal() ? "Pass" : "Fail") <<endl;  //Fail
    cout << "Test isLegal for invalid expression 1.(2-1) " << (expr10.isLegal() ? "Pass" : "Fail") <<endl;  //Fail
    cout << "Test isLegal for invalid expression 3+()+2 " << (expr11.isLegal() ? "Pass" : "Fail") <<endl;  //Fail
}
void testIsMatch() {
    expression_evaluator expr1("3 + (4 * 2)");
    expression_evaluator expr2("3 + (4 * 2");
    expression_evaluator expr3("3 + 4 * (2 + 5)");
    expression_evaluator expr4("3 + 4 * 2)");

    cout << "Test isMatch for matching parentheses 3 + (4 * 2): " << (expr1.isMatch() ? "Pass" : "Fail") << endl;  // Pass
    cout << "Test isMatch for unbalanced parentheses 3 + (4 * 2: " << (expr2.isMatch() ? "Pass" : "Fail") << endl;  // Fail
    cout << "Test isMatch for matching parentheses 3 + 4 * (2 + 5): " << (expr3.isMatch() ? "Pass" : "Fail") << endl;  // Pass
    cout << "Test isMatch for unbalanced parentheses 3 + 4 * 2): " << (expr4.isMatch() ? "Pass" : "Fail") << endl;  // Fail
}
void testEvaluate() {
    expression_evaluator expr1("3 + 4");
    expression_evaluator expr2("5 * 6");
    expression_evaluator expr3("10 / 2");
    expression_evaluator expr4("2 * (3 + 4)");
    expression_evaluator expr5("2 + 3 * 5");
    expression_evaluator expr6("(3 + 4) * 5");
    expression_evaluator expr7("10 ^ 3");  
    expression_evaluator expr8("3 + (4 * 2)");  // 3 + (4 * 2) 应该是 3 + 8 = 11
    expression_evaluator expr9("2.1e1+3^2-(-2)*3"); //36


    cout << "Test evaluate (3 + 4) = " << expr1.evaluate() << endl;  // 7
    cout << "Test evaluate (5 * 6) = " << expr2.evaluate() << endl;  // 30
    cout << "Test evaluate (10 / 2) = " << expr3.evaluate() << endl;  // 5
    cout << "Test evaluate (2 * (3 + 4)) = " << expr4.evaluate() << endl;  // 14
    cout << "Test evaluate (2 + 3 * 5) = " << expr5.evaluate() << endl;  // 17
    cout << "Test evaluate (3 + 4) * 5 = " << expr6.evaluate() << endl;  // 35
    cout << "Test evaluate invalid expression 10 ^ 3 = " << expr7.evaluate() << endl;  //1000
    cout << "Test evaluate 3 + (4 * 2) = " << expr8.evaluate() << endl;  // 11
    cout << "Test evaluate 2.1e1+3^2-(-2)*3 = "<<expr9.evaluate()<<endl; //36
}
void testExponentiation() {
    expression_evaluator expr1("2 e 3");  // 2 * 10^3 = 2000
    expression_evaluator expr2("5 e 2");  // 5 * 10^2 = 500
    expression_evaluator expr3("1 e 4");  // 1 * 10^4 = 10000
    expression_evaluator expr4("3 e 0");  // 3 * 10^0 = 3

    cout << "Test exponentiation 2 e 3 = " << expr1.evaluate() << endl;  // 2000
    cout << "Test exponentiation 5 e 2 = " << expr2.evaluate() << endl;  // 500
    cout << "Test exponentiation 1 e 4 = " << expr3.evaluate() << endl;  // 10000
    cout << "Test exponentiation 3 e 0 = " << expr4.evaluate() << endl;  // 3
}
void testNegativeNumbers() {
    expression_evaluator expr1("((-3) + 4) * 5");
    expression_evaluator expr2("(-3) + 4");
    expression_evaluator expr3("3 + (-4)");

    cout << "Test negative numbers ((-3) + 4) * 5 =" << expr1.evaluate() << endl;  // 5
    cout << "Test negative numbers (-3) + 4=" << expr2.evaluate() << endl;  // 1
    cout << "Test negative numbers 3 + (-4) =: " << expr3.evaluate() << endl;  // -1
}
void testFloatingPoint() {
    expression_evaluator expr1("3.5 + 4.2");
    expression_evaluator expr2("5.5 * 2");
    expression_evaluator expr3("10.4 / 2");

    cout << "Test floating point numbers 3.5 + 4.2 =" << expr1.evaluate() << endl;  // 7.7
    cout << "Test floating point numbers 5.5 * 2 = " << expr2.evaluate() << endl;  // 11
    cout << "Test floating point numbers 10.4 / 2 = " << expr3.evaluate() << endl;  // 5.2
}
void testDivideByZero() {
    expression_evaluator expr1("10 / 0");  // 应该显示错误信息
    cout << "Test divide by zero 10 / 0: " << expr1.evaluate() << endl;  // 应该输出错误 -1
}
void testEmptyExpression() {
    expression_evaluator expr("");
    cout << "Test empty expression: " << expr.evaluate() << endl;  // 应该输出错误
}
void testComprehensive() {
    expression_evaluator expr1("3 + 5 * 2 - 1"); //12
    expression_evaluator expr2("(3+5)*(2-1)"); //8
    expression_evaluator expr3("2+3*(6/3)e1"); //62
    expression_evaluator expr4("4e2^0.5"); //20
    expression_evaluator expr5("0.08e(-1 )^(1/3)");  //0.2
    expression_evaluator expr6("0.21.1+2");  
    expression_evaluator expr7("0022+0.11e2-(-3)^2"); //24 
    cout << "Test Comprehensive expression: 3 + 5 * 2 - 1= " << expr1.evaluate() << endl;    
    cout << "Test Comprehensive expression: (3+5)*(2-1)= " << expr2.evaluate() << endl;    
    cout << "Test Comprehensive expression: 2+3*(6/3)e1= " << expr3.evaluate() << endl;  
    cout << "Test Comprehensive expression: 4e2^0.5= " << expr4.evaluate() << endl;  
    cout << "Test Comprehensive expression: 0.08e(-1 )^(1/3) = " << expr5.evaluate() << endl;  
    cout << "Test Comprehensive expression: 0.21.1+2 = " << expr6.evaluate() << endl;  
    cout << "Test Comprehensive expression: 0022+0.11e2-(-3)^2 = " << expr7.evaluate() << endl;  
}



int main(){
    testModify();
    cout<<"----------------------------------------"<<endl;
    testIsLegal();
    cout<<"----------------------------------------"<<endl;
    testIsMatch();
    cout<<"----------------------------------------"<<endl;
    testEvaluate();
    cout<<"----------------------------------------"<<endl;
    testExponentiation();
    cout<<"----------------------------------------"<<endl;
    testNegativeNumbers();
    cout<<"----------------------------------------"<<endl;
    testFloatingPoint();
    cout<<"----------------------------------------"<<endl;    
    testComprehensive();
    cout<<"----------------------------------------"<<endl;    
    testDivideByZero();
    cout<<"----------------------------------------"<<endl;    
    testEmptyExpression();

    return 0;
}