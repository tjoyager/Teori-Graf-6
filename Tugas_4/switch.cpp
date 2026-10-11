#include <iostream>
using namespace std;

int main() {
    bool a, b, c, d, e, f, g, h, k;
    
    cout << "=== Program Validasi Switching Network ===" << endl;
    cout << "Masukkan status saklar (1 untuk ON, 0 untuk OFF)" << endl;
    
    cout << "Input saklar a: "; cin >> a;
    cout << "Input saklar b: "; cin >> b;
    cout << "Input saklar c: "; cin >> c;
    cout << "Input saklar d: "; cin >> d;
    cout << "Input saklar e: "; cin >> e;
    cout << "Input saklar f: "; cin >> f;
    cout << "Input saklar g: "; cin >> g;
    cout << "Input saklar h: "; cin >> h;
    cout << "Input saklar k: "; cin >> k;
    
    bool L = k && ( 
                (h && ( (a && b && f) || (e && (f || (b && c) || a)) )) || 
                (g && ( (a && (b || (e && f))) || c )) || 
                d 
             );
             
    cout << "\n--- HASIL EVALUASI ---" << endl;
    if (L) {
        cout << "Status: LAMPU MENYALA (ON)" << endl;
    } else {
        cout << "Status: LAMPU MATI (OFF)" << endl;
    }
    
    return 0;
}
