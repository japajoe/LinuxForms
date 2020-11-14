#ifndef CONCURRENTQUEUE_HPP
#define CONCURRENTQUEUE_HPP

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ConcurrentQueue
{
public:
    mutable std::mutex mut;

    ConcurrentQueue() 
    {

    }
    
    ConcurrentQueue(const ConcurrentQueue& other)
    {
        std::lock_guard<std::mutex> lock(other.mut);
        dataQueue = other.dataQueue;
    }

    ConcurrentQueue& operator = (const ConcurrentQueue& other) = delete;

    void Enqueue(T value)
    {
        std::lock_guard<std::mutex> lock(mut);
        dataQueue.push(value);
        dataCondition.notify_one();
    }

    bool TryDequeue(T& value)
    {
        std::lock_guard<std::mutex> lock(mut);
        if(dataQueue.empty())
        {
            return false;
        }
        value = dataQueue.front();
        dataQueue.pop();

        //Same as above
        //value = std::move(dataQueue.front());

        return true;
    }

    std::shared_ptr<const T> TryDequeue()
    {
        std::lock_guard<std::mutex> lock(mut);

        if(dataQueue.empty())
        {
            return nullptr;
        }
        std::shared_ptr<const T> result(std::make_shared<const T>(dataQueue.front()));
        dataQueue.pop();
        return result;
    }

    bool IsEmpty() const 
    { 
        std::lock_guard<std::mutex> lock(mut);
        return dataQueue.empty();
    }

private:
    std::queue<T> dataQueue;
    std::condition_variable dataCondition;
};

#endif