#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main() {
    printf("Enter sequence of pages to file ex1_file.txt. Enter number of frames: ");
    
    int num_frames;
    scanf("%d", &num_frames);
    int frames[num_frames];
    unsigned int counters[num_frames];
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        counters[i] = 0;
    }

    FILE *file_seq = fopen("ex1_file.txt", "r");
    if (file_seq == NULL) {
        printf("File error!");
        exit(0);
    }

    int page_num;
    int hits = 0, miss = 0;

    while (fscanf(file_seq, "%d ", &page_num) != -1) {
        bool isIn = false;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page_num) {
                hits++;
                isIn = true;
                break;
            }
        }
        if (!isIn) {
            miss++;
            int counter_min = UINT32_MAX, counter_in;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    counter_in = j;
                    break;
                }
                if (counter_min > counters[j]) {
                    counter_min = counters[j];
                    counter_in = j;
                }
            }
            frames[counter_in] = page_num;
            counters[counter_in] = 1 << 31;
        }
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != page_num) {
                counters[j] = counters[j] >> 1;
            } else {
                counters[j] = (counters[j] >> 1) | (1 << 31);
            }
        }
    }
    printf("Hits: %d, Miss: %d, Ratio: %f", hits, miss, 1.0 * hits/miss);
    return 0;
}