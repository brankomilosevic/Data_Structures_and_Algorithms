#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

/*
Problem Introduction Stack is an abstract data type supporting the operations Push() and Pop(). It is not difficult to implement it in a way that both these operations work in constant time. In this problem, you goal will be to implement a stack that also supports finding the maximum value and to ensure that all operations still work in constant time.

Task. Implement a stack supporting the operations Push(), Pop(), and Max(). Input Format. The first line of the input contains the number q of queries. Each of the following q lines specifies a query of one of the following formats: push v, pop, or max. Constraints. 1 ≤ q ≤ 400000, 0 ≤ v ≤ 105. Output Format. For each max query, output (on a separate line) the maximum value of the stack.
*/

// Branko Milosevic 2020-09-04
// Coursera Data Structures wk01-04

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;
using std::pair;

class StackWithMax {
    private:
        vector<pair<long long, long long> > elements;
        long long top;

    public:
        StackWithMax()
        {
            top = -1;
        }
        bool empty()
        {
            return top == -1;
        }
        void Push(long long element)
        {
            if(empty())
            {
                elements.push_back(std::make_pair(element, element));
                top = 0;
            }
            else
            {
                long long mx = std::max(element, elements[top].second);
                elements.push_back(std::make_pair(element, mx));
                top++;
            }
        }
        void Pop()
        {
            elements.pop_back();
            top--;
        }
        long long Max()
        {
            return elements[top].second;
        }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax the_stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            the_stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            the_stack.Pop();
        }
        else if (query == "max") {
            cout << the_stack.Max() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}
