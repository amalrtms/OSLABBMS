#include <stdio.h>

int count=0;

int search(int key, int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == key)
            return i;
    }
    return -1;
}

void printFrames(int frames[], int f) {
    printf("PF No. %2d: ", ++count);
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int f) {
    int frames[f];
    for (int i = 0; i < f; i++) frames[i] = -1;
    int faults = 0, index = 0;

    printf("\nFIFO Page Replacement Process:\n");
    count = 0;

    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames, f) == -1) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            printFrames(frames, f);
            faults++;
        }
    }
    printf("FIFO Page Faults: %d\n", faults);
}

int findLRU(int time[], int f) {
    int min = time[0], pos = 0;
    for (int i = 1; i < f; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n, int f) {
    int frames[f], time[f];
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
    int faults = 0, t = 0;
    printf("\nLRU Page Replacement Process:\n");
    count = 0;
    for (int i = 0; i < n; i++) {
        t++;
        int pos = search(pages[i], frames, f);
        if (pos != -1) {
            time[pos] = t;
        } else {
            int rep = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    rep = j;
                    break;
                }
            }
            if (rep == -1) rep = findLRU(time, f);
            frames[rep] = pages[i];
            time[rep] = t;
            printFrames(frames, f);
            faults++;
        }
    }
    printf("LRU Page Faults: %d\n", faults);
}

int findOptimal(int pages[], int frames[], int n, int current, int f) {
    int index = -1, farthest = -1;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return (index == -1) ? 0 : index;
}

void optimal(int pages[], int n, int f) {
    int frames[f], faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;
    printf("\nOptimal Page Replacement Process:\n");
    count = 0;
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frames, f) == -1) {
            int inserted = 0;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    inserted = 1;
                    break;
                }
            }
            if (!inserted) {
                int victim = findOptimal(pages, frames, n, i, f);
                frames[victim] = pages[i];
            }
            printFrames(frames, f);
            faults++;
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}

void main() {
    int f, n;
    printf("Enter no of Frames: ");
    scanf("%d", &f);
    printf("Enter length of reference string: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);
}