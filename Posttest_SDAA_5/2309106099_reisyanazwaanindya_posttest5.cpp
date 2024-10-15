#include <iostream>
#include <string>

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

// Prosedur untuk menambahkan produk (stack)
void pushProduk(ProdukOptik*& stackKepala) {
    int id = 1;
    if (stackKepala != nullptr) {
        ProdukOptik* current = stackKepala;
        while (current->next != nullptr) {
            current = current->next;
            id++;  
        }
        id++;  
    }

    string nama, jenis;
    int stok;
    float harga;

    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan jenis produk (kacamata/lensa): ";
    getline(cin, jenis);

    do {
        cout << "Masukkan jumlah stok: ";
        cin >> stok;
    } while (stok < 0);

    do {
        cout << "Masukkan harga produk: ";
        cin >> harga;
    } while (harga < 0);

    ProdukOptik* produkBaru = buatProdukBaru(id, nama, jenis, stok, harga);
    
    // Menambahkan produk ke stack (di depan)
    produkBaru->next = stackKepala;
    stackKepala = produkBaru;

    cout << "Produk berhasil ditambahkan ke stack dengan ID: " << produkBaru->idProduk << "!\n";
}

// Prosedur untuk menghapus produk (stack pop)
void popProduk(ProdukOptik*& stackKepala) {
    if (stackKepala == nullptr) {
        cout << "Stack kosong. Tidak ada produk yang bisa dihapus.\n";
        return;
    }

    ProdukOptik* temp = stackKepala;
    stackKepala = stackKepala->next;
    cout << "Produk dengan ID " << temp->idProduk << " telah dihapus dari stack.\n";
    delete temp;
}

// Prosedur untuk menambahkan produk (queue enqueue)
void enqueueProduk(ProdukOptik*& queueKepala, ProdukOptik*& queueEkor) {
    int id = 1;
    if (queueKepala != nullptr) {
        ProdukOptik* current = queueKepala;
        while (current->next != nullptr) {
            current = current->next;
            id++;  
        }
        id++;  
    }

    string nama, jenis;
    int stok;
    float harga;

    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, nama);
    cout << "Masukkan jenis produk (kacamata/lensa): ";
    getline(cin, jenis);

    do {
        cout << "Masukkan jumlah stok: ";
        cin >> stok;
    } while (stok < 0);

    do {
        cout << "Masukkan harga produk: ";
        cin >> harga;
    } while (harga < 0);

    ProdukOptik* produkBaru = buatProdukBaru(id, nama, jenis, stok, harga);

    // Menambahkan produk ke queue (di belakang)
    if (queueKepala == nullptr) {
        queueKepala = produkBaru;
        queueEkor = produkBaru;
    } else {
        queueEkor->next = produkBaru;
        queueEkor = produkBaru;
    }

    cout << "Produk berhasil ditambahkan ke queue dengan ID: " << produkBaru->idProduk << "!\n";
}

// Prosedur untuk menghapus produk (queue dequeue)
void dequeueProduk(ProdukOptik*& queueKepala) {
    if (queueKepala == nullptr) {
        cout << "Queue kosong. Tidak ada produk yang bisa dihapus.\n";
        return;
    }

    ProdukOptik* temp = queueKepala;
    queueKepala = queueKepala->next;
    cout << "Produk dengan ID " << temp->idProduk << " telah dihapus dari queue.\n";
    delete temp;
}

// Fungsi untuk mengurutkan produk dengan Merge Sort
void merge(ProdukOptik* left, ProdukOptik* right, ProdukOptik*& result) {
    if (left == nullptr) {
        result = right;
        return;
    }
    if (right == nullptr) {
        result = left;
        return;
    }
    if (left->harga <= right->harga) {
        result = left;
        merge(left->next, right, result->next);
    } else {
        result = right;
        merge(left, right->next, result->next);
    }
}

