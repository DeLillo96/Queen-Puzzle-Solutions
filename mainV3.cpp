#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
uint s, c = 0;
vector<vector <int>> repo;

int getSizeOfChessboard(int argc, char *argv[]) {
    if(argc == 1 || argc > 2 ) {
        cout << "ERROR!\nlunch me with size of chessboard:\n\t./<program_name> n\nRemember: n is positive!";
        exit(0);
    } else {
        return strtol(argv[1], NULL, 10);
    }
}

vector<int> merge(vector<int> v1, vector<int> v2) {
    uint i1, i2;
    vector<int> r;
    for(i1 = 0, i2 = 0; v1.size() > i1 && v2.size() > i2;) {
        if(v1[i1] <= v2[i2]){
            if(v1[i1] == v2[i2]) r.push_back(v1[i1]);
            i1++;
        } else i2++;
    }
    return r;
}

vector<int> gfpx(uint x, uint y){
    vector<int> v;
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

void * pr(vector<int> v) {
    uint x, i, y;
    i = 0;
    cout << '\t';
    for (x = 0; x < s; x++) cout << "  " << x << " ";
    cout << '\n';
    for(x = 0; x < s; x++) {
        cout << x << '\t';
        for(y = 0; y < s && i < s; y++) {
            if(v[i] == y + s * x) {
                cout << "| X ";
                i++;
            } else {
                cout << "|   ";
            }
        }
        printf("\n");
    }
}

void * sol(uint n, vector<int> pool, vector<int> pushed) {
    uint i, max, j;

    pushed.push_back(n);
    if(pushed.size() == s) {
        pr(pushed);
        c++;
        return NULL;
    }
    max = s * (pushed.size() + 1);
    j = pushed.size() + pool.size() - s;
    for(i = 0; i < pool.size() && j >= i && pool[i] < max; i++) {
        sol(pool[i], merge(pool, repo[pool[i]]), pushed);
    }
}

int main(int argc, char *argv[]) {
    s = getSizeOfChessboard(argc, argv);

    for(uint x = 0; x < s; x++) {
        for(uint y = 0; y < s; y++) {
            repo.push_back(gfpx(x, y));
        }
    }

    for(uint i = 0; i < s; i++) {
        sol(i, repo[i], vector <int> ());
    }
    cout << "finish!\nfound " << c << " solutions\n";
    return 0;
}
