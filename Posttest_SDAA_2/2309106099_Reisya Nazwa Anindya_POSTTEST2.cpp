#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan data produk optik
struct ProdukOptik {
    int idProduk;          // ID produk
    string namaProduk;
    string jenisProduk;
    int stok;
    float harga;
};

// Prosedur untuk menambahkan produk
void tambahProduk(ProdukOptik* daftarProduk, int& jumlahProduk) {
    cin.ignore();  // Bersihkan input buffer sebelum getline
    daftarProduk[jumlahProduk].idProduk = jumlahProduk + 1;  // ID otomatis berdasarkan jumlah produk
    cout << "Masukkan nama produk: ";
    getline(cin, daftarProduk[jumlahProduk].namaProduk);
    cout << "Masukkan jenis produk (kacamata/lensa): ";
    getline(cin, daftarProduk[jumlahProduk].jenisProduk);
    cout << "Masukkan jumlah stok: ";
    cin >> daftarProduk[jumlahProduk].stok;
    cout << "Masukkan harga produk: ";
    cin >> daftarProduk[jumlahProduk].harga;
    jumlahProduk++;
    cout << "Produk berhasil ditambahkan dengan ID: " << daftarProduk[jumlahProduk-1].idProduk << "!\n";
}

// Prosedur untuk menampilkan semua produk dalam format tabel
void tampilkanProduk(const ProdukOptik* daftarProduk, int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << "Belum ada produk yang ditambahkan.\n";
        return;
    }

    // Tampilkan header tabel
    cout << "\n============================== Store Optik Mata ==============================\n";
    cout << "+---------------------------------------------------------------------------------+\n";
    cout << "| ID  |        Nama Produk        |    Jenis Produk    |   Stok   |   Harga       |\n";
    cout << "+---------------------------------------------------------------------------------+\n";
    
    // Menampilkan isi dari produk dalam bentuk tabel
    for (int i = 0; i < jumlahProduk; i++) {
        printf("| %-3d | %-24s | %-18s | %-8d | Rp%-11.2f |\n", 
               daftarProduk[i].idProduk, daftarProduk[i].namaProduk.c_str(), 
               daftarProduk[i].jenisProduk.c_str(), 
               daftarProduk[i].stok, 
               daftarProduk[i].harga);
    }
    
    cout << "+---------------------------------------------------------------------------------+\n";
}

// Fungsi untuk mencari produk berdasarkan ID
int cariProduk(const ProdukOptik* daftarProduk, int jumlahProduk, int id) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].idProduk == id) {
            return i;  // Mengembalikan indeks produk
        }
    }
    return -1;  // Produk tidak ditemukan
}

// Prosedur untuk mengupdate stok dan harga produk berdasarkan ID
void updateProduk(ProdukOptik* daftarProduk, int jumlahProduk) {
    int id;
    cout << "Masukkan ID produk yang ingin diupdate: ";
    cin >> id;
    int indeks = cariProduk(daftarProduk, jumlahProduk, id);
    if (indeks != -1) {
        cout << "Masukkan stok baru: ";
        cin >> daftarProduk[indeks].stok;
        cout << "Masukkan harga baru: ";
        cin >> daftarProduk[indeks].harga;
        cout << "Produk berhasil diperbarui!\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus produk berdasarkan ID
void hapusProduk(ProdukOptik* daftarProduk, int& jumlahProduk) {
    int id;
    cout << "Masukkan ID produk yang ingin dihapus: ";
    cin >> id;
    int indeks = cariProduk(daftarProduk, jumlahProduk, id);
    if (indeks != -1) {
        for (int i = indeks; i < jumlahProduk - 1; i++) {
            daftarProduk[i] = daftarProduk[i + 1];  // Menggeser elemen
        }
        jumlahProduk--;
        cout << "Produk berhasil dihapus!\n";
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

// Fungsi utama
int main() {
    const int kapasitasMaks = 100;
    ProdukOptik daftarProduk[kapasitasMaks];
    int jumlahProduk = 0;
    int pilihan;
    
    // Header besar untuk Store Optik Mata
    cout << "========================================================================================\n";
    cout << "||                                                                                    ||\n";
    cout << "||                           WELCOME TO STORE OPTIK MATA                              ||\n";
    cout << "||                      Menyediakan Beragam Kacamata dan Lensa Berkualitas            ||\n";
    cout << "||                                                                                    ||\n";
    cout << "========================================================================================\n";
    
    do {
        cout << "\n=== Manajemen Stor Optik Mata ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Update Produk\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahProduk(daftarProduk, jumlahProduk);
                break;
            case 2:
                tampilkanProduk(daftarProduk, jumlahProduk);
                break;
            case 3:
                updateProduk(daftarProduk, jumlahProduk);
                break;
            case 4:
                hapusProduk(daftarProduk, jumlahProduk);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
