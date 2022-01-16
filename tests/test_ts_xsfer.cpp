#include "ts_deque.h"
#include <iostream>
#include <fstream>
#include <vector>

#include <thread>
#include <chrono>
#include <random>

int MAX_ENTRIES = 1000;

void enq_thread(TsDeque<uint8_t> &deq, std::ifstream& input) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 3);

    std::vector<char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    std::cout << "EnqThread:Starting to push " << MAX_ENTRIES << " entries" << std::endl;
    for(int i = 0; i < bytes.size(); i++) {
        ts_deq.push_back(bytes[i]);
        std::this_thread::sleep_for(std::chrono::milliseconds(distrib(gen)));
    }
}


void deq_thread(TsDeque<unit8_t> &deq, std::ofstream& output) {
    uint8_t item;

    for(int i = 0; i < MAX_ENTRIES; i++) {
        ts_deq.wait_for_item();
        item = ts_deq.pop_front();
        output.write(&item, 1);
    }
    std::cout << "DeqThread: Checked all the entries" << std::endl;
}


int main(int argc, char* argv[]) {
    TsDeque<uint8_t> ts_deq;

    std::ifstream input("in_data.txt", std::ios::binary);
    std::ofstream output("out_dat.txt", std::ios::binary | std::ios::out);

    std::thread t2(deq_thread, std::ref(ts_deq), in_stream);
    std::thread t1(enq_thread, std::ref(ts_deq), out_stream);
   

    t1.join();
    t2.join();

    in_stream.close();
    out_stream.close();

    return 0;
}
