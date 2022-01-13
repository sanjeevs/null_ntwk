#include "ts_deque.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

int MAX_ENTRIES = 1000;

void enq_thread(TsDeque<int> &deq) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 3);

    std::cout << "EnqThread:Starting to push " << MAX_ENTRIES << " entries" << std::endl;
    for(int i = 0; i < MAX_ENTRIES; i++) {
        deq.push_back(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(distrib(gen)));
    }
}


void deq_thread(TsDeque<int> &deq) {
    int item;

    for(int i = 0; i < MAX_ENTRIES; i++) {
        deq.wait_for_item();
        item = deq.pop_front();
        if(i != item) {
            std::cout << "OOPS: container mismatch at i=" << i 
                      << ",Got=" << item << std::endl;
        }
    }
    std::cout << "DeqThread: Checked all the entries" << std::endl;
}


int main() {
    TsDeque<int> deq;

    std::thread t2(deq_thread, std::ref(deq));
    std::thread t1(enq_thread, std::ref(deq));
   

    t1.join();
    t2.join();

    return 0;
}