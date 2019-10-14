#include <iostream>
#include "ConverterToPostfix.h"

int main() {
    string expression;
    cout << "Input Expression: " << '\n';
    getline(cin, expression);
    Converter converter(expression);
    auto postfix_exp = converter.get_result();
    cout << "Output Postfix Expression: " << '\n';
    for(const auto& element : postfix_exp){
        cout << element << ",";
    }
    return 0;
}