#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
// #include <stdint.h> use <cstdint>
#include <cstdint>
#include <queue>
#include <vector>
#include <memory>
// https://codereview.stackexchange.com/questions/161756/just-another-thread-pool-in-c
// namespace natives or you can use std::int16_t etc...
{
    typedef int16_t             int16;
    typedef int32_t             int32;
    typedef int64_t             int64;

    typedef std::atomic_bool    flag;
}

class ThreadPool
{
public:
    struct BaseTask
    {
        virtual void runTask() = 0;
    };

    template <class T> struct Task : public BaseTask
    {
        Task(T task)
            : m_Task(task)
        {}

        virtual void runTask()
        {
            m_Task();
        }

        T m_Task;
    };

	// not needed just use std::bind to replace this
    // template <class T, class P1> struct ParameteredTask : public BaseTask
    // {
    //     ParameteredTask(T task, const P1& p1)
    //         : m_Task(task), m_P1(p1)
    //     {}

    //     virtual void runTask()
    //     {
    //         m_Task(m_P1);
    //     }

    //     T  m_Task;
    //     P1 m_P1;
    // };

    typedef std::queue<BaseTask*>                       TaskQueue;
    typedef std::vector <std::shared_ptr<std::thread> > WorkerGroup;
    typedef std::mutex                                  QueueLock;
    typedef std::unique_lock<std::mutex>                QueueGuard;
    typedef std::condition_variable                     WorkerSignal;

    static void thMain(TaskQueue* queue, QueueLock* qlock, WorkerSignal* signal, natives::flag* online)
    {
        while (*online)
        {
            BaseTask* task = nullptr;

            std::shared_ptr<ThreadPool::QueueGuard> qguard(std::make_shared<ThreadPool::QueueGuard>(*qlock));

            if (!queue->empty())
            {
                task = queue->front();
                queue->pop();

                qguard.reset();
            }
            else if (*online)
            {
                signal->wait(*qguard);
            }

            if (nullptr != task)
            {
                task->runTask();
                delete task;
            }
        }
    }

    ThreadPool(natives::int32 size)
        : m_Online(true)
    {
        for (natives::int32 counter = 0; size > counter; ++counter)
        {
            m_Workers.push_back(std::make_shared<std::thread>(thMain, &m_Queue, &m_QLock, &m_Signal, &m_Online));
        }
    }

    void addThread()
    {
        m_Workers.push_back(std::make_shared<std::thread>(thMain, &m_Queue, &m_QLock, &m_Signal, &m_Online));
    }

    ~ThreadPool()
    {
        m_Online = false;

        m_Signal.notify_all();

        std::for_each(m_Workers.begin(), m_Workers.end(), [](std::shared_ptr<std::thread> thread)->void {thread->join(); });
    }

    void enqueue(BaseTask* task)
    {
        QueueGuard guard(m_QLock);
        m_Queue.push(task);

        m_Signal.notify_all();
    }

    template <class T> void enqueue(T task)
    {
        QueueGuard guard(m_QLock);
        m_Queue.push(new Task<T>(task));

        m_Signal.notify_all();
    }

    template <class T, class P1> void enqueue(T task, const P1& p1)
    {
        QueueGuard guard(m_QLock);
        m_Queue.push(new ParameteredTask<T, P1>(task, p1));

        m_Signal.notify_all();
    }

    natives::int32 getQueueSize()
    {
        QueueGuard guard(m_QLock);
        natives::int32 size = m_Queue.size();

        return size;
    }

    WorkerGroup   m_Workers;
    TaskQueue     m_Queue;
    QueueLock     m_QLock;
    WorkerSignal  m_Signal;
    natives::flag m_Online;
};
Here is a little usage example:

std::mutex m;

void report(natives::int32 i)
{
    {
        std::unique_lock<std::mutex> guard(m);
        std::cout << "hi " << i << "\n";
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
    ThreadPool pool(4);

    pool.enqueue(report, 1);
    pool.enqueue(report, 2);
    pool.enqueue(report, 3);
    pool.enqueue(report, 4);
    pool.enqueue(report, 5);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    pool.addThread();

    getchar();

    return 0;
}