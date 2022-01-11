#include <bits/stdc++.h>

using namespace std;

// Class
class Chopstics {
public:
    mutex mu;
    Chopstics(){;}
};

int main(int argc, char const *argv[]){
    cout << "Type number of Philosophers here :";
    int num; cin >> num;

    // lamda function 
    auto eat = [](Chopstics &lf_chopstic, Chopstics &rt_chopstic, int philospher_num){
        unique_lock<mutex> llock(lf_chopstic.mu);
        unique_lock<mutex> rlock(rt_chopstic.mu);
        cout << "Philosopher " << philospher_num << " is eating now" << endl;
        chrono::milliseconds timeout(2000);
        this_thread::sleep_for(timeout);
        cout << "Philosopher " << philospher_num << " has finished eating" << endl;
    };

    // Objects
    Chopstics chp[num];
    thread philosopher[num];

    // Start
    cout << "Philosopher " << (1) << " is reading.." << endl;
    philosopher[0] = thread(eat, std::ref(chp[0]), std::ref(chp[num-1]), (1));
    for(int i = 1; i < num; ++i) {
        cout << "Philosopher " << (i+1) << " is reading.." << endl;
        philosopher[i] = thread(eat, std::ref(chp[i]), std::ref(chp[i-1]), (i+1));
    }

    // Joining the thread
    for(auto & x: philosopher) {
        x.join();
    }

    return 0;
}