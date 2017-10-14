#include <iostream>
#include <vector>
#include "Chessboard.cpp"
#include "Queen.cpp"

int getSizeOfChessboard(int argc, char *argv[]) {
    int size = 0, i;
    if(argc == 1 || argc > 2 ) {
        do {
            printf("insert the size of the chessboard : ");
            scanf("%d", &size);
        } while (size < 4);
    } else {
        size = strtol(argv[1], NULL, 10);
        if(size < 4) {
            printf("ERROR!\n");
            if(size != 0) printf("The chessboard is too small\n");
            exit(0);
        }
    }
    return size;
}

int main(int argc, char *argv[]) {
    int size = getSizeOfChessboard(argc, argv);
    Chessboard chessboard;
    chessboard.setData(size);
    chessboard.getSolutions();
    return 0;
}
