#ifndef SOLVER_CONVERTERTOPOSTFIX_H
#define SOLVER_CONVERTERTOPOSTFIX_H

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Converter{
private:
    string expression;
    vector<string> postfix_exp;
    string operand="";

    bool isOperand(char C){
        if(C >= '0' && C <= '9') return true;
        if(C >= 'a' && C <= 'z') return true;
        if(C >= 'A' && C <= 'Z') return true;
        return false;
    }

    bool isOperator(char C){
        return C == '+' || C == '-' || C == '*' || C == '/' || C == '^';
    }

    int GetOperatorWeight(char op){
        int weight = -1;
        switch(op){
            case '+':
                weight = 1;
                break;
            case '-':
                weight = 1;
                break;
            case '*':
                weight = 2;
                break;
            case '/':
                weight = 2;
                break;
            case '^':
                weight = 3;
                break;
        }
        return weight;
    }

    static bool IsRightAssociative(char op){
        return op == '^';
    }

    bool hasHigherPrecedence(char op1, char op2){
        //cout << "op1: " << op1 << " op2: " << op2 << '\n';
        int op1Weight = GetOperatorWeight(op1);
        int op2Weight = GetOperatorWeight(op2);
        //cout << "op1Weight: " << op1Weight << " op2Weight: " << op2Weight << '\n';
        // If operators have equal precedence:
        // return true if they are left associative.
        // return false, if it's right associative.
        // if operator is left-associative, left one should be given priority.
        if(op1Weight == op2Weight){
            if(IsRightAssociative(op1)) return false;
            else return true;
        }
        return op1Weight > op2Weight;
    }

    bool isOpeningParentheses(char op){
        return op == '(';
    }

    bool isClosingParentheses(char op){
        return op == ')';
    }

    void InfixToPostfix(){
        stack<char> stack_operators;
        operand = "";
        for(int i=0; i< expression.length(); ++i){
            if(isOperand(expression[i])){
                operand += expression[i];
            }
            else if(isOperator(expression[i])){
                if(operand.length()){   // save previous operand if exist
                    //cout << "push to postfix_vector: " << operand << '\n';
                    postfix_exp.push_back(operand);
                    operand = "";
                }
                while(!stack_operators.empty() && !isOpeningParentheses(stack_operators.top()) && hasHigherPrecedence(stack_operators.top(), expression[i])){
                    //cout << "xx..push to postfix vector: " << stack_operators.top() << '\n';
                    string opt_exp(1,stack_operators.top());
                    postfix_exp.push_back(opt_exp);
                    stack_operators.pop();
                }
                stack_operators.push(expression[i]);
            }
            else if(isOpeningParentheses(expression[i])){
                stack_operators.push(expression[i]);
            }
            else if(isClosingParentheses(expression[i])){
                // store prev operand in vector
                if(operand.length()){
                    //cout << "Closing...push to postfix_vector: " << operand << '\n';
                    postfix_exp.push_back(operand);
                    operand = "";
                }
                while(!stack_operators.empty() && !isOpeningParentheses(stack_operators.top())){
                    string opt_exp(1,stack_operators.top());
                    postfix_exp.push_back(opt_exp);
                    stack_operators.pop();
                }
                stack_operators.pop();  // pop the opening parenthesis
            }
        }
        if(operand.length()){   // end of expression, so save the last operand...for instance: A+B*C   <-- save C
            //cout << "outside the for...push to postfix_vector: " << operand << '\n';
            postfix_exp.push_back(operand);
        }
        // Pop Operators that could be left on the stack
        while(!stack_operators.empty()){
            //cout << "lefts...push to postfix vector: " << stack_operators.top() << '\n';
            string opt_exp(1,stack_operators.top());
            postfix_exp.push_back(opt_exp);
            stack_operators.pop();
        }
    }

public:
    Converter() : expression(""){}
    Converter(string _expression) : expression(_expression){}

    vector<string> get_postfix(){
        // Invocar metodos privados
        InfixToPostfix();
        return postfix_exp;
    };
};
#endif //SOLVER_CONVERTERTOPOSTFIX_H
