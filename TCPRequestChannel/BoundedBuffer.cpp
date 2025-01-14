// your PA3 BoundedBuffer.cpp code here
#include "BoundedBuffer.h"
#include <thread> 
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <cassert>


using namespace std;


BoundedBuffer::BoundedBuffer (int _cap) : cap(_cap) {
    // modify as needed
}

BoundedBuffer::~BoundedBuffer () {
    // modify as needed
}

void BoundedBuffer::push (char* msg, int size) {            

    // 1. Convert the incoming byte sequence given by msg and size into a vector<char>
    // 2. Wait until there is room in the queue (i.e., queue lengh is less than cap)
    // 3. Then push the vector at the end of the queue
    // 4. Wake up threads that were waiting for push
    unique_lock<mutex> ul (m);
    if (msg == nullptr || size <= 0) {
        throw invalid_argument("Invalid message or size in push");
    }
    
    cv.wait(ul, [&] {return q.size() < cap;});
    vector<char> message;
    for(int i = 0; i < size; i++){
        message.push_back(msg[i]);
    }
    q.push(message);
    ul.unlock();
    cv.notify_all();
}

int BoundedBuffer::pop (char* msg, int size) {
    // 1. Wait until the queue has at least 1 item
    // 2. Pop the front item of the queue. The popped item is a vector<char>
    // 3. Convert the popped vector<char> into a char*, copy that into msg; assert that the vector<char>'s length is <= size
    // 4. Wake up threads that were waiting for pop
    // 5. Return the vector's length to the caller so that they know how many bytes were popped
    unique_lock<mutex> ul(m);

    if (msg == nullptr || size <= 0) {
        throw invalid_argument("Invalid message or size in pop");
    }
    cv.wait(ul, [&] { return q.size() > 0; });

    assert(q.front().size() <= size);
    for(int i = 0; i < q.front().size(); i++){
        msg[i] = q.front().at(i);
    }
    int msgSize = q.front().size();
    q.pop();
    ul.unlock();
    cv.notify_all();
    return msgSize;
}

size_t BoundedBuffer::size () {
    return q.size();
}