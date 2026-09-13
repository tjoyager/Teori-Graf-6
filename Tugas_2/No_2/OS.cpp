#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node {
    string name;
    bool isFolder;
    Node* parent;
    vector<Node*> children;
    
    Node(string n, bool folder, Node* p = nullptr) {
        name = n;
        isFolder = folder;
        parent = p;
    }
};

int main() {
    Node* root = new Node("/", true);
    
    Node* folderDokumen = new Node("dokumen", true, root);
    Node* folderSistem = new Node("sistem", true, root);
    
    Node* fileLaporan = new Node("laporan.pdf", false, folderDokumen);
    Node* fileCatatan = new Node("catatan.txt", false, folderDokumen);
    Node* fileSyslog = new Node("syslog.log", false, folderSistem);
    
    root->children.push_back(folderDokumen);
    root->children.push_back(folderSistem);
    
    folderDokumen->children.push_back(fileLaporan);
    folderDokumen->children.push_back(fileCatatan);
    
    folderSistem->children.push_back(fileSyslog);
    
    Node* current = root;
    string command, arg;
    
    while (true) {
        cout << "Path saat ini [" << current->name << "] $ ";
        cin >> command;
        
        if (command == "exit") {
            break;
        } 
        else if (command == "ls") {
            for (Node* child : current->children) {
                cout << (child->isFolder ? "[DIR]  " : "[FILE] ") << child->name << endl;
            }
        } 
        else if (command == "cd") {
            cin >> arg;
            
            if (arg == "..") {
                if (current->parent != nullptr) {
                    current = current->parent;
                } else {
                    cout << "Sudah berada di root!" << endl;
                }
            } 
            else {
                bool found = false;
                for (Node* child : current->children) {
                    if (child->name == arg) {
                        if (child->isFolder) {
                            current = child;
                            found = true;
                        } else {
                            cout << "Bukan sebuah direktori!" << endl;
                            found = true;
                        }
                        break;
                    }
                }
                if (!found) {
                    cout << "Direktori tidak ditemukan!" << endl;
                }
            }
        } 
        else {
            cout << "Perintah tidak dikenal. Gunakan: ls, cd <nama>, cd .., exit" << endl;
        }
    }
    
    return 0;
}
