#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Struct untuk menyimpan data produk optik
struct ProdukOptik {
    int idProduk;
    string namaProduk;
    string jenisProduk;
    int stok;
    float harga;
    ProdukOptik* next;
};

// Fungsi untuk membuat node baru
ProdukOptik* buatProdukBaru(int id, const string& nama, const string& jenis, int stok, float harga) {
    ProdukOptik* produkBaru = new ProdukOptik;
    produkBaru->idProduk = id;
    produkBaru->namaProduk = nama;
    produkBaru->jenisProduk = jenis;
    produkBaru->stok = stok;
    produkBaru->harga = harga;
    produkBaru->next = nullptr;
    return produkBaru;
}

// Fungsi untuk menambahkan produk ke stack
void pushProduk(ProdukOptik*& kepala) {
    int id, stok;
    float harga;
    string nama, jenis;

    cout << "Masukkan ID Produk: ";
    cin >> id;
    cout << "Masukkan Nama Produk: ";
    cin.ignore(); // Clear newline from input buffer
    getline(cin, nama);
    cout << "Masukkan Jenis Produk: ";
    getline(cin, jenis);
    cout << "Masukkan Stok Produk: ";
    cin >> stok;
    cout << "Masukkan Harga Produk: ";
    cin >> harga;

    ProdukOptik* produkBaru = buatProdukBaru(id, nama, jenis, stok, harga);
    produkBaru->next = kepala; // Menyambungkan ke head sebelumnya
    kepala = produkBaru; // Menjadi head baru
}

// Fungsi untuk mengeluarkan produk dari stack
void popProduk(ProdukOptik*& kepala) {
    if (kepala == nullptr) {
        cout << "Stack kosong, tidak ada produk untuk dihapus.\n";
        return;
    }
    ProdukOptik* produkHapus = kepala;
    kepala = kepala->next; // Pindah ke node berikutnya
    delete produkHapus; // Hapus node
    cout << "Produk berhasil dihapus dari stack.\n";
}

// Fungsi untuk menambahkan produk ke queue
void enqueueProduk(ProdukOptik*& kepala, ProdukOptik*& ekor) {
    int id, stok;
    float harga;
    string nama, jenis;

    cout << "Masukkan ID Produk: ";
    cin >> id;
    cout << "Masukkan Nama Produk: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan Jenis Produk: ";
    getline(cin, jenis);
    cout << "Masukkan Stok Produk: ";
    cin >> stok;
    cout << "Masukkan Harga Produk: ";
    cin >> harga;

    ProdukOptik* produkBaru = buatProdukBaru(id, nama, jenis, stok, harga);
    if (ekor == nullptr) {
        kepala = ekor = produkBaru; // Jika queue kosong
    } else {
        ekor->next = produkBaru; // Menambahkan di akhir
        ekor = produkBaru; // Update ekor
    }
    cout << "Produk berhasil ditambahkan ke queue.\n";
}

// Fungsi untuk mengeluarkan produk dari queue
void dequeueProduk(ProdukOptik*& kepala) {
    if (kepala == nullptr) {
        cout << "Queue kosong, tidak ada produk untuk dihapus.\n";
        return;
    }
    ProdukOptik* produkHapus = kepala;
    kepala = kepala->next; // Pindah ke node berikutnya
    delete produkHapus; // Hapus node
    cout << "Produk berhasil dihapus dari queue.\n";
}

// Fungsi untuk menampilkan produk dari stack dan queue
void tampilkanProduk(ProdukOptik* stackKepala, ProdukOptik* queueKepala) {
    ProdukOptik* current;

    cout << "=== Daftar Produk dari Stack ===\n";
    current = stackKepala;
    while (current != nullptr) {
        cout << "ID: " << current->idProduk << ", Nama: " << current->namaProduk
             << ", Jenis: " << current->jenisProduk << ", Stok: " << current->stok
             << ", Harga: " << current->harga << endl;
        current = current->next;
    }

    cout << "=== Daftar Produk dari Queue ===\n";
    current = queueKepala;
    while (current != nullptr) {
        cout << "ID: " << current->idProduk << ", Nama: " << current->namaProduk
             << ", Jenis: " << current->jenisProduk << ", Stok: " << current->stok
             << ", Harga: " << current->harga << endl;
        current = current->next;
    }
}

