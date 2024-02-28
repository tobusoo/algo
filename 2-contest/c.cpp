#include <iostream>
#include <sstream>
#include <stack>

int main()
{
    std::stack<int> values;
    // std::stack<char> operators;

    int temp, operand1, operand2;
    std::string s, s2;
    std::getline(std::cin, s2);
    std::istringstream ss(s2);

    while (ss >> s) {
        if (isdigit(s[0])) {
            temp = std::atoi(s.c_str());
            values.push(temp);
        } else {
            switch (s[0]) {
            case '+':
                operand2 = values.top();
                values.pop();
                operand1 = values.top();
                values.pop();
                values.push(operand1 + operand2);
                break;
            case '-':
                operand2 = values.top();
                values.pop();
                operand1 = values.top();
                values.pop();
                values.push(operand1 - operand2);
                break;
            case '*':
                operand2 = values.top();
                values.pop();
                operand1 = values.top();
                values.pop();
                values.push(operand1 * operand2);
                break;
            default:
                break;
            }
        }
    }
    std::cout << values.top() << '\n';

    return 0;
}