void mergeSort(ProdukOptik*& head) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    ProdukOptik* middle = head;
    ProdukOptik* fast = head->next;

    // Temukan tengah
    while (fast != nullptr && fast->next != nullptr) {
        middle = middle->next;
        fast = fast->next->next;
    }

    ProdukOptik* left = head;
    ProdukOptik* right = middle->next;
    middle->next = nullptr;

    mergeSort(left);
    mergeSort(right);

    // Gabungkan dua sub-list
    merge(left, right, head);
}

// Fungsi untuk mengurutkan produk dengan Quick Sort
ProdukOptik* partition(ProdukOptik* low, ProdukOptik* high) {
    float pivot = high->harga;
    ProdukOptik* i = low; // Pointer untuk elemen yang lebih kecil

    for (ProdukOptik* j = low; j != high; j = j->next) {
        if (j->harga < pivot) {
            swap(i->harga, j->harga);
            swap(i->namaProduk, j->namaProduk);
            swap(i->jenisProduk, j->jenisProduk);
            swap(i->stok, j->stok);
            i = i->next; // Geser i ke depan
        }
    }
    swap(i->harga, high->harga); // Tukar harga i dan pivot
    swap(i->namaProduk, high->namaProduk);
    swap(i->jenisProduk, high->jenisProduk);
    swap(i->stok, high->stok);
    return i; // Kembalikan node pivot
}

void quickSort(ProdukOptik* low, ProdukOptik* high) {
    if (high != nullptr && low != high && low != high->next) {
        ProdukOptik* pivotNode = partition(low, high);
        quickSort(low, pivotNode);
        quickSort(pivotNode->next, high);
    }
}

// Fungsi untuk menampilkan produk
void tampilkanProduk(ProdukOptik* kepala) {
    ProdukOptik* current = kepala;
    cout << "=== Daftar Produk ===\n";
    while (current != nullptr) {
        cout << "ID: " << current->idProduk << ", Nama: " << current->namaProduk
             << ", Jenis: " << current->jenisProduk << ", Stok: " << current->stok
             << ", Harga: " << current->harga << endl;
        current = current->next;
    }
}

// Fungsi utama
int main() {
    ProdukOptik* stackKepala = nullptr;  // Stack linked list
    ProdukOptik* queueKepala = nullptr;  // Queue linked list
    ProdukOptik* queueEkor = nullptr;    // Queue tail
    int pilihan;

    do {
        cout << "\n=== Manajemen Produk (Stack & Queue) ===\n";
        cout << "1. Push Produk ke Stack\n";
        cout << "2. Pop Produk dari Stack\n";
        cout << "3. Enqueue Produk ke Queue\n";
        cout << "4. Dequeue Produk dari Queue\n";
        cout << "5. Tampilkan Produk (Ascending)\n";
        cout << "6. Urutkan Produk dengan Merge Sort (Ascending)\n";
        cout << "7. Urutkan Produk dengan Quick Sort (Descending)\n";
        cout << "8. Keluar\n";
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
                tampilkanProduk(queueKepala);
                break;
            case 6:
                mergeSort(queueKepala);
                cout << "Produk telah diurutkan dengan Merge Sort (Ascending).\n";
                break;
            case 7:
                // Cari akhir queue untuk pemanggilan Quick Sort
                if (queueKepala != nullptr) {
                    ProdukOptik* current = queueKepala;
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    quickSort(queueKepala, current); // Urutkan dengan Quick Sort
                    cout << "Produk telah diurutkan dengan Quick Sort (Descending).\n";
                }
                break;
            case 8:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    // Menghapus semua produk dalam stack untuk menghindari memory leak
    while (stackKepala != nullptr) {
        ProdukOptik* temp = stackKepala;
        stackKepala = stackKepala->next;
        delete temp;
    }

    // Menghapus semua produk dalam queue untuk menghindari memory leak
    while (queueKepala != nullptr) {
        ProdukOptik* temp = queueKepala;
        queueKepala = queueKepala->next;
        delete temp;
    }

    return 0;
}
