#include <stdio.h>
#include <stdlib.h>

#define MAX_SEGMENTS 200
#define TOTAL_MEMORY 1024

typedef struct {
    int start;
    int size;
    int free;
    int pid;
} Segment;

Segment segs[MAX_SEGMENTS];
int seg_count = 0;
int next_pid = 1;
int next_fit_index = 0;

void init_memory() {
    seg_count = 1;
    segs[0].start = 0;
    segs[0].size = TOTAL_MEMORY;
    segs[0].free = 1;
    segs[0].pid = 0;
    next_pid = 1;
    next_fit_index = 0;
}

void print_memory() {
    printf("\nMemory Layout (start,size,free/pid):\n");
    for (int i = 0; i < seg_count; i++) {
        if (segs[i].free)
            printf("[%d,%d,FREE] ", segs[i].start, segs[i].size);
        else
            printf("[%d,%d,PID:%d] ", segs[i].start, segs[i].size, segs[i].pid);
    }
    printf("\n");
}

void coalesce() {
    for (int i = 0; i < seg_count - 1; ) {
        if (segs[i].free && segs[i+1].free) {
            segs[i].size += segs[i+1].size;
            for (int j = i+1; j < seg_count - 1; j++)
                segs[j] = segs[j+1];
            seg_count--;
        } else {
            i++;
        }
    }
}

int split_and_assign(int idx, int req_size) {
    if (req_size <= 0) return -1;
    if (!segs[idx].free || segs[idx].size < req_size) return -1;
    int pid = next_pid++;
    if (segs[idx].size == req_size) {
        segs[idx].free = 0;
        segs[idx].pid = pid;
    } else {
        if (seg_count + 1 >= MAX_SEGMENTS) return -1;
        for (int j = seg_count; j > idx; j--) segs[j] = segs[j-1];
        seg_count++;
        segs[idx+1].start = segs[idx].start + req_size;
        segs[idx+1].size = segs[idx].size - req_size;
        segs[idx+1].free = 1;
        segs[idx+1].pid = 0;
        segs[idx].size = req_size;
        segs[idx].free = 0;
        segs[idx].pid = pid;
    }
    return pid;
}

int allocate_first_fit(int req_size) {
    for (int i = 0; i < seg_count; i++) {
        if (segs[i].free && segs[i].size >= req_size) return split_and_assign(i, req_size);
    }
    return -1;
}

int allocate_best_fit(int req_size) {
    int best_idx = -1;
    int best_size = 1<<30;
    for (int i = 0; i < seg_count; i++) {
        if (segs[i].free && segs[i].size >= req_size) {
            if (segs[i].size < best_size) {
                best_size = segs[i].size;
                best_idx = i;
            }
        }
    }
    if (best_idx == -1) return -1;
    return split_and_assign(best_idx, req_size);
}

int allocate_worst_fit(int req_size) {
    int worst_idx = -1;
    int worst_size = -1;
    for (int i = 0; i < seg_count; i++) {
        if (segs[i].free && segs[i].size >= req_size) {
            if (segs[i].size > worst_size) {
                worst_size = segs[i].size;
                worst_idx = i;
            }
        }
    }
    if (worst_idx == -1) return -1;
    return split_and_assign(worst_idx, req_size);
}

int allocate_next_fit(int req_size) {
    int start = next_fit_index;
    int i = start;
    int wrapped = 0;
    while (1) {
        if (segs[i].free && segs[i].size >= req_size) {
            next_fit_index = i;
            int pid = split_and_assign(i, req_size);
            next_fit_index = (next_fit_index + 1) % seg_count;
            return pid;
        }
        i++;
        if (i >= seg_count) {
            i = 0;
            wrapped = 1;
        }
        if (i == start && wrapped) break;
    }
    return -1;
}

int allocate_by_choice(int choice, int req_size) {
    if (req_size <= 0) return -1;
    if (choice == 1) return allocate_first_fit(req_size);
    if (choice == 2) return allocate_best_fit(req_size);
    if (choice == 3) return allocate_worst_fit(req_size);
    if (choice == 4) return allocate_next_fit(req_size);
    return -1;
}

int deallocate_by_pid(int pid) {
    if (pid <= 0) return -1;
    int found = 0;
    for (int i = 0; i < seg_count; i++) {
        if (!segs[i].free && segs[i].pid == pid) {
            segs[i].free = 1;
            segs[i].pid = 0;
            found = 1;
        }
    }
    if (found) coalesce();
    return found ? 0 : -1;
}

void menu() {
    printf("\nMemory Allocation Simulation\n");
    printf("Total memory = %d units\n", TOTAL_MEMORY);
    printf("1. Allocate (First Fit)\n");
    printf("2. Allocate (Best Fit)\n");
    printf("3. Allocate (Worst Fit)\n");
    printf("4. Allocate (Next Fit)\n");
    printf("5. Deallocate by PID\n");
    printf("6. Display Memory\n");
    printf("7. Initialize Memory\n");
    printf("8. Exit\n");
}

int main() {
    init_memory();
    int choice;
    while (1) {
        menu();
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 8) break;
        if (choice >=1 && choice <=4) {
            int size;
            printf("Enter block size to allocate: ");
            if (scanf("%d", &size) != 1) break;
            int pid = allocate_by_choice(choice, size);
            if (pid == -1) printf("Allocation failed for size %d\n", size);
            else printf("Allocated PID=%d for size %d\n", pid, size);
        } else if (choice == 5) {
            int pid;
            printf("Enter PID to deallocate: ");
            if (scanf("%d", &pid) != 1) break;
            if (deallocate_by_pid(pid) == 0) printf("Deallocated PID %d\n", pid);
            else printf("PID %d not found\n", pid);
        } else if (choice == 6) {
            print_memory();
        } else if (choice == 7) {
            init_memory();
            printf("Memory reinitialized\n");
        } else {
            printf("Invalid option\n");
        }
    }
    return 0;
}
