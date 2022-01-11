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

vector<Process> calc(vector<Process> p, int tq){
    int n = p.size(), cur = 0, idx = 0;
    int time = 0, ttl_tot = 0, ttl_wt = 0, ttl_rt = 0, ttl_it = 0;
    vector<int> burst_rem(n), is_completed(n, 0);
    vector<bool> mark(n, false);

    for(int i = 0; i < n; i++){
        burst_rem[i] = p[i].bt;
    }

    int current_time = 0, completed = 0, prev = 0;
    
    queue<int> qu;

    while(completed != n){
        int idx = -1;
        
        for(int i = 0; i < n; i++){
            if(p[i].at <= current_time and is_completed[i] == 0 and mark[i] == 0){
                qu.push(i);
                mark[i] = 1;
            }
        }
        
        // queue<int> temp;
        // while(qu.size() != 0){
        //     cerr << qu.front() << "->";
        //     temp.push(qu.front());
        //     qu.pop();

        // } cerr << "\n";        

        // while(temp.size() != 0){
        //     cerr << temp.front() << "->";
        //     qu.push(temp.front());
        //     .pop();

        // } cerr << "\n";        

        if(qu.size() != 0){
            idx = qu.front();
            qu.pop();
        }

        // cerr << "RUNS\n";
        // cerr << burst_rem[idx] << " " << idx << "\n";

        if(idx != -1){
            cerr << "idx = " << idx << "\n";
            // cerr << "pid = " << p[idx].pid << "\n";

            if(burst_rem[idx] == p[idx].bt){
                p[idx].st = current_time;
                ttl_it += p[idx].st - prev;
            }

            int pass_time = min(tq, burst_rem[idx]);
            // cerr << "pass time = " << pass_time << "\n";

            burst_rem[idx] -= pass_time;
            
            current_time += pass_time;
            
            prev = current_time;

            cerr << "pass time = " << pass_time << "\n";
            cerr << "rem_bt = " << burst_rem[idx] << "\n";

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
            } else {
                qu.push(idx);
                cerr << "idx pushed = " << idx << "\n";
            }

            cerr << "\n";
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
    int tq; cin >> tq;
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

    vector<Process> ans = calc(p, tq);

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
    // freopen("error.txt", "w", stderr);   

    int T; cin >> T;
    int num = 0;
    while(T--){
        cout << "\t\t\t\t  Case : " << (++num) << "\n";
        solve(); cout << "\n";
    }
    
    return 0;
}