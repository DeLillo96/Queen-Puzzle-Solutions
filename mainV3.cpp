#include <iostream>
#include <vector>

uint s, c = 0;
std::vector<std::vector <int>> repo;

int getSizeOfChessboard(int argc, char *argv[]) {
    if(argc == 1 || argc > 2 ) {
        std::cout << "ERROR!\nlunch me with size of chessboard:\n\t./<program_name> n\nRemember: n is positive!";
        exit(0);
    } else {
        return strtol(argv[1], NULL, 10);
    }
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
    i = 0;
    std::cout << "pr: ";
    for(uint j = 0; j < v.size(); j++) std::cout << v[j] << " ";
    std::cout << "\n";
    /* USE FOR SEXY PRINT * /
    printf("\t");
    for (x = 0; x < s; x++) printf("  %d ", x);
    printf("\n");
    for(x = 0; x < s; x++) {
        printf("%d\t", x);
        for(y = 0; y < s && i < s; y++) {
            if(v[i] == y + s * x) {
                printf("| @ ");
                i++;
            } else {
                printf("|   ");
            }
        }
        printf("\n");
    }/**/
}

void * sol(uint n, std::vector<int> pool, std::vector<int> pushed) {
    uint i, max;

    pushed.push_back(n);
    max = s * (pushed.size() + 1);
    for(i = 0; i < pool.size(); i++) {
        if(pool[i] >= max) break;
        sol(pool[i], merge(pool, repo[pool[i]]), pushed);
    }
    if(pushed.size() == s) {
        pr(pushed);
        c++;
    }
}

int main(int argc, char *argv[]) {
    s = getSizeOfChessboard(argc, argv);
    std::vector<int> v;

    for(uint x = 0; x < s; x++) {
        for(uint y = 0; y < s; y++) {
            repo.push_back(gfpx(x, y));
        }
    }

/** TESTS** /
    for(uint x = 0; x < repo.size(); x++) { //REPOSITORY
        printf("%d :", x);
        for(uint y = 0; y < repo[x].size(); y++) {
            printf("%d ", repo[x][y]);
        }
        printf("\n");
    }
    std::vector <int> x = merge(repo[0],repo[6]); //MERGE
/**/

    for(uint i = 0; i < s; i++) {
        std::cout << (i*100)/s << "%\n";
        sol(i, repo[i], v);
    }
    std::cout << "finish!\nfound " << c << " solutions\n";
    return 0;
}
