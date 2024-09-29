#include <iostream>
#include <string>

using namespace std;

// Struct untuk menyimpan data produk optik
struct ProdukOptik {
    int idProduk;                // ID produk
    string namaProduk;           // Nama produk
    string jenisProduk;          // Jenis produk
    int stok;                    // Jumlah stok
    float harga;                 // Harga produk
    ProdukOptik* next;           // Pointer ke produk berikutnya
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

// Prosedur untuk menambahkan produk
void tambahProduk(ProdukOptik*& kepala) {
    int id = 1;
    if (kepala != nullptr) {
        ProdukOptik* current = kepala;
        while (current->next != nullptr) {
            current = current->next;
            id++;  // Menentukan ID berdasarkan jumlah produk
        }
        id++;  // Increment untuk ID produk baru
    }
    
    cin.ignore();  // Bersihkan input buffer sebelum getline
    string nama, jenis;
    int stok;
    float harga;

    cout << "Masukkan nama produk: ";
    getline(cin, nama);
    cout << "Masukkan jenis produk (kacamata/lensa): ";
    getline(cin, jenis);

    // Validasi stok
    do {
        cout << "Masukkan jumlah stok: ";
        cin >> stok;
    } while (stok < 0); // Stok tidak boleh negatif

    // Validasi harga
    do {
        cout << "Masukkan harga produk: ";
        cin >> harga;
    } while (harga < 0); // Harga tidak boleh negatif

    ProdukOptik* produkBaru = buatProdukBaru(id, nama, jenis, stok, harga);

    // Menambahkan produk ke dalam linked list
    if (kepala == nullptr) {
        kepala = produkBaru;  // Jika list kosong, produk baru menjadi kepala
    } else {
        ProdukOptik* current = kepala;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = produkBaru;  // Menambahkan produk baru di akhir list
    }

    cout << "Produk berhasil ditambahkan dengan ID: " << produkBaru->idProduk << "!\n";
}

// Prosedur untuk menampilkan semua produk dalam format tabel
void tampilkanProduk(ProdukOptik* kepala) {
    if (kepala == nullptr) {
        cout << "Belum ada produk yang ditambahkan.\n";
        return;
    }

    // Tampilkan header tabel
    cout << "\n============================== Store Optik Mata ==============================\n";
    cout << "+---------------------------------------------------------------------------------+\n";
    cout << "| ID  |        Nama Produk        |    Jenis Produk    |   Stok   |   Harga       |\n";
    cout << "+---------------------------------------------------------------------------------+\n";
    
    // Menampilkan isi dari produk dalam bentuk tabel
    ProdukOptik* current = kepala;
    while (current != nullptr) {
        printf("| %-3d | %-24s | %-18s | %-8d | Rp%-11.2f |\n", 
               current->idProduk, current->namaProduk.c_str(), 
               current->jenisProduk.c_str(), 
               current->stok, 
               current->harga);
        current = current->next;
    }
    
    cout << "+---------------------------------------------------------------------------------+\n";
}

// Fungsi untuk mencari produk berdasarkan ID
ProdukOptik* cariProduk(ProdukOptik* kepala, int id) {
    ProdukOptik* current = kepala;
    while (current != nullptr) {
        if (current->idProduk == id) {
            return current;  // Mengembalikan pointer ke produk
        }
        current = current->next;
    }
    return nullptr;  // Produk tidak ditemukan
}

// Prosedur untuk mengupdate stok dan harga produk berdasarkan ID
void updateProduk(ProdukOptik* kepala) {
    int id;
    cout << "Masukkan ID produk yang ingin diupdate: ";
    cin >> id;
    ProdukOptik* produk = cariProduk(kepala, id);
    if (produk != nullptr) {
        // Validasi stok baru
        do {
            cout << "Masukkan stok baru: ";
            cin >> produk->stok;
        } while (produk->stok < 0); // Stok tidak boleh negatif

        // Validasi harga baru
        do {
            cout << "Masukkan harga baru: ";
            cin >> produk->harga;
        } while (produk->harga < 0); // Harga tidak boleh negatif

        cout << "Produk berhasil diperbarui!\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus produk berdasarkan ID
void hapusProduk(ProdukOptik*& kepala) {
    int id;
    cout << "Masukkan ID produk yang ingin dihapus: ";
    cin >> id;

    if (kepala == nullptr) {
        cout << "Belum ada produk yang dapat dihapus.\n";
        return;
    }

    if (kepala->idProduk == id) {
        // Hapus produk di kepala
        ProdukOptik* temp = kepala;
        kepala = kepala->next;
        delete temp;  // Menghapus node
        cout << "Produk berhasil dihapus!\n";
        return;
    }

    ProdukOptik* current = kepala;
    while (current->next != nullptr && current->next->idProduk != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Produk tidak ditemukan.\n";
    } else {
        ProdukOptik* temp = current->next;
        current->next = current->next->next;  // Menghapus node dari linked list
        delete temp;  // Menghapus node
        cout << "Produk berhasil dihapus!\n";
    }
}

// Fungsi utama
int main() {
    ProdukOptik* kepala = nullptr;  // Inisialisasi kepala linked list
    int pilihan;
    
    // Header besar untuk Store Optik Mata
    cout << "========================================================================================\n";
    cout << "||                                                                                    ||\n";
    cout << "||                           WELCOME TO STORE OPTIK MATA                              ||\n";
    cout << "||                      Menyediakan Beragam Kacamata dan Lensa Berkualitas            ||\n";
    cout << "||                                                                                    ||\n";
    cout << "========================================================================================\n";
    
    do {
        cout << "\n=== Manajemen Store Optik Mata ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Update Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProduk(kepala);
                break;
            case 2:
                tampilkanProduk(kepala);
                break;
            case 3:
                updateProduk(kepala);
                break;
            case 4:
                hapusProduk(kepala);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    // Menghapus semua produk untuk menghindari memory leak
    while (kepala != nullptr) {
        ProdukOptik* temp = kepala;
        kepala = kepala->next;
        delete temp;
    }

    return 0;
}
