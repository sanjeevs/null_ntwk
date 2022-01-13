#ifndef INCLUDED_ts_deque_h
#define INCLUDED_ts_deque_h

#include <deque>
#include <mutex>
#include <condition_variable>

template <class T> class TsDeque {

public:
    TsDeque() {}

    void push_back(T item) {
        deq_mutex.lock();
        deq.push_back(item);
        deq_mutex.unlock();
        cv.notify_one();
    }

    T pop_front() {
        deq_mutex.lock();
        T item = deq[0];
        deq.pop_front();
        deq_mutex.unlock();
        return item;
    }

    int size() {
        deq_mutex.lock();
        int len = deq.size();
        deq_mutex.unlock();
        return len;
    }

    bool empty() {
        return size() == 0;
    }

    void wait_for_item() {
        while(empty()) {
            std::unique_lock<std::mutex> lk1(deq_mutex);
            cv.wait(lk1);
        }
    }

private:
    std::mutex deq_mutex;
    std::condition_variable cv;

    std::deque<T> deq;

};


#endif
