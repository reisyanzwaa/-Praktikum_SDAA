#include <iostream>
using namespace std;

// Fungsi rekursif untuk menyelesaikan Menara Hanoi
void menaraHanoiRekursif(int jumlahBola, char tiangAsal, char tiangTujuan, char tiangSementara) {
    if (jumlahBola == 1) {
        std::cout << "Pindahkan bola 1 dari " << tiangAsal << " ke " << tiangTujuan << std::endl;
        return;
    }

    menaraHanoiRekursif(jumlahBola - 1, tiangAsal, tiangSementara, tiangTujuan);
    std::cout << "Pindahkan bola " << jumlahBola << " dari " << tiangAsal << " ke " << tiangTujuan << std::endl;
    menaraHanoiRekursif(jumlahBola - 1, tiangSementara, tiangTujuan, tiangAsal);
}

int main() {
    int jumlahBola = 3; // Jumlah bola
    char tiangAsal = 'A'; // Tiang asal
    char tiangTujuan = 'C'; // Tiang tujuan
    char tiangSementara = 'B'; // Tiang sementara

    std::cout << "Menyelesaikan Menara Hanoi dengan " << jumlahBola << " bola:" << std::endl;
    std::cout << "Tiang asal: " << tiangAsal << std::endl;
    std::cout << "Tiang tujuan: " << tiangTujuan << std::endl;
    std::cout << "Tiang sementara: " << tiangSementara << std::endl;
    menaraHanoiRekursif(jumlahBola, tiangAsal, tiangTujuan, tiangSementara);

    std::cout << "\nHasil akhir:" << std::endl;
    std::cout << "Tiang asal: " << tiangAsal << " (tidak ada bola)" << std::endl;
    std::cout << "Tiang tujuan: " << tiangTujuan << " (bola 1, 2, 3)" << std::endl;
    std::cout << "Tiang sementara: " << tiangSementara << " (tidak ada bola)" << std::endl;

    return 0;
}