#ifndef SOLVER_POSTFIXEVALUATION_H
#define SOLVER_POSTFIXEVALUATION_H

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class PostfixEvaluation{
private:
    stack<int> op_numbers;
    vector<string> postfix_exp;

    bool isOperand(char C){
        return C >= '0' && C <= '9';
    }

    bool isOperator(char C){
        return C == '+' || C == '-' || C == '*' || C == '/' || C == '^';
    }

    // Function to perform an operation and return output.
    int executeOperation(char operation, int operand1, int operand2){
        if(operation == '+') return operand1 +operand2;
        else if(operation == '-') return operand1 - operand2;
        else if(operation == '*') return operand1 * operand2;
        else if(operation == '/') return operand1 / operand2;
        else cout<<"Unexpected Error \n";
        return -1;
    }

    int solver(){
        for(const auto& element : postfix_exp){
            if(isOperand(element[0])){
                int number_element = stoi(element); //convert the string to number and then push
                op_numbers.push(number_element);
            }
            else if(isOperator(element[0])){
                int operand2 = op_numbers.top();
                op_numbers.pop();
                int operand1 = op_numbers.top();
                op_numbers.pop();
                int res = executeOperation(element[0], operand1, operand2);
                // Push back the result to the stack of number
                op_numbers.push(res);
            }
        }
        return op_numbers.top();
    }

public:
    // Constructors
    PostfixEvaluation()= default;
    PostfixEvaluation(vector<string> vec_postfix) : postfix_exp(vec_postfix){}

    int get_result(){
        return solver();
    }
};


#endif //SOLVER_POSTFIXEVALUATION_H
