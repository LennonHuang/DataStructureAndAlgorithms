#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {//Matching the input character c and the bracket
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;//Only store the opening brackets with A STACK and then check the close ones
    int ans = 0;//use ans to record the response.
    int num_cls = 0;//number of closing brackets
    int num_op = 0;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            //When there is a opening bracket coming, store it into the stack.
            opening_brackets_stack.push(Bracket(next,position));
            num_op += 1;
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.size() == 0){
                ans = position + 1;
                break;
            }
            if(!opening_brackets_stack.top().Matchc(next)){
                //if it is NOT correct
                ans = position + 1;
                break;
            }
            else{
                num_cls += 1;
                opening_brackets_stack.pop();
            }
        }
    }

    // Printing answer, write your code here
    if(ans != 0){
    std::cout << ans << std::endl;
    }
    else{
        if(num_cls == num_op){
            std::cout << "Success" << std::endl;
        }
        else{
            std::cout << num_cls + num_op << std::endl;
        }
    }
    return 0;
}
