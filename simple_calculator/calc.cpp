#include <iostream>
#include <stack>
#include <deque>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>


bool 
arePairs(char open, char close) {
    return (open == '(' && close == ')');
}

bool 
brackets(const std::deque<char>& inputDeque) {
    std::stack<char> stack;
    
    for (char ch : inputDeque) {
        if (ch == '(') {
            stack.push(ch);
        }
        else if (ch == ')') {
            if (stack.empty() || !arePairs(stack.top(), ch)) {
                return false;
            }
            stack.pop();
        }
    }

    return stack.empty();
}

int 
get_priority(char op) {
    switch(op) {
        case '^':
            return 3; 
        case '/':
        case '*':
            return 2; 
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

std::deque<std::string> 
infix_to_postfix(const std::deque<char>& input_deq) {
    std::deque<std::string> output;
    std::stack<char> stack;
    
    std::string num = "";
    bool last_was_operator = true;

    for (size_t i = 0; i < input_deq.size(); ++i) {
        char ch = input_deq[i];
        
        if (isdigit(ch) || ch == '.') {
            num += ch; 
            last_was_operator = false;
        } else {
            if (!num.empty()) {
                output.push_back(num);
                num = "";
            }

            if (ch == '(') {
                stack.push(ch);
                last_was_operator = true;
            } 
            else if (ch == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    output.push_back(std::string(1, stack.top()));
                    stack.pop();
                }
                stack.pop();
                last_was_operator = false;
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
                if (ch == '-' && last_was_operator) {
                    if (i + 1 < input_deq.size() && (isdigit(input_deq[i+1]) || input_deq[i+1] == '.')) {
                        num += ch;
                        continue;
                    }
                }
                
                while (!stack.empty() && get_priority(ch) <= get_priority(stack.top())) {
                    output.push_back(std::string(1, stack.top()));
                    stack.pop();
                }
                stack.push(ch);
                last_was_operator = true;
            }
        }
    }

    if (!num.empty()) {
        output.push_back(num);
    }

    while (!stack.empty()) {
        output.push_back(std::string(1, stack.top()));
        stack.pop();
    }

    return output;
}

double 
evaluate_postfix(const std::deque<std::string>& postfix) {
    std::stack<double> stack;

    for (const std::string& token : postfix) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1) || token[0] == '.') {
            stack.push(std::stod(token));
        } else {
            double num2 = stack.top(); 
            stack.pop();
            double num1 = stack.top(); 
            stack.pop();
            double result = 0;
            switch(token[0]) {
                case '+': 
                    result = num1 + num2; 
                    break;
                case '-': 
                    result = num1 - num2; 
                    break;
                case '*': 
                    result = num1 * num2;
                    break;
                case '/': 
                    if (num2 == 0) {
                        std::cerr << "error: division by zero" << std::endl;
                        exit (1);
                    }
                    result = num1 / num2; 
                    break;
                case '^': 
                    result = pow(num1, num2); 
                    break;
            }
            stack.push(result);
        }
    }

    return stack.top();
}

int main(void) {
    std::deque<char> input_deq;
    std::string input;
    
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    // Заменяем все вхождения ** на ^
    size_t pos = 0;
    while ((pos = input.find("**", pos)) != std::string::npos) {
        input.replace(pos, 2, "^");
        pos += 1; 
    }

    for (char ch : input) {
        input_deq.push_back(ch);
    }


    if (!brackets(input_deq)) {
        std::cout << "error: brackets are not balanced" << std::endl;
        return 0;
    }

    
    auto postfix = infix_to_postfix(input_deq);

    double result = evaluate_postfix(postfix);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
