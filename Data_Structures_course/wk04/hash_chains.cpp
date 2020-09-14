#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

/*
Task.
In this task your goal is to implement a hash table with lists chaining.
You are already given the number of buckets m and the hash function.
It is a polynomial hash function
add string
del string
find string
check i

Input Format.
There is a single integer m in the first line — the number of buckets you should have.
The next line contains the number of queries N.
It’s followed by N lines, each of them contains one query in the format described above.

Output Format.
Print the result of each of the find and check queries, one result per line, in the same order as these queries are given in the input.
*/

// Branko Milosevic 2020-09-14
// Coursera Data Structures wk04-03

using std::string;
using std::vector;
using std::cin;
using std::list;

struct my_query {
    string type, s;
    size_t ind;
    vector<string> substrings;
};

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    vector<list<string> > buckets;
    // store all strings in one vector
    vector<string> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        buckets.resize(bucket_count);
        vector<list<string> >::iterator itRow;
        list<string>::iterator itCol;

        if (query.type == "check")
        {
            list<string>& bucket = buckets[query.ind];
            for(itCol = bucket.begin(); itCol != bucket.end(); ++itCol) std::cout << *itCol << " ";

            std::cout << "\n";
        }
        else
        {
            int hashValue = hash_func(query.s);
            list<string>& bucket = buckets[hashValue];
            for(itCol = bucket.begin(); itCol != bucket.end(); ++itCol)
            {
                if(*itCol == query.s)
                    break;
            }
            if(query.type == "find")
            {
                writeSearchResult(itCol != bucket.end());
            }
            else if(query.type == "add")
            {
                if(itCol == bucket.end())
                    bucket.push_front(query.s);
            }
            else if(query.type == "del")
            {
                if(itCol != bucket.end())
                    bucket.erase(itCol);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}


