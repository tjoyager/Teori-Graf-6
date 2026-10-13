#include <bits/stdc++.h>
using namespace std;

void cariJalur(int indeks, vector<vector<int> >& sebelumnya, vector<int>& angka, 
                    vector<int>& jalur, vector<vector<int> >& semuaHasil) {
    jalur.push_back(angka[indeks]);

    if (sebelumnya[indeks].empty()) {
        vector<int> hasil = jalur;
        reverse(hasil.begin(), hasil.end());
        semuaHasil.push_back(hasil);
    } else {
        for (int k = 0; k < sebelumnya[indeks].size(); k++) {
            cariJalur(sebelumnya[indeks][k], sebelumnya, angka, jalur, semuaHasil);
        }
    }

    jalur.pop_back();
}

int main() {
    int n;

    cout << "Largest Monotonically Increasing Subsequence\n";
    cout << "Masukkan jumlah elemen: ";
    cin >> n;

    if (n <= 0) {
        cout << "Jumlah elemen harus lebih dari 0.\n";
        return 0;
    }

    vector<int> angka(n);
    vector<int> dp(n, 1);
    vector<vector<int> > sebelumnya(n);

    cout << "Masukkan elemen:\n";
    for (int i = 0; i < n; i++) {
        cin >> angka[i];
    }

    int panjangMax = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (angka[j] < angka[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    sebelumnya[i].clear();
                    sebelumnya[i].push_back(j);
                } else if (dp[j] + 1 == dp[i]) {
                    sebelumnya[i].push_back(j);
                }
            }
        }

        if (dp[i] > panjangMax) {
            panjangMax = dp[i];
        }
    }

    vector<vector<int> > semuaHasil;
    vector<int> jalur;

    for (int i = 0; i < n; i++) {
        if (dp[i] == panjangMax) {
            cariJalur(i, sebelumnya, angka, jalur, semuaHasil);
        }
    }

    cout << "\nDeret awal: ";
    for (int i = 0; i < n; i++) {
        cout << angka[i] << " ";
    }

    cout << "\nPanjang LMIS: " << panjangMax;
    cout << "\nJumlah subsequence: " << semuaHasil.size();
    cout << "\nSemua subsequence terpanjang:\n";

    for (int i = 0; i < semuaHasil.size(); i++) {
        cout << i + 1 << ". ";
        for (int j = 0; j < semuaHasil[i].size(); j++) {
            cout << semuaHasil[i][j];
            if (j < semuaHasil[i].size()-1) cout  << " -> ";
        }
        cout << "\n";
    }

    return 0;
}