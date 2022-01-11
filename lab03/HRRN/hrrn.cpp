#include <bits/stdc++.h>

#define dbg(x) cerr << #x << " = " << x << endl;

using namespace std;

class Process {
public:
    int pid;
    int at; // arrival time
    int bt; // burst time
    int st; // start time
    int ct; // start time
    int tot; // turn around time
    int wt; // wating time
    int rt; // response time

    void set(int pid, int at, int bt){
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        this->st = -1;
        this->ct = -1;
        this->tot = -1;
        this->wt = -1;
        this->rt = -1;
    }
};

template<typename T> void printElement(T t, const int& width){
    const char separator = ' ';
    cout << left << setw(width) << setfill(separator) << t;
}

void printall(const vector<Process> & p){
    int n = p.size();
    const char separator = ' ';
    const int width = 6;
    
    printElement("PID", width);
    printElement("AT", width);
    printElement("BT", width);
    printElement("ST", width);
    printElement("CT", width);
    printElement("TOT", width);
    printElement("WT", width);
    printElement("RT", width);
    cout << "\n";

    for(int i = 0; i < n; i++){
        printElement(p[i].pid, width);
        printElement(p[i].at, width);
        printElement(p[i].bt, width);
        printElement(p[i].st, width);
        printElement(p[i].ct, width);
        printElement(p[i].tot, width);
        printElement(p[i].wt, width);
        printElement(p[i].rt, width);
        cout << "\n";
    }

}

vector<Process> calc(vector<Process> p){
    int n = p.size(), cur = 0, idx = 0;
    int time = 0, ttl_tot = 0, ttl_wt = 0, ttl_rt = 0, ttl_it = 0;
    vector<int> burst_rem(n), is_completed(n, 0);

    for(int i = 0; i < n; i++){
        burst_rem[i] = p[i].bt;
    }

    int current_time = 0, completed = 0, prev = 0;
    while(completed != n){
        int idx = -1;
        float mn = -1.1;
        for(int i = 0; i < n; i++){
            if(p[i].at <= current_time and is_completed[i] == 0){

                if(((float)(current_time - p[i].at + p[i].bt)/p[i].bt) > mn){
                    mn = ((float)(current_time - p[i].at + p[i].bt)/p[i].bt);
                    idx = i;
                }

                if(((float)(current_time - p[i].at + p[i].bt)/p[i].bt) == mn){
                    if(p[i].at < p[idx].at){
                        mn = ((float)(current_time - p[i].at + p[i].bt)/p[i].bt);
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1){

            if(burst_rem[idx] == p[idx].bt){
                p[idx].st = current_time;
                ttl_it += p[idx].st - prev;
            }
            burst_rem[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_rem[idx] == 0) {
                p[idx].ct = current_time;
                p[idx].tot = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tot - p[idx].bt;
                p[idx].rt = p[idx].st - p[idx].at;

                ttl_tot += p[idx].tot;
                ttl_wt += p[idx].wt;
                ttl_rt += p[idx].rt;

                is_completed[idx] = 1;
                completed++;
            }
        }

        else {
            current_time++;
        }
    }
    return p;
}

float avg_tot(const vector<Process> & p){
    int n = p.size();
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += p[i].tot;
    }
    return (float)ans/n;
}

float avg_wt(const vector<Process> & p){
    int n = p.size();
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += p[i].wt;
    }
    return (float)ans/n;
}

void solve(){
    int n; cin >> n;
    vector<Process> p(n);
    for(int i = 0; i < n; i++){
        int pid, at, bt; cin >> pid >> at >> bt;
        p[i].set(pid, at, bt);
    } // O(n)
    
    sort(p.begin(), p.end(), 
    [](const Process & left, const Process & right){
        return left.at < right.at;
    }); // O(n*log(n))
    
    // printall(p); // O(n)
    // cout << "\n";

    vector<Process> ans = calc(p);

    // printall(ans); cout << "\n";

    sort(ans.begin(), ans.end(), 
    [](const Process & left, const Process & right){
        return left.pid < right.pid;
    });

    printall(ans);

    cout << "Avg TOT = " << avg_tot(ans) << "\n";
    cout << "Avg WT  = " << avg_wt(ans) << "\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL); 
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);   

    int T; cin >> T;
    int num = 0;
    while(T--){
        cout << "\t\t\t\t  Case : " << (++num) << "\n";
        solve(); cout << "\n";
    }
    
    return 0;
}