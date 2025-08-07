#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <thread>

using Task = std::function<void()>;

const unsigned int threadCount = std::thread::hardware_concurrency();

class Threadpool {
  public:
    Threadpool() : threads(threadCount) {
        for (unsigned int i = 0; i < threadCount; ++i) {
            threads.emplace_back(threadHandler, this);
        }
    }

    void queue(Task task) {
        std::lock_guard<std::mutex> lock(taskQueue_mux);
        taskQueue.push(task);
    }

    [[nodiscard]] int count() const { return taskQueue.size(); }

  protected:
    std::queue<Task> taskQueue;
    std::mutex taskQueue_mux;
    std::vector<std::thread> threads;

    static void threadHandler(Threadpool *pool) {
        while (true) {
            if (!pool)
                break;

            pool->taskQueue_mux.lock();
            Task task = pool->taskQueue.front();
            pool->taskQueue.pop();
            pool->taskQueue_mux.unlock();

            task();
        }
    }
};
