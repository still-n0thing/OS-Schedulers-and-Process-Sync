#include <bits/stdc++.h>

using namespace std;

const long long n = 2;

vector<bool> Flag(n, true);
int Turn = 0;

int main(int argc, char const *argv[]){
    auto writeFile = [&](string file_name){
        ofstream myfile(file_name);
        if(myfile.is_open()){
            myfile << "I want ot write this to a file\n";
            myfile << "I dont really like Shakespeare\n";
            myfile.close();
        } else {
            cout << "Unable to open file\n";
        }
    };

    auto readFile = [&](string file_name){
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
    };

    auto p0 = [&](string file_name){
        Flag[0] = true;
        Turn = 1;
        if(Turn == 1 and Flag[1] == true){
            readFile(file_name);
        }
        Flag[0] = false;
    };

    auto p1 = [&](string file_name){
        Flag[1] = true;
        Turn = 0;
        if(Turn == 0 and Flag[0] == true){
            writeFile(file_name);
        }
        Flag[1] = false;
    };

    // Execution has started
    thread th1(p0, "poem.txt");
    thread th2(p1, "poem.txt"); 
    
    th2.join();
    th1.join(); 

    return 0;
}
