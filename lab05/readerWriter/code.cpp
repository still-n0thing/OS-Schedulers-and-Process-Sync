#include <bits/stdc++.h>

using namespace std;

// Globle Varibles
int read_count = 0, counter = 0;
const int N = 5;
mutex m;
condition_variable read_cond, write_cond;

// Function Defination
void read();
void write();
chrono::milliseconds rand_val();

int main(int argc, char const *argv[]){
    const int NUM_READ = N, NUM_WRITE = N;
    
    cout << "Hardware Concurrency : " << thread::hardware_concurrency() << endl;
    vector<thread> threads;

    for(int i = 0; i < NUM_READ; i++){
        threads.push_back(thread{read});
    }

    for(int i = 0; i < NUM_WRITE; i++){
        threads.push_back(thread{write});
    }

    for(int i = 0; i < NUM_READ + NUM_WRITE; i++){
        threads[i].join();
    }

    return 0;
}

chrono::milliseconds rand_val(){
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist(0, 20);
    return chrono::milliseconds(dist(rng));
}

void read(){
    unique_lock<mutex> lk(m, defer_lock);
    for(int i = 0; i < N; i++){
        this_thread::sleep_for(rand_val());
        lk.lock();
        if(read_count == -1){
            read_cond.wait(lk, [](){
                return (read_count != -1);
            });
        }
        read_count++;
        lk.unlock();
        cout << "Reader Value : " << counter << endl << "Number of reader : " << read_count << endl;
        lk.lock();
        read_count--;
        if(read_count == 0){
            write_cond.notify_all();
        }
        lk.unlock();
    }
}

void write(){
    unique_lock<mutex> lk(m, defer_lock);
    for(int i = 0; i < N; i++){
        this_thread::sleep_for(rand_val());
        lk.lock();
        if(read_count > 0){
            write_cond.wait(lk, [](){
                return (read_count == 0);
            });
        }
        read_count = -1;
        lk.unlock();
        counter++;
        cout << "Reader Value : " << counter << endl << "Number of reader : " << read_count << endl;
        lk.lock();
        read_count = 0;
        read_cond.notify_all();
        write_cond.notify_all();
        lk.unlock();
    }
}