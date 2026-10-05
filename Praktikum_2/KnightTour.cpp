#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int N = 8;
int startX, startY; 
int modePilihan; 

int langkahBaris[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int langkahKolom[8] = {1, 2, 2, 1, -1, -2, -2, -1};

struct OpsiLangkah {
    int x, y, derajat;
    bool operator<(const OpsiLangkah& lain) const {
        return derajat < lain.derajat; 
    }
};

bool posisiValid(int x, int y, const vector<vector<int>>& papan) {
    return (x >= 0 && x < N && y >= 0 && y < N && papan[x][y] == -1);
}

int hitungDerajat(int x, int y, const vector<vector<int>>& papan) {
    int jumlah = 0;
    for (int i = 0; i < 8; i++) {
        if (posisiValid(x + langkahBaris[i], y + langkahKolom[i], papan)) jumlah++;
    }
    return jumlah;
}

bool cariRuteKuda(int x, int y, int urutan, vector<vector<int>>& papan) {
    if (urutan == N * N) {
        if (modePilihan == 1) {
            return true;
        } else {
            for (int i = 0; i < 8; i++) {
                if (x + langkahBaris[i] == startX && y + langkahKolom[i] == startY) {
                    return true;
                }
            }
            return false;
        }
    }

    vector<OpsiLangkah> langkahSelanjutnya;
    for (int i = 0; i < 8; i++) {
        int nextX = x + langkahBaris[i];
        int nextY = y + langkahKolom[i];
        if (posisiValid(nextX, nextY, papan)) {
            langkahSelanjutnya.push_back({nextX, nextY, hitungDerajat(nextX, nextY, papan)});
        }
    }

    //Warnsdorff's
    sort(langkahSelanjutnya.begin(), langkahSelanjutnya.end());

    //DFS
    for (OpsiLangkah opsi : langkahSelanjutnya) {
        papan[opsi.x][opsi.y] = urutan;
        
        if (cariRuteKuda(opsi.x, opsi.y, urutan + 1, papan)) {
            return true; 
        }
        
        papan[opsi.x][opsi.y] = -1;
    }

    return false;
}

int main(void) {
    vector<vector<int>> papan(N, vector<int>(N, -1));

    cout << "The Knight's Tour\n";
    cout << "1. Open Tour\n";
    cout << "2. Closed Tour\n";
    cout << "Pilih mode (1/2): ";
    cin >> modePilihan;

    cout << "Masukkan koordinat awal bidak kuda (baris 0-7, kolom 0-7): ";
    cin >> startX >> startY;

    if (startX < 0 || startX >= N || startY < 0 || startY >= N || (modePilihan != 1 && modePilihan != 2)) {
        cout << "Input koordinat atau mode tidak valid.\n";
        return 0;
    }

    papan[startX][startY] = 0; 

    if (cariRuteKuda(startX, startY, 1, papan)) {
        cout << "\nRute berhasil ditemukan.\n";
        if (modePilihan == 2) cout << "Closed Tour: Koordinat akhir terhubung langsung dengan koordinat awal\n";
        
        cout << "\nMatriks Langkah Bidak (0 - 63):\n\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (papan[i][j] == 0) {
                    cout << "\033[1;32m" << setw(3) << papan[i][j] << "\033[0m "; //Start hijau
                } else if (papan[i][j] == 63) {
                    cout << "\033[1;31m" << setw(3) << papan[i][j] << "\033[0m "; //Finish merah
                } else {
                    cout << setw(3) << papan[i][j] << " ";
                }
            }
            cout << "\n\n";
        }
    } else {
        cout << "\nGagal menemukan rute.\n";
    }

    return 0;
}