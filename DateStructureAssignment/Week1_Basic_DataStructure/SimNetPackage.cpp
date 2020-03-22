#include <iostream>
#include <queue>
#include <vector>

struct Request
{
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response
{
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer
{
public:
    Buffer(int size):
        size_(size),
        finish_time_()
    {}

    Response Process(const Request &request)
    {
        // write your code here
        //Pop all finished pks
        while(request.arrival_time >= finish_time_.front())
        {
            if(finish_time_.size()== 0)
                break;
            if(finish_time_.size()> 0)
            {
                finish_time_.pop();
                std::cout << "Pop!" << std::endl;
            }
        }
        //Check whether the pk can be put into the buffer
        if(finish_time_.size() == size_)
        {
            //Buffer is full.
            std::cout << "Full. Drop!" << std::endl;
            return Response(true,-1);
        }
        else
        {
            //Still got space
            //The processor can process one at a time. Check whether it can be processed immediately.
            if(finish_time_.size() == 0)
            {
                //std::cout << "Queue is empty. Process right away." << std::endl;
                finish_time_.push(request.arrival_time + request.process_time);
                return Response(false,request.arrival_time);
            }
            else
            {
                //Pk cannot be processed immediately.
                //std::cout << "Still processing other pkg..." << std::endl;
                finish_time_.push(finish_time_.front()+request.process_time);
                return Response(false,finish_time_.front());//Will start when there is an empty space at buffer.
            }
        }

    }
private:
    int size_;
    std::queue <int> finish_time_;// a queue that records pks in buffer with finish time.
};

std::vector <Request> ReadRequests()
{
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i)
    {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer)
{
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses)
{
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main()
{
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
