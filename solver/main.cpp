#include <iostream>
#include "ConverterToPostfix.h"
#include "PostfixEvaluation.h"

int main() {
    string expression;
    cout << "Input Expression: " << '\n';
    getline(cin, expression);
    Converter converter(expression);
    auto postfix_exp = converter.get_postfix();
    // Print Postfix expression
    /*cout << "Output Postfix Expression: " << '\n';
    for(const auto& element : postfix_exp){
        cout << element << " ";
    }
    cout << '\n';
    */
    PostfixEvaluation solver(postfix_exp);
    auto result = solver.get_result();
    cout << "Result: " << result << '\n';

    return 0;
}