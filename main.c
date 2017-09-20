#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int width;
} chessboardPosition;

int main(int argc, char *argv[]) {
    int size = 0, i;
    if(argc == 1 || argc > 2 ) {
        printf("insert the size of the chessboard : ");
        scanf("%d", &size);
    } else {
        size = strtol(argv[1], NULL, 10);
    }
    chessboardPosition queensPosition[size];
    if(size%2 == 1) {
        queensPosition[size].height = size;
        queensPosition[size].width = size;
        printf("queen jolly:\t(%d, %d)\n", size, size);
        size--;
    }
    if (size%3 == 2) {
        printf("sorry, this method not work for this size..\n");
        exit(0);
    }
    queensPosition[0].height = 2;
    queensPosition[0].width = 1;
    printf("queen 1:\t(0, 1)\n");
    for(i = 1; i < size; i++) {
        if(queensPosition[i - 1].height == size) {
            queensPosition[i].height = 0;
        } else {
            queensPosition[i].height = queensPosition[i - 1].height + 2;
        }
        queensPosition[i].width = queensPosition[i - 1].width + 1;
        printf("queen %d:\t(%d, %d)\n", (i + 1), queensPosition[i].width, queensPosition[i].height);
    }
    exit(0);
}
