#include <bits/stdc++.h>

#define dbg(x) cerr<<#x<<" = "; deb(x); cerr<<endl;

using namespace std;

void solve(){

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL); 
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);   

    long long T; cin >> T;
    while(T--){
        solve();
    }
    
    return 0;
}


vector<Process> calc(vector<Process> & p){
    int n = p.size(), cur = 0, idx = 0;
    vector<Process> q, ans;
    for(int i = 0; i < n; i++){
        idx = right_less_equal(p, cur);

        if(p[i].at <= cur){
            q.push_back(p[i]);
        }
        sort(q.begin(), q.end(),
        [](const Process & left, const Process & right){
            return left.bt < right.bt;
        });

        if(q.size() and p[i].at  >= cur){
            Process temp = q[0]; q.erase(q.begin());
            temp.rt = (cur - temp.at > 0 ? cur - temp.at : 0);
            cur += temp.bt;
            temp.ct = cur;
            temp.tot = temp.ct - temp.at;
            temp.wt = temp.tot - temp.bt;
            ans.push_back(temp);
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