// Fungsi untuk melakukan Fibonacci Search
int fibonacciSearch(vector<int>& arr, int x) {
    int n = arr.size();
    int fib2 = 0;
    int fib1 = 1;
    int fibM = fib2 + fib1;

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fib2, n - 1);
        if (arr[i] < x) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}

// Fungsi untuk melakukan Jump Search
int jumpSearch(vector<int>& arr, int x) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }

    if (arr[prev] == x) {
        return prev;
    }

    return -1;
}

// Fungsi untuk melakukan Boyer-Moore Search
vector<int> boyerMooreSearch(const string& text, const string& pattern) {
    int m = pattern.length();
    int n = text.length();
    vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }

    vector<int> hasil;
    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            hasil.push_back(s);
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }
    return hasil;
}

// Fungsi untuk mengonversi data linked list ke dalam vektor
vector<int> konversiKeVektor(ProdukOptik* kepala) {
    vector<int> vektor;
    ProdukOptik* current = kepala;
    while (current != nullptr) {
        vektor.push_back(current->stok);
        current = current->next;
    }
    return vektor;
}

// Fungsi untuk menampilkan hasil pencarian string
void tampilkanHasilPencarianString(const vector<int>& hasil, const string& pattern) {
    if (hasil.empty()) {
        cout << "Tidak ditemukan produk dengan nama yang mengandung: " << pattern << endl;
    } else {
        cout << "Ditemukan produk pada posisi: ";
        for (int posisi : hasil) {
            cout << posisi << " ";
        }
        cout << endl;
    }
}

// Fungsi utama
int main() {
    ProdukOptik* stackKepala = nullptr;
    ProdukOptik* queueKepala = nullptr;
    ProdukOptik* queueEkor = nullptr;
    int pilihan;

    do {
        cout << "\n=== Manajemen Produk (Stack & Queue) ===\n";
        cout << "1. Push Produk ke Stack\n";
        cout << "2. Pop Produk dari Stack\n";
        cout << "3. Enqueue Produk ke Queue\n";
        cout << "4. Dequeue Produk dari Queue\n";
        cout << "5. Tampilkan Produk\n";
        cout << "6. Cari Produk dengan Fibonacci Search (Stok)\n";
        cout << "7. Cari Produk dengan Jump Search (Stok)\n";
        cout << "8. Cari Produk dengan Boyer-Moore Search (Nama)\n";
        cout << "9. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                pushProduk(stackKepala);
                break;
            case 2:
                popProduk(stackKepala);
                break;
            case 3:
                enqueueProduk(queueKepala, queueEkor);
                break;
            case 4:
                dequeueProduk(queueKepala);
                break;
            case 5:
                tampilkanProduk(stackKepala, queueKepala);
                break;
            case 6: {
                int stok;
                cout << "Masukkan stok yang dicari: ";
                cin >> stok;
                vector<int> vektor = konversiKeVektor(stackKepala);
                int index = fibonacciSearch(vektor, stok);
                if (index != -1) {
                    cout << "Produk ditemukan pada index: " << index << endl;
                } else {
                    cout << "Produk tidak ditemukan.\n";
                }
                break;
            }
            case 7: {
                int stok;
                cout << "Masukkan stok yang dicari: ";
                cin >> stok;
                vector<int> vektor = konversiKeVektor(stackKepala);
                int index = jumpSearch(vektor, stok);
                if (index != -1) {
                    cout << "Produk ditemukan pada index: " << index << endl;
                } else {
                    cout << "Produk tidak ditemukan.\n";
                }
                break;
            }
            case 8: {
                string pola;
                cout << "Masukkan nama produk yang dicari: ";
                cin.ignore();
                cout << "Masukkan teks untuk pencarian: ";
                string teks;
                getline(cin, teks);
                vector<int> hasil = boyerMooreSearch(teks, pola);
                tampilkanHasilPencarianString(hasil, pola);
                break;
            }
            case 9:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 9);

    return 0;
}
