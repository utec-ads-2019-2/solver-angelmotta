#ifndef SOLVER_POSTFIXEVALUATION_H
#define SOLVER_POSTFIXEVALUATION_H

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

class PostfixEvaluation{
private:
    stack<float> op_numbers;
    vector<string> postfix_exp;

    bool isOperand(char C){
        //return C >= '0' && C <= '9';
        if(C >= '0' && C <= '9') return true;
        if(C >= 'a' && C <= 'z') return true;
        if(C >= 'A' && C <= 'Z') return true;
        return false;
    }

    int convertOperandToInt(string C){
        int num_operand;
        if(C >= "0" && C <= "9"){
            num_operand = stoi(C);
            return num_operand;
        }
        if((C >= "a" && C <= "z") || (C >= "A" && C <= "Z")){
            cout << "Ingresa un numero para la variable '" << C << "' : ";
            cin >> num_operand;
            return num_operand;
        }
        return -1;
    }

    bool isOperator(char C){
        return C == '+' || C == '-' || C == '*' || C == '/' || C == '^';
    }

    // Function to perform an operation and return output.
    float executeOperation(char operation, float operand1, float operand2){
        if(operation == '+') return operand1 +operand2;
        else if(operation == '-') return operand1 - operand2;
        else if(operation == '*') return operand1 * operand2;
        else if(operation == '/') return operand1 / operand2;
        else if(operation == '^') return pow(operand1,operand2);
        else cout<<"Unexpected Error \n";
        return -1;
    }

    float solver(){
        for(const auto& element : postfix_exp){
            if(isOperand(element[0])){
                //cout << "Operando: " << element[0] << '\n';
                //int number_element = stoi(element); //convert the string to number and then push
                int number_element = convertOperandToInt(element);
                op_numbers.push(number_element);
            }
            else if(isOperator(element[0])){
                auto operand2 = op_numbers.top();
                op_numbers.pop();
                auto operand1 = op_numbers.top();
                op_numbers.pop();
                auto res = executeOperation(element[0], operand1, operand2);
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

    float get_result(){
        return solver();
    }
};


#endif //SOLVER_POSTFIXEVALUATION_H
