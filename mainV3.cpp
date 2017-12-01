#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
uint s, c = 0;
vector<vector <int>> repo;

int get_size_of_chessboard(int argc, char *argv[]) {
    if(argc == 1 || argc > 2 ) {
        cout << "ERROR!\nlunch me with size of chessboard:\n\t./<program_name> n\nRemember: n is positive!";
        exit(0);
    } else {
        return strtol(argv[1], NULL, 10);
    }
}

vector<int> merge(vector<int> v1, vector<int> v2) {
    vector<int> r;
    for (uint i = 0, j = 0; i < v1.size() && j < v2.size();){
        if (v1[i] < v2[j]) i++;
        else if (v1[i] > v2[j]) j++;
        else {
            r.push_back(v2[j++]);
            i++;
        }
    }
    return r;
}

vector<int> get_free_position(uint x, uint y){
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
    cout << "  ";
    for (x = 0; x < s; x++) cout << "  " << x << " ";
    cout << '\n';
    for(x = 0; x < s; x++) {
        cout << char('A' + x) << ' ';
        for(y = 0; y < s && i < s; y++) {
            if(v[i] == y + s * x) {
                cout << "| X ";
                i++;
            } else {
                cout << "|   ";
            }
        }
        cout << "|\n";
    }
}

void * sol(uint n, vector<int> pool, vector<int> pushed) {
    pushed.push_back(n);
    if(pushed.size() == s) {
        pr(pushed);
        c++;
        return NULL;
    }
    for(
        uint i = 0;
        i < pool.size() &&
        (pushed.size() + pool.size()) >= s &&
        pool[i] < (s * (pushed.size() + 1));
        i++
    ) sol(pool[i], merge(pool, repo[pool[i]]), pushed);
}

int main(int argc, char *argv[]) {
    s = get_size_of_chessboard(argc, argv);

    for(uint x = 0; x < s; x++)
        for(uint y = 0; y < s; y++)
            repo.push_back(get_free_position(x, y));

    for(uint i = 0; i < s; i++)
        sol(i, repo[i], vector <int> ());
    cout << "finish!\nfound " << c << " solutions\n";
    return 0;
}
