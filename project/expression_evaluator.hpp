    #include<iostream>
    #include<vector>
    #include<cmath>
    #include<string>
    #include<algorithm>
    using namespace std;
    class expression_evaluator{
    private:
        string expressions="";  //record the expression
        // to check a char is an operator or not, regard e as a special operator
        bool isoperator(const char &c){
            if(c=='+' || c=='-' || c=='*' || c=='/' || c=='e' || c=='^'){
                return true;
            }
            else{
                return false;
            }
        }

        //判断运算符优先级大小
        int prior(const char &c){
            if(c=='+' || c=='-'){
                return 1;
            }
            else if(c=='/' || c=='*'){
                return 2;
            }
            else if(c=='^'){
                return 3;
            }
            else if(c=='e'){
                return 4;
            }
            else if(c=='.'){
                return 5;
            }
            else{
                return 0;
            }
        }
        //实现一步运算
        double calculate(const double &x, const double &y, const char &c){
            if(c=='+'){
                return x+y;
            }
            else if(c=='-'){
                return x-y;
            }
            else if(c=='*'){
                return x*y;
            }
            else  if(c=='/' && y!=0){
                return x/y;
            }
            else if(c=='/' && y==0){
                cerr<<"can not be devided by zero"<<endl;
                return -1;
            }
            else if(c=='e'){
                return x*pow(10,y);
            }
            else if(c=='^'){
                return pow(x,y);
            }
            else{
                return 0;
            }
        }
        //deal with negative numbers
        void modify(){
            expressions.erase(remove(expressions.begin(), expressions.end(), ' '), expressions.end());
            for(int i=1; i<expressions.length(); ++i){
                if(expressions[i-1]=='(' && expressions[i]=='-'){
                    expressions.insert(i,1,'0');
                    ++i;
                }
            }
        }

    public:
        expression_evaluator(){}
        expression_evaluator(const string &expressions):expressions(expressions){
            modify();
        }

        //判断表达式是否合法,运算符开头或者结尾以及两个非括号的运算符连续出现
        bool isLegal(){
            int l=expressions.size();
           for(int i=0; i<l-1; ++i){
                bool a=!isdigit(expressions[i]) && expressions[i]!='(' && expressions[i]!=')';
                bool b=!isdigit(expressions[i+1])&& expressions[i+1]!='(' && expressions[i+1]!=')';
                bool c= expressions[i]=='.';
                bool d=expressions[i+1]=='.';
                if((i==0 && a ) || (i==l-2 && b ) ||
                    (a && b) || (a&& expressions[i+1]==')')||(expressions[i]=='('&&expressions[i+1]==')')||
                    (expressions[i]=='('&& b) ||(c && expressions[i+1]==')') ||(c && expressions[i+1]=='(') ||
                    (expressions[i]=='(' && d) ||(expressions[i]==')' && d)||
                    (expressions[i]=='(' && expressions[i+1]==')')){
                        return false;
                    }
            }
            if(isoperator(expressions[l])){
                return false;
            }
            return true;
        }

        //检查括号是否匹配
        bool isMatch(){
            vector<char> brackets;
            for(char c:expressions){
                if(c=='('){
                    brackets.push_back(c);
                }
                else if(c==')'){
                    if(brackets.size()==0){
                        return false;
                    }
                    else{
                        brackets.pop_back();
                    }
                }
            }
            return brackets.size()==0;
        }

        double evaluate(){
            if(!isLegal()||!isMatch()){
                cerr<<"brackets are matched or illegal expression"<<endl;
                return -1;
            }
            int l=expressions.length();
            if(l==0){
                cerr<<"no expression!"<<endl;
                return -1;
            }
            string new_expression=expressions.append(" ");
            string currentnum;
            //用vector实现栈
            vector<double> nums;  //用于存放数字
            vector<char> ops;  //存放操作符
            int counter=0; //record the number of '.'
            for(int i=0; i<l;++i){
                char c=new_expression[i];
                char d=new_expression[i+1];
                if(isdigit(c)){
                    currentnum+=c;
                    if(! isdigit(d) && d!='.'){
                        nums.push_back(stod(currentnum));
                        currentnum.clear();
                        counter=0;
                    }
                }
                else if(c=='.' && counter==0){
                    currentnum+=c;
                    ++counter;
                }
                else if(c=='.' && counter!=0){
                    cerr<<"invalid expression"<<endl;
                    return -1;
                }

                if(isoperator(c)){
                    if(ops.size()==0){
                        ops.push_back(c);
                    }
                    else{
                        while(prior(c)<=prior(ops.back()) &&ops.size()!=0){
                            double y=nums.back();
                            nums.pop_back();
                            double x=nums.back();
                            nums.pop_back();
                            char op=ops.back();
                            ops.pop_back();
                            double x1=calculate(x, y, op);
                            nums.push_back(x1);
                        }
                    ops.push_back(c);
                    }
                }
                else if(c=='('){
                    ops.push_back(c);
                }
                else if(c==')'){
                    while(ops.back()!='('){
                        char op=ops.back();
                        ops.pop_back();
                        double y=nums.back();
                        nums.pop_back();
                        double x=nums.back();
                        nums.pop_back();
                        double x1=calculate(x, y, op);
                        nums.push_back(x1);
                    }
                    ops.pop_back();
                }
            }
            while(ops.size()!=0){
                char op=ops.back();
                ops.pop_back();
                double y=nums.back();
                nums.pop_back();
                double x=nums.back();
                nums.pop_back();
                double x1=calculate(x, y, op);
                nums.push_back(x1);
            }
            return nums.back();
        }
};