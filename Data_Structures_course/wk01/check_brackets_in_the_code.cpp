#include <iostream>
#include <stack>
#include <string>

/*
Problem Introduction
In this problem you will implement a feature for a text editor to find errors in the usage of brackets in the code.
Input Format.
Input contains one string S which consists of big and small latin letters, digits, punctuation marks and brackets  from the set []{}().
Constraints.
The length of S is at least 1 and at most 105.
Output Format. Ifthecodein S usesbracketscorrectly,output“Success"(withoutthequotes).
Otherwise, output the 1-based index of the first unmatched closing bracket, and if there are no unmatched closing brackets, output the 1-based index of the first unmatched opening bracket.
*/

// Branko Milosevic 2020-09-04
// Coursera Data Structures wk01-01

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
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

    int faulty_position = -1;

    std::stack <Bracket> opening_brackets_stack;

    for (int position = 0; position < text.length(); ++position)
    {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{')
        {
            // Process opening bracket, write your code here
            Bracket *bracket = new Bracket(next, position + 1);
            opening_brackets_stack.push(*bracket);
        }

        if (next == ')' || next == ']' || next == '}')
        {
            // Process closing bracket, write your code here
            if (opening_brackets_stack.size() == 0)
            {
                faulty_position = position + 1;
                break;
            }
            else if (opening_brackets_stack.top().Matchc(next))
            {
                // pop it
                opening_brackets_stack.pop();
            }
            else
            {
                faulty_position = position + 1;
                break;
            }
        }
    }

    // Printing answer, write your code here
    if (opening_brackets_stack.size() == 0 && faulty_position == -1)
    {
        std::cout << "Success" << "\n";
    }
    else
    {
        if (opening_brackets_stack.size() && faulty_position == -1)
        {
            faulty_position = opening_brackets_stack.top().position;
        }
        std::cout << faulty_position << "\n";
    }

    return 0;
}
