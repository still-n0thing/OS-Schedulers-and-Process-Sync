#include <stdio.h>
 
typedef struct Data {
    long long pid; // unique identification given to every process
    long long at; // arrival_time : when process arrives into the queue
    long long bt; // burst_time : CPU time
    long long ct; // completion_time : when process execution completes
    long long tot; // turn around time : bt + wt
    long long wt; // wating_time : tot - bt
} Data;
 
void init_set(Data * dt ,long long pid, long long at, long long bt){
    dt->pid = pid;
    dt->at = at;
    dt->bt = bt;
    dt->ct = -1;
    dt->tot = -1;
    dt->wt = -1;
}
 
void swap_d(Data * x, Data * y){
    Data t;
    t = *x;
    *x = *y;
    *y = t;
}
 
void insertion_sort(Data dt[], long long n){
    for(long long i = 0; i < n; i++){
        long long j = i;
        while(j > 0 && dt[j].at < dt[j-1].at){
            swap_d(&dt[j], &dt[j-1]);
            j--;
        }
    }
}
 
void printall(Data dt[], long long n){
    printf("PID\tAT\tBT\tCT\tTOT\tWT\n");
    for(long long i = 0; i < n; i++){
        printf("%2lld\t%2lld\t%2lld\t%2lld\t%2lld\t%2lld\n",
        dt[i].pid, dt[i].at, dt[i].bt, dt[i].ct, dt[i].tot, dt[i].wt
        );
        fflush(stdout);
    }
}
 
void update(Data dt[], long long n){
    long long cur = 0;
    for(long long i = 0; i < n; i++){
        if(dt[i].at >= cur){
            dt[i].ct = dt[i].at + dt[i].bt;
        } else {
            dt[i].ct = cur + dt[i].bt;
        }
        cur = dt[i].ct;
        dt[i].tot = dt[i].ct - dt[i].at;
        dt[i].wt = dt[i].tot - dt[i].bt;
    }
}
 
double avg_tot(Data dt[], long long n){
    long long ans = 0;
    for(long long i = 0; i < n; i++){
        ans += (double)dt[i].tot;
    }
    return (double)ans/n;
}
 
double avg_wt(Data dt[], long long n){
    long long ans = 0;
    for(long long i = 0; i < n; i++){
        ans += (double)dt[i].wt;
    }
    return (double)ans/n;
}
 
void solve(long long tc){
    long long n; // number of process
    // IO : <number of process>
    scanf("%lld", &n);
   
    // All the process
    Data a[n];
 
    long long pid, at, bt; // required input
    // IO : <pid> <arrival-time> <burst-time>
 
    for(long long i = 0; i < n; i++){
        scanf("%lld %lld %lld", &pid, &at, &bt);
        init_set(&a[i], pid, at, bt);
    }
 
    insertion_sort(a, n);
    update(a, n);
 
    printf("\tTest Case : %lld \n", tc);
    printall(a, n);
    printf("Average TOT = %lf\n", avg_tot(a, n));
    printf("Average WT  = %lf\n", avg_wt(a, n));
    printf("\n");
}
 
int main(int argc, char const *argv[]){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
   
    long long t;
    scanf("%2lld", &t);
   
    for(long long i = 1; i <= t; i++){
        solve(i);
    }
 
    return 0;
}
