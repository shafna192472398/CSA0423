#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int pid[n], bt[n], p[n], rt[n], wt[n], tat[n];
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&pid[i],&bt[i],&p[i]);
        rt[i]=bt[i];
        wt[i]=tat[i]=0;
    }

    int completed=0, time=0;

    while(completed<n){
        int idx=-1, maxp=-1;
        for(int i=0;i<n;i++){
            if(rt[i]>0 && p[i]>maxp){
                maxp=p[i];
                idx=i;
            }
        }
        rt[idx]--;
        time++;
        if(rt[idx]==0){
            completed++;
            tat[idx]=time;
            wt[idx]=tat[idx]-bt[idx];
        }
    }

    printf("PID\tBT\tP\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",pid[i],bt[i],p[i],wt[i],tat[i]);
    }

    return 0;
}
