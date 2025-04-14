#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <iomanip.h>
#include <fstream.h>
#define MAX_TUGAS 100

struct Tugas {
    char nama[100];
    char deadline[100];
    bool selesai;
};

Tugas daftarTugas[MAX_TUGAS];
int jumlahTugas = 0;

void simpanFile() {
    ofstream file("simpan.txt", ios::trunc);
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan!" << endl;
        return;
    }
    for (int i = 0; i < jumlahTugas; i++) {
        file << daftarTugas[i].nama << ","
             << daftarTugas[i].deadline << ","
             << daftarTugas[i].selesai << endl;
    }
    file.close();
    cout << "Data berhasil disimpan!" << endl;
}

void loadDariFile() {
    ifstream file("simpan.txt");
    if (!file) {
        // Tidak ada file, anggap saja belum ada data
        return;
    }

    jumlahTugas = 0;
    while (file.getline(daftarTugas[jumlahTugas].nama, 100, ',')) {
        file.getline(daftarTugas[jumlahTugas].deadline, 100, ',');
        int status;
        file >> status;
        file.ignore(); // Untuk newline
        daftarTugas[jumlahTugas].selesai = status;
        jumlahTugas++;
    }
    file.close();
}

void tampilkanTugas() {
    if (jumlahTugas == 0) {
        cout << "Tidak Ada Tugas" << endl;
        return;
    }
    cout << "============================== DAFTAR TUGAS ==================================\n";
     for (int i = 0; i < jumlahTugas; i++) {
        cout << setiosflags(ios::left);
        cout << "| " << i + 1 << ". | Nama: " << setw(13) << daftarTugas[i].nama
             << " | Deadline: " << setw(7) << daftarTugas[i].deadline
             << " | Status: " << setw(15)<< (daftarTugas[i].selesai ? "Selesai" : "Belum Selesai") << endl;
    }
}

void tambahTugas() {
    if (jumlahTugas >= MAX_TUGAS) {
        cout << "Tugas Anda Penuh. Segera Kerjakan!" << endl;
        return;
    }

    Tugas tugasBaru;
    cin.ignore();
    cout << "Masukkan nama tugas: ";
    cin.getline(tugasBaru.nama, 100);
    cout << "Masukkan deadline (DD/MM/YYYY): ";
    cin.getline(tugasBaru.deadline, 100);
    tugasBaru.selesai = false;

    daftarTugas[jumlahTugas] = tugasBaru;
    jumlahTugas++;

    simpanFile();
    cout << "Tugas berhasil ditambahkan!" << endl;
}

void tandaiSelesai() {
    tampilkanTugas();
    int nomor;
    cout << "Masukkan nomor tugas yang selesai: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jumlahTugas) {
        daftarTugas[nomor - 1].selesai = true;
        simpanFile();
        cout << "Tugas berhasil ditandai selesai!" << endl;
    } else {
        cout << "Nomor tugas tidak valid!" << endl;
    }
}

void hapusTugas() {
    tampilkanTugas();
    int nomor;
    cout << "Masukkan nomor tugas yang ingin dihapus: ";
    cin >> nomor;
    if (nomor > 0 && nomor <= jumlahTugas) {
        for (int i = nomor - 1; i < jumlahTugas - 1; i++) {
            daftarTugas[i] = daftarTugas[i + 1];
        }
        jumlahTugas--;
        simpanFile();
        cout << "Tugas berhasil dihapus!" << endl;
    } else {
        cout << "Nomor tugas tidak valid!" << endl;
    }
}

void tampilkanFileLangsung() {
    ifstream file("simpan.txt");
    if (!file) {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    string line;
    cout << "============================== DAFTAR TUGAS ==================================\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void hapusFile() {
    if (remove("simpan.txt") == 0) {
        jumlahTugas = 0;
        cout << "File berhasil dihapus." << endl;
    } else {
        cout << "Gagal menghapus file!" << endl;
    }
}

void editTugas() {
    loadDariFile();
    tampilkanTugas();

    int nomor;
    cout << "Masukkan nomor tugas yang ingin diedit: ";
    cin >> nomor;
    cin.ignore();
    if (nomor > 0 && nomor <= jumlahTugas) {
        char input[100];

        cout << "Edit nama tugas (kosongkan untuk tetap): ";
        cin.getline(input, 100);
        if (strlen(input) > 0) {
            strcpy(daftarTugas[nomor - 1].nama, input);
        }

        cout << "Edit deadline tugas (kosongkan untuk tetap): ";
        cin.getline(input, 100);
        if (strlen(input) > 0) {
            strcpy(daftarTugas[nomor - 1].deadline, input);
        }

        char selesai;
        cout << "Tandai selesai? (y/n): ";
        cin >> selesai;
        if (selesai == 'y' || selesai == 'Y') {
            daftarTugas[nomor - 1].selesai = true;
        } else if (selesai == 'n' || selesai == 'N') {
            daftarTugas[nomor - 1].selesai = false;
        }

        simpanFile();
        cout << "Tugas berhasil diedit!" << endl;
    } else {
        cout << "Nomor tugas tidak valid!" << endl;
    }
}

int main() {
    int pilihan;
    loadDariFile(); // Muat data di awal

    do {
        cout << "\n============================== DAFTAR TUGAS ==================================\n";
        cout << "1. Tambah Daftar Tugas\n";
        cout << "2. Lihat Daftar Tugas\n";
        cout << "3. Tandai Tugas Selesai\n";
        cout << "4. Hapus Daftar Tugas\n";
        cout << "5. Lihat Isi File\n";
        cout << "6. Hapus File\n";
        cout << "7. Edit Tugas\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: clrscr(); tambahTugas(); break;
            case 2: clrscr(); tampilkanTugas(); break;
            case 3: clrscr(); tandaiSelesai(); break;
            case 4: clrscr(); hapusTugas(); break;
            case 5: clrscr(); tampilkanFileLangsung(); break;
            case 6: clrscr(); hapusFile(); break;
            case 7: clrscr(); editTugas(); break;
            case 8: cout << "Keluar dari aplikasi. Sampai jumpa!\n"; break;
            default: cout << "Pilihan tidak valid!\n"; break;
        }
    } while (pilihan != 8);

    return 0;
}


