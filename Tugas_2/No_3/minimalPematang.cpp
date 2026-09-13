#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pematang {
    int id; //Nomor pematang
    int u;  //Area 1 yang dibatasi
    int v;  //Area 2 yang dibatasi
};

int jumlah_area, jumlah_pematang;
vector<Pematang> daftar_pematang;
vector<vector<int>> semua_solusi;

int find_parent(vector<int>& parent, int i) {
    if (parent[i] == i) return i;

    return find_parent(parent, parent[i]); 
}

void cari_spanning_trees(int index_pematang, vector<int>& parent, vector<int>& lubang_saat_ini, int edge_terpilih) {
    if (edge_terpilih == jumlah_area - 1) {
        semua_solusi.push_back(lubang_saat_ini);
        return;
    }

    if (index_pematang >= jumlah_pematang) {
        return;
    }

    Pematang p = daftar_pematang[index_pematang];
    int root_u = find_parent(parent, p.u);
    int root_v = find_parent(parent, p.v);

    if (root_u != root_v) {
        vector<int> parent_backup = parent; 
        
        parent[root_u] = root_v;
        lubang_saat_ini.push_back(p.id);

        cari_spanning_trees(index_pematang + 1, parent, lubang_saat_ini, edge_terpilih + 1);

        lubang_saat_ini.pop_back();
        parent = parent_backup;
    }

    cari_spanning_trees(index_pematang + 1, parent, lubang_saat_ini, edge_terpilih);
}

int main(void) {
    cout << "=== SISTEM PENGAIRAN PETAK SAWAH (SPANNING TREES) ===\n\n";
    
    cout << "Masukkan jumlah area (total petak sawah + 1 area luar): ";
    cin >> jumlah_area;
    cout << "Masukkan jumlah keseluruhan pematang: ";
    cin >> jumlah_pematang;
    
    daftar_pematang.resize(jumlah_pematang);
    
    cout << "\nMasukkan data batas (Area_A Area_B No_Pematang):\n";
    cout << "Catatan: Gunakan angka 0 untuk area luar (selokan pembuangan)\n";
    
    for (int i = 0; i < jumlah_pematang; i++) {
        cin >> daftar_pematang[i].u >> daftar_pematang[i].v >> daftar_pematang[i].id;
    }

    int limit_tampilan;
    cout << "\nBerapa banyak opsi maksimal yang ingin ditampilkan? (misal: 10, atau isi 1000 untuk melihat semua): ";
    cin >> limit_tampilan;

    vector<int> parent(jumlah_area + 1);
    for (int i = 0; i <= jumlah_area; i++) {
        parent[i] = i;
    }

    vector<int> lubang_awal;
    
    cari_spanning_trees(0, parent, lubang_awal, 0);

    cout << "\n=== HASIL ANALISIS ===\n";
    if (semua_solusi.empty()) {
        cout << "Tidak ditemukan satupun kombinasi pelubangan yang valid.\n";
    } else {
        cout << "Total kombinasi pelubangan yang valid : " << semua_solusi.size() << " kasus.\n\n";
        
        int tampilkan = min((int)semua_solusi.size(), limit_tampilan);
        cout << "Menampilkan " << tampilkan << " opsi (semuanya dipastikan tanpa siklus dan terkuras habis):\n";
        
        for (int i = 0; i < tampilkan; i++) {
            cout << "Opsi " << i + 1 << ": Lubangi pematang -> ";
            for (int id : semua_solusi[i]) {
                cout << id << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}