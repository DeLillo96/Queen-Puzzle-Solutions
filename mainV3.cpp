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

vector<int> subbed(vector<int> v1, vector<int> v2) {
    for (uint i = 0, j = 0; i < v1.size() && j < v2.size();){
        if (v1[i] < v2[j]) i++;
        else if (v1[i] > v2[j]) j++;
        else {
            v1.erase(v1.begin() + i);
            j++;
        }
    }
    return v1;
}

vector<int> get_free_position(uint x, uint y){
    vector<int> v;
    if(y == (s - 1)) return v;
    for(uint y1 = y + 1; y1 < s; y1++) {
        for(uint x1 = 0; x1 < s; x1++) {
            if(x1 == x)continue;
            if((x1 + y1) == (x + y) || (x1 - y1) == (x - y)) continue;
            v.push_back(y1 * s + x1);
        }
    }
    return v;
}

vector<int> get_occuped_position(uint x, uint y){
    vector<int> v;
    int n = 0, level = 1, shift;
    for(uint x1 = x; x1 < s; x1++) {
        v.push_back(s * y + x1);
    }
    for(uint y1 = y + 1; y1 < s; y1++, level++) {
        n = s * y1 + x;
        shift = s * y1;
        if(n >= shift + level) v.push_back(n - level);
        v.push_back(n);
        if(n < shift + s - level) v.push_back(n + level);
    }
    return v;
}

void * fill_repository(){
    for(uint y = 0; y < s; y++) {
        cout << y << '\n';
        if (y == 0) {
            for(uint x = 0; x < s; x++) {
                repo.push_back(get_free_position(x, 0));
            }
        } else {
            for(uint x = 0; x < s; x++){
                repo.push_back(get_occuped_position(x, y));
            }
        }
    }
}

void * print(vector<int> v) {
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

void * solutions(uint n, vector<int> pool, vector<int> pushed) {
    pushed.push_back(n);
    int size_p = pushed.size(), size_r = size_p + pool.size();
    if(size_p == s) {
        print(pushed);
        c++;
        return NULL;
    }
    size_p++;
    for(; size_r >= s && pool[0] < (s * size_p); size_r--) {
        solutions(pool[0], subbed(pool, repo[pool[0]]), pushed);
        pool.erase(pool.begin());
    }
}

int main(int argc, char *argv[]) {
    s = get_size_of_chessboard(argc, argv);

    fill_repository();

    for(uint i = 0; i < s; i++)
        solutions(i, repo[i], vector <int> ());
    cout << "finish!\nfound " << c << " solutions\n";
    return 0;
}
