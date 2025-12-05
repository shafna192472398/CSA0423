#include <stdio.h>

int main() {
    int n, qt;
    scanf("%d", &n);
    int pid[n], bt[n], rt[n], wt[n], tat[n];
    for(int i=0;i<n;i++){
        scanf("%d%d", &pid[i], &bt[i]);
        rt[i]=bt[i];
        wt[i]=tat[i]=0;
    }
    scanf("%d", &qt);

    int time=0, done=0;
    while(done<n){
        for(int i=0;i<n;i++){
            if(rt[i]>0){
                if(rt[i]>qt){
                    time+=qt;
                    rt[i]-=qt;
                } else {
                    time+=rt[i];
                    rt[i]=0;
                    tat[i]=time;
                    wt[i]=tat[i]-bt[i];
                    done++;
                }
            }
        }
    }

    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }
    return 0;
}
