#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Archivo {
    string name;
};

struct Directorio {
    string name;
    vector<Archivo> archivos;
    vector<Directorio> subdirectorios;
};

bool findfile(Directorio& dir, string& path, const string& target) {
    for (auto& arch : dir.archivos) {
        if (arch.name == target) {
            path = "/" + dir.name + path;
            return true;
        }
    }
    for (auto& subdir : dir.subdirectorios) {
        string subdirpath = path + "/" + subdir.name;
        if (findfile(subdir, subdirpath, target)) {
            path = "/" + dir.name + subdirpath;
            return true;
        }
    }
    return false;
}

int main() {
    Directorio sistemaDeArchivos = {
        "root",
        {
            {"archivo1.txt"},
            {"archivo2.txt"}
        },
        {
            {
                "subdir1",
                {
                    {"archivo3.txt"}
                },
                {
                    {
                        "subdir2",
                        {
                            {"target.txt"},
                            {"archivo4.txt"}
                        },
                        {}
                    }
                }
            },
            {"archivo5.txt"}
        }
    };

    string target = "archivo3.txt";
    string path = "";
    if (findfile(sistemaDeArchivos, path, target)) {
        cout << "Archivo encontrado en " << path << "/" << target << endl;
    } else {
        cout << "Archivo no encontrado" << endl;
    }

    return 0;
}