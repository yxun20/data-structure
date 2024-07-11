#pragma warning(disable:4996)
#include <stdio.h>

int hanoi(int n, char departure, char auxiliary, char arrival) {
    if (n == 1) {
        return 1;
    }
    else {
        int cost = 0;
        cost += hanoi(n - 1, departure, arrival, auxiliary);
        cost += n;
        cost += hanoi(n - 1, auxiliary, departure, arrival);
        return cost;
    }
}

int main() {
    FILE* inputFile = fopen("input_hw1.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL) {
        printf("Failed to open input_hw1.txt input file.\n");
        return 0;
    }
    if (outputFile == NULL) {
        printf("Failed to create output.txt output file.\n");
        fclose(inputFile);
        return 0;
    }

    int caseNum;
    fscanf(inputFile, "%d\n", &caseNum);

    for (int i = 0; i < caseNum; i++) {
        int diskNum;
        fscanf(inputFile, "%d\n", &diskNum);
        int costSum = hanoi(diskNum, 'A', 'B', 'C');
        fprintf(outputFile, "%d\n", costSum);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}