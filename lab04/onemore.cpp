#include <bits/stdc++.h>

using namespace std;

const int n = 2;

#define MAX 10

vector<int> workable(MAX, 0);

vector<bool> Flag(n, false);
int Turn = 0;

void display(const vector<int> & a){
    cout << " [";
    for(auto i : a){
        cout << i << " ";
    }
    cout << "]\n";
}

int main(int argc, char const *argv[]){

    freopen ("output.txt", "w", stdout);

    iota(workable.begin(), workable.end(), 0);
    display(workable);

    auto increaseVal = [&](int val){
        for(int i = 0; i < MAX; i++){
            workable[i] += val;
        }
        // display(workable);
    };

    auto decreaseVal = [&](int val){
        for(int i = 0; i < MAX; i++){
            workable[i] -= val;
        }
        // display(workable);
    };

    auto p0 = [&](int val){
        Flag[0] = true;
        Turn = 1;
        if(Turn == 1 and Flag[1] == true){
            increaseVal(val);
        }
        Flag[0] = false;
    };

    auto p1 = [&](int val){
        Flag[1] = true;
        Turn = 0;
        if(Turn == 0 and Flag[0] == true){
            decreaseVal(val);
        }
        Flag[1] = false;
    };

    // Execution has started
    thread th1(p0, 10);
    thread th2(p1, 5);     

    // th2.join();
    // th1.join(); 

    display(workable);

    return 0;
}
