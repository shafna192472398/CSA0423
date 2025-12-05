#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int pid[n], bt[n], wt[n], tat[n];
    
    for(int i=0;i<n;i++){
        scanf("%d%d", &pid[i], &bt[i]);
    }
    
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(bt[j] < bt[i]) {
                int t = bt[i]; bt[i] = bt[j]; bt[j] = t;
                t = pid[i]; pid[i] = pid[j]; pid[j] = t;
            }
        }
    }
    
    wt[0] = 0;
    for(int i=1;i<n;i++){
        wt[i] = wt[i-1] + bt[i-1];
    }
    
    for(int i=0;i<n;i++){
        tat[i] = wt[i] + bt[i];
    }
    
    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }
    
    return 0;
}
