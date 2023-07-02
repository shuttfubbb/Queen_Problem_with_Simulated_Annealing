#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007

const int N = 1000;
int patience = 45000;
int board[N];
int cross1[2*N];
int cross2[2*N];
int nCk[1001][1001];

void clear_calc(){
    for(int i = 0; i < 2*N; ++i){
        cross1[i] = 0;
        cross2[i] = 0;
    }
}

void make_pascal_triangle(){
    for (int i = 0; i <= 1000; i++) {
		for (int j = 0; j <= 1000; j++) {
			if (i == j || j == 0)nCk[i][j] = 1;
			else nCk[i][j] = nCk[i - 1][j - 1] + nCk[i - 1][j];
			nCk[i][j] %= mod;
		}
	}
}

int calc_attacks(){
    int attacks = 0;
    clear_calc();
    for(int i=0; i < N; ++i){
        int j = board[i];
        cross1[i-j+N] += 1;
        cross2[i+j-1] += 1;
    }
    for(int i=0; i < 2*N; ++i){
        if(cross1[i] >= 2){
            attacks += nCk[cross1[i]][2];
        }
        if((cross2[i] >= 2)){
            attacks += nCk[cross2[i]][2];
        }
    }
    return attacks;
}

void show(){
    cout << "Loi giai la:\n";
    for(int i=0; i<N; ++i){
        cout << board[i] << " ";
    }
    cout << "\nSo quan hau de doa nhau: " << calc_attacks();
}

void solve() {
    double temperature = 100000, cooling_rate = 0.999;
    int iterations = 0;
    int current_attacks = calc_attacks();
    while(current_attacks > 0 ) {
        int x = rand() % N, y = rand() % N;
        swap(board[x], board[y]);
        int new_attacks = calc_attacks();
        int delta = new_attacks - current_attacks;
        if(delta <= 0 || exp(-delta / temperature) > (double)rand() / RAND_MAX) {
            current_attacks = new_attacks;
        } else {
            swap(board[x], board[y]);
        }
        temperature *= cooling_rate;
        iterations++;
    }
    cout << "So lan lap la: " << iterations << endl;
    show();
}

void init(){
    for(int i = 0; i < N; i++) {
        board[i] = i;
    }
}

int main() {
    init();
    clear_calc();
    make_pascal_triangle();
    solve();
    return 0;
}