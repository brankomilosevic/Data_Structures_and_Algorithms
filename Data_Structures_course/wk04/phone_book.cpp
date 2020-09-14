#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::string;
using std::vector;
using std::cin;
using std::map;

/*
Task.
In this task your goal is to implement a simple phone book manager.
It should be able to process the following types of user’s queries:
add number
del number
find number

Input Format.
There is a single integer N in the first line — the number of queries.
It’s followed by N lines, each of them contains one query in the format described above.

Output Format.
Print the result of each find query
- the name corresponding to the phone number
- “not found" if there is no person in the phone book with such phone number.

Output one result per line in the same order as the find queries are given in the input.
*/

// Branko Milosevic 2020-09-10
// Coursera Data Structures wk04-01

struct Query
{
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> queries[i].type;

        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query> &queries)
{
    vector<string> result;
    // STL map (hash table)
    map<int, string> Phone_Book;
    map<int, string>::iterator iter;
    // traverse every query
    for (int i = 0; i < queries.size(); i++)
    {
        iter = Phone_Book.find(queries[i].number);

        if (queries[i].type == "add")
        {
            Phone_Book[queries[i].number] = queries[i].name;
        }
        else if (queries[i].type == "del")
        {
            if(iter != Phone_Book.end())
                Phone_Book.erase(iter);
        }
        else if(queries[i].type == "find")
        {
            string response = "not found";
            if(iter != Phone_Book.end()) response = iter->second;

            result.push_back(response);
        }
    }
    return result;
}

/*
vector<string> process_queries(const vector<Query>& queries)
{
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
	vector<Query> contactsDA(10000000);
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add")
        {
			contactsDA[queries[i].number] = queries[i];
        }
        else if (queries[i].type == "del")
        {
            contactsDA[queries[i].number].name = "";
			contactsDA[queries[i].number].number = 0;
        }
        else
        {
            string response = "not found";
        	if(contactsDA[queries[i].number].name != "")
				response = contactsDA[queries[i].number].name;

			result.push_back(response);
        }
    return result;
}
*/
int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}

// Original
/*
#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
*/

