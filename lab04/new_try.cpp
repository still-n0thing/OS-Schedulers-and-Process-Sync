#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

const long long n = 2;
vector<bool> Flag(n, true);
int Turn = 0;

string file_name = "poem.txt";

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_p0 = PTHREAD_COND_INITIALIZER;
pthread_cond_t c_p1 = PTHREAD_COND_INITIALIZER;

void *process0(void *param);
void *process1(void *param);

int main(int argc, char const *argv[]){
    pthread_t th0, th1;

    if(pthread_create(&th0, NULL, process0, NULL) != 0){
        cerr << "process 0 thread cannot be created" << endl;
        exit(1);
    }

    if(pthread_create(&th1, NULL, process1, NULL) != 0){
        cerr << "process 1 thread cannot be created" << endl;
        exit(1);
    }

    pthread_join(th1, NULL);
    pthread_join(th0, NULL);
    // Same file is read and write by different process

    cout << "Execution completed" << endl;

    return 0;
}

void *process0(void *param){
    // Peterson Solution
    Flag[0] = true;
    Turn = 1;
    if(Turn == 1 and Flag[1] == true){
        pthread_mutex_lock(&m);
        ofstream myfile(file_name);
        if(myfile.is_open()){
            myfile << "I want ot write this to a file\n";
            myfile << "I dont really like Shakespeare\n";
            myfile.close();
        } else {
            cout << "Unable to open file\n";
        }
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_p1);
    }
    Flag[0] = false;
} 

void *process1(void *param){
    // Peterson Solution
    Flag[1] = true;
    Turn = 0;
    if(Turn == 0 and Flag[0] == true){
        pthread_mutex_lock(&m);
        string line;
        ifstream myfile(file_name);
        if(myfile.is_open()){
            while(getline(myfile, line)){
                cout << line << "\n";
            }
            myfile.close();
        } else {
            cout << "Unable to open file\n";
        }
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&c_p0);

    }
    Flag[1] = false;
} 