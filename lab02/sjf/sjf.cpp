#include <bits/stdc++.h>

#define dbg(x) cerr<<#x<<" = " << x << endl;

using namespace std;

class Process {
public:
    int pid;
    int at; // arrival time
    int bt; // burst time
    int ct; // start time
    int tot; // turn around time
    int wt; // wating time
    int rt; // response time

    void set(int pid, int at, int bt){
        this->pid = pid;
        this->at = at;
        this->bt = bt;
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
    printElement("CT", width);
    printElement("TOT", width);
    printElement("WT", width);
    printElement("RT", width);
    cout << "\n";

    for(int i = 0; i < n; i++){
        printElement(p[i].pid, width);
        printElement(p[i].at, width);
        printElement(p[i].bt, width);
        printElement(p[i].ct, width);
        printElement(p[i].tot, width);
        printElement(p[i].wt, width);
        printElement(p[i].rt, width);
        cout << "\n";
    }

}

int right_less_equal(vector<Process> & a, int x){
    int n = a.size(), l = -1, r = n, m = 0;
    while(r > l+1){
        m = (l+r)/2;
        if(a[m].at <= x){
            l = m;
        }
        else{
            r = m;
        }
    }
    return l; // return -1 if x < a[0]
}

vector<Process> calc(vector<Process> & p){
    int n = p.size(), cur = 0, idx = 0;
    vector<Process> ans, q;
    for(int i = 0; i < n; i++){
        idx = right_less_equal(p, cur);
        dbg(idx);
        if(idx == -1){
            cur = p[i].at;
            idx = right_less_equal(p, cur);
        }
        q.push_back(p[i]);
        if(i >= idx and q.size()){
            sort(q.begin(), q.end(),
            [](const Process & left, const Process & right){
                return left.bt < right.bt;
            });
            Process temp = q[0]; q.erase(q.begin());
            temp.rt = (cur - temp.at > 0 ? cur - temp.at : 0);
            cur += temp.bt;
            temp.ct = cur;
            temp.tot = temp.ct - temp.at;
            temp.wt = temp.tot - temp.bt;
            ans.push_back(temp);
            idx = right_less_equal(p, cur);
        }
    }
    while(q.size()){
        Process temp = q[0]; q.erase(q.begin());
        temp.rt = (cur - temp.at > 0 ? cur - temp.at : 0);
        cur += temp.bt;
        temp.ct = cur;
        temp.tot = temp.ct - temp.at;
        temp.wt = temp.tot - temp.bt;
        ans.push_back(temp);
    }

    return ans;
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
    
    printall(p); // O(n)
    cout << "\n";

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
        cout << "\t\t\tCase : " << (++num) << "\n";
        solve(); cout << "\n";
    }
    
    return 0;
}