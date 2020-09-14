#include <iostream>
#include <queue>
#include <vector>

/*
Problem Introduction
In this problem you will implement a program to simulate the processing of network packets.
Input Format.
The first line of the input contains the size S of the buffer and the number n of incoming network packets.
Each of the next n lines contains two numbers.
i-th line contains the time of arrival Ai and the processing time Pi (both in milliseconds) of the i-th packet.
It is guaranteed that the sequence of arrival times is non-decreasing.
However, it can contain the exact same times of arrival in milliseconds.
In this case the packet which is earlier in the input is considered to have arrived earlier.

Constraints.
All the numbers in the input are integers. 1 ≤ S ≤ 105; 0 ≤ n ≤ 105; 0 ≤ Ai ≤ 106; 0 ≤ Pi ≤ 103; Ai ≤ Ai+1 for 1 ≤ i ≤ n−1.
Output Format.
For each packet output either the moment of time (in milliseconds) when the processor began processing it
or −1 if the packet was dropped (output the answers for the packets in the same order as the packets are given in the input).
*/

// Branko Milosevic 2020-09-04
// Coursera Data Structures wk01-03

int main()
{
	//std::ios::sync_with_stdio(0);

	int i, j, k, n, t;
    int S;

    std::cin >> S >> n;

    std::queue<std::pair<int, std::pair<int, int> > > q;
    std::vector<std::pair<int, std::pair<int, int> > > v(n);

    for(i = 0; i < n; i++)
    {
        std::cin >> j >> k;
        v[i] = std::make_pair(i, std::make_pair(j,k));
    }

    std::vector<int> res(n);

    j = 0;

    while(j < n && j < S)
    {
        q.push(v[j]);
        j++;
    }

    t = 0;

    while(!q.empty())
    {
        int st = std::max(t, q.front().second.first);
        t = st + q.front().second.second;
        res[q.front().first] = st;

        q.pop();

        while(q.size() < S && j < n)
        {
            if(v[j].second.first<t)
                res[j++] = -1;
            else
                q.push(v[j++]);
        }
    }

    for (int i = 0; i < n; i++)
        std::cout << res[i] << '\n';

}



/* I will loook at the Coursera solution later on (bellow)*/

/*

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request) {
        // write your code here
    }
private:
    int size_;
    std::queue <int> finish_time_;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}

*/
