#include <iostream>
#include <vector>

uint s = 4, c = 0;
std::vector<std::vector <int>> repo;

int getSizeOfChessboard(int argc, char *argv[]) {
    uint size = 0, i;
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

std::vector<int> merge(std::vector<int> v1, std::vector<int> v2) {
    uint i1, i2;
    std::vector<int> r;
    for(i1 = 0, i2 = 0; v1.size() > i1 && v2.size() > i2;) {
        if(v1[i1] <= v2[i2]){
            if(v1[i1] == v2[i2]) r.push_back(v1[i1]);
            i1++;
        } else i2++;
    }
    return r;
}

std::vector<int> gfpx(uint x, uint y){
    std::vector<int> v;
    uint x1 = x + 1;
    if(x == (s - 1)) return v;
    for(uint x1 = x + 1; x1 < s; x1++) {
        for(uint y1 = 0; y1 < s; y1++) {
            if(y1 == y)continue;
            if((x1 + y1) == (x + y) || (x1 - y1) == (x - y)) continue;
            v.push_back(y1 + s * x1);
        }
    }
    return v;
}

void * pr(std::vector<int> v) {
    uint x, i, y;
    i = 1;
    printf("pr: ");
    for(uint j = 0; j < v.size(); j++) printf("%d ", v[j]);
    printf("\n");
    /*printf("\t");
    for (x = 0; x < s; x++) printf("  %d ", x);
    printf("\n");
    for(x = 0; x < s; x++) {
        printf("%d\t", x);
        for(y = 0; y < s && i <= s; y++) {
            if(v[s - i] == y + s * x) {
                printf("| @ ");
                i++;
            } else {
                printf("|   ");
            }
        }
        printf("\n");
    }/**/
}

std::vector<int> sol(uint n, std::vector<int> pool) {
    uint i;
    std::vector<int> ret, next;

    ret.push_back(n);
    for(i = 0; i < pool.size(); i++) {
        if(pool[i]/s > (n/s + 1)) break;
        ret = sol(pool[i], merge(pool, repo[pool[i]]));
        ret.push_back(n);
        if(ret.size() <= s ) {
            pr(ret);
            c++; //Tenere il conto delle soluzioni
        }
    }
    return ret;
}

int main(int argc, char *argv[]) {
    s = getSizeOfChessboard(argc, argv);

    for(uint x = 0; x < s; x++) {
        for(uint y = 0; y < s; y++) {
            repo.push_back(gfpx(x, y));
        }
    }

/** TEST FOR FIRST SETS OF DATA ** /
    for(uint x = 0; x < repo.size(); x++) {
        printf("%d :", x);
        for(uint y = 0; y < repo[x].size(); y++) {
            printf("%d ", repo[x][y]);
        }
        printf("\n");
    }
/**/

    //std::vector <int> x = merge(repo[0],repo[6]); //TEST FOR MERGE
    //for(uint j = 0; j < x.size(); j++) printf("%d\n", x[j]);
    for(uint i = 0; i < s + 1; i++) sol(i, repo[i]);
    printf("ok, printed %d solutions\n", c);
    return 0;
}
