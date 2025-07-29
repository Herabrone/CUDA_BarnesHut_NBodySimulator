#ifndef THREADPOOL_H
#define THREADPOOL_H

// ThreadPool.h - implements a fixed-size thread pool with task queue
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();

    // Enqueue a new task
    void enqueue(std::function<void()> task);

    // Stop accepting new tasks and join all threads
    void joinAll();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

#endif // THREADPOOL_H
