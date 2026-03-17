//TuGaS 1 Praktikum Algoritma Daffa_49

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
using namespace std;

struct Karyawan
{
    int id;
    char nama[67];
};

struct Barang
{
    char nama[67];
    long harga;
    int stok;
};

struct Karyawan karyawan[101];
struct Barang barang[101];

void pause()
{
    cout << "\n--------------------------------------------" << endl;
    system("pause");
}

int bdg(const char a[], const char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return a[i] - b[i];
        }
        i++;
    }
    return a[i] - b[i];
}

bool yatidak()
{
    char c;
    cout << "\nKembali ke menu sebelumnya? (Y/T) : ";
    cin >> c;
    
    if (c == 'y' || c == 'Y')
    {
        system("cls");
        return false; 
    }
    else if (c == 't' || c == 'T')
    {
        system("cls"); 
        return true;  
    }
    else
    {
        cout << "Opsi menu tidak tersedia. Silahkan input kembali pilihan yang tersedia." << endl;
        return yatidak();
    }
}

int hitungdatakrywn()
{
    int jumlah = 0;
    FILE *filekaryawan;
    filekaryawan = fopen("karyawan.txt", "r");
    
    if (filekaryawan == NULL) return 0;
    
    while (jumlah < 100 && fscanf(filekaryawan, " %d , %[^\n]", &karyawan[jumlah].id, karyawan[jumlah].nama) == 2)
    {
        jumlah++;
    }
    fclose(filekaryawan);
    return jumlah;
}

void simpandatakrywn(int n, const char* mode)
{
    FILE *filekaryawan;
    filekaryawan = fopen("karyawan.txt", mode);
    
    if (filekaryawan != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(filekaryawan, "%d,%s\n", karyawan[i].id, karyawan[i].nama);
        }
        fclose(filekaryawan);
    }
    else
    {
        cout << "Terdapat error saat buka data!" << endl;
    }
}

int hitungdatabrg()
{
    int jumlah = 0;
    FILE *filebarang;
    filebarang = fopen("barang.txt", "r");
    
    if (filebarang == NULL) return 0;
    
    while (jumlah < 100 && fscanf(filebarang, " %[^,] , %ld , %d", barang[jumlah].nama, &barang[jumlah].harga, &barang[jumlah].stok) == 3)
    {
        jumlah++;
    }
    fclose(filebarang);
    return jumlah;
}

void simpandatabrg(int n, const char* mode)
{
    FILE *filebarang;
    filebarang = fopen("barang.txt", mode);
    
    if (filebarang != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(filebarang, "%s,%ld,%d\n", barang[i].nama, barang[i].harga, barang[i].stok);
        }
        fclose(filebarang);
    }
    else
    {
        cout << "Terdapat error saat buka data!" << endl;
    }
}

void bubblesortbrgasc(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (barang[j].harga > barang[j + 1].harga)
            {
                struct Barang temp = barang[j];
                barang[j] = barang[j + 1];
                barang[j + 1] = temp;
            }
        }
    }
}

void quicksortbrgdesc(int kiri, int kanan)
{
    int i = kiri, j = kanan;
    long pivot = barang[(kiri + kanan) / 2].harga;
    
    do {
        while (barang[i].harga > pivot) i++; 
        while (barang[j].harga < pivot) j--; 
        
        if (i <= j) {
            struct Barang temp = barang[i];
            barang[i] = barang[j];
            barang[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    
    if (kiri < j) quicksortbrgdesc(kiri, j);
    if (i < kanan) quicksortbrgdesc(i, kanan);
}

void bubblesortnamabrg(int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (bdg(barang[j].nama, barang[j + 1].nama) > 0)
            {
                struct Barang temp = barang[j];
                barang[j] = barang[j + 1];
                barang[j + 1] = temp;
            }
        }
    }
}

void tampiltabelkrywn(int n)
{
    cout << "============================================" << endl;
    cout << left << "| " << setw(10) << "ID" << "| " << setw(27) << "NAMA KARYAWAN" << "|" << endl;
    cout << "============================================" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << left << "| " << setw(10) << karyawan[i].id 
             << "| " << setw(27) << karyawan[i].nama << "|" << endl;
    }
    cout << "============================================" << endl;
}

void tampiltabelbrg(int n)
{
    cout << "=================================================" << endl;
    cout << left << "| " << setw(20) << "NAMA BARANG" << "| " << setw(12) << "HARGA" << "| " << setw(9) << "STOK" << "|" << endl;
    cout << "=================================================" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << left << "| " << setw(20) << barang[i].nama 
             << "| " << setw(12) << barang[i].harga 
             << "| " << setw(9) << barang[i].stok << "|" << endl;
    }
    cout << "=================================================" << endl;
}

void tambahkrywn()
{
    int n = hitungdatakrywn(); 
    int jumlah;
    
    cout << endl;
    cout << "============================================" << endl;
    cout << "               TAMBAH KARYAWAN              " << endl;
    cout << "============================================" << endl;
    cout << "Masukan jumlah karyawan yang di input : ";
    cin >> jumlah;
    cin.ignore(1000, '\n');

    FILE *file = fopen("karyawan.txt", "a");
    if(file == NULL) return;

    for (int i = 0; i < jumlah; i++)
    {
        int tempid;
        char tempnama[50];
        
        cout << "--------------------------------------------" << endl;
        cout << "Data Karyawan ke-" << i + 1 << endl;
        cout << "ID Karyawan   : ";
        cin >> tempid;
        cin.ignore(1000, '\n');

        bool duplikat = false;
        for (int j = 0; j < n; j++) {
            if (karyawan[j].id == tempid) {
                duplikat = true;
                break;
            }
        }

        if (duplikat) {
            cout << "usaha GAGAL karena: ID Karyawan tersebut sudah terdaftar\n";
            i--; 
            continue; 
        }

        cout << "Nama Karyawan : ";
        cin.getline(tempnama, 50);

        fprintf(file, "%d,%s\n", tempid, tempnama);
        
        karyawan[n].id = tempid;
        n++;
    }
    fclose(file);
    cout << "--------------------------------------------" << endl;
    cout << "Data Berhasil Disimpan!" << endl;
}

void carikrywn()
{
    int n = hitungdatakrywn();
    int targetid;

    cout << endl;
    cout << "============================================" << endl;
    cout << "             CARI DATA KARYAWAN             " << endl;
    cout << "============================================" << endl;
    
    if (n == 0)
    {
        cout << "Tidak ada data karyawan yang bisa dicari." << endl;
        return;
    }

    cout << "Masukan ID Karyawan yang dicari : ";
    cin >> targetid;

    bool ketemu = false;
    for (int i = 0; i < n; i++)
    {
        if (karyawan[i].id == targetid)
        {
            cout << "--------------------------------------------" << endl;
            cout << "Data ditemukan!" << endl;
            cout << "ID   : " << karyawan[i].id << endl;
            cout << "Nama : " << karyawan[i].nama << endl;
            cout << "--------------------------------------------" << endl;
            ketemu = true;
            break;
        }
    }

    if (!ketemu) cout << "ID tidak dapat ditemukan." << endl;
}

void menuadmin()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "============================================" << endl;
        cout << "                 Halo Admin!                " << endl;
        cout << "============================================" << endl;
        cout << "1. Tambah data karyawan" << endl;
        cout << "2. Lihat data karyawan" << endl;
        cout << "3. Searching data karyawan" << endl;
        cout << "4. Logout" << endl;
        cout << "============================================" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            do { tambahkrywn(); } while (yatidak());
            break;
        case 2:
            do 
            { 
                cout << endl;
                cout << "============================================" << endl;
                cout << "               DATA KARYAWAN                " << endl;
                cout << "============================================" << endl;
                int n = hitungdatakrywn();
                if (n == 0) cout << "Tidak ada data." << endl;
                else tampiltabelkrywn(n);
            } while (yatidak());
            break;
        case 3:
            do { carikrywn(); } while (yatidak());
            break;
        case 4:
            cout << "Logout berhasil!" << endl;
            pause();
            break;
        default:
            cout << "Pilihan tidak tersedia mohon input pilihan ulang!" << endl;
            pause();
        }
    } while (pilihan != 4);
}

void loginadmin()
{
    char loginuser[50];
    char loginpassword[50];
    bool masuk = false;

    do
    {
        system("cls");
        cout << "============================================" << endl;
        cout << "                LOGIN ADMIN                 " << endl;
        cout << "============================================" << endl;
        cout << "Masukkan Username : ";
        cin >> loginuser;
        cout << "Masukkan Password : ";
        cin >> loginpassword;

        if (bdg(loginuser, "admin") == 0 && bdg(loginpassword, "123") == 0)
        {
            masuk = true;
            cout << "\nLogin Berhasil !" << endl;
            pause();
            menuadmin();
        }
        else
        {
            cout << "\nUsername atau Password SALAH, mohon input ulang!" << endl;
            pause();
        }
    } while (!masuk);
}

void tambahbrg()
{
    int n = hitungdatabrg();
    int jumlah;
    
    cout << endl;
    cout << "============================================" << endl;
    cout << "               TAMBAH BARANG                " << endl;
    cout << "============================================" << endl;
    cout << "Masukan Jumlah Barang : ";
    cin >> jumlah;
    cin.ignore(1000, '\n');

    FILE *file = fopen("barang.txt", "a");
    if (file == NULL) return;

    for (int i = 0; i < jumlah; i++)
    {
        char tempnama[50];
        long tempharga;
        int tempstok;
        
        cout << "--------------------------------------------" << endl;
        cout << "Data Barang ke-" << i + 1 << endl;
        cout << "Nama Barang  : ";
        cin.getline(tempnama, 50);

        bool duplikat = false;
        for (int j = 0; j < n; j++) {
            if (bdg(barang[j].nama, tempnama) == 0) {
                duplikat = true;
                break;
            }
        }

        if (duplikat) {
            cout << "usaha GAGAL karena: Barang dengan nama tersebut sudah ada!\n";
            i--; 
            continue; 
        }

        cout << "Harga Barang : ";
        cin >> tempharga;
        cout << "Stok Barang  : ";
        cin >> tempstok;
        cin.ignore(1000, '\n'); 

        fprintf(file, "%s,%ld,%d\n", tempnama, tempharga, tempstok);
        
        int c = 0;
        while(tempnama[c] != '\0') { barang[n].nama[c] = tempnama[c]; c++; }
        barang[n].nama[c] = '\0';
        n++;
    }
    fclose(file);
    cout << "--------------------------------------------" << endl;
    cout << "Data Berhasil Disimpan!" << endl;
}

void lihatbrg()
{
    int n = hitungdatabrg();
    int pilihansort;

    cout << endl;
    cout << "============================================" << endl;
    cout << "                LIHAT BARANG                " << endl;
    cout << "============================================" << endl;

    if (n == 0)
    {
        cout << "Tidak ada data yang bisa ditampilkan." << endl;
        return;
    }

    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Pilih sorting : ";
    cin >> pilihansort;
    cout << endl;

    if (pilihansort == 1)
    {
        bubblesortbrgasc(n);
    }
    else if (pilihansort == 2)
    {
        quicksortbrgdesc(0, n - 1);
    }
    else
    {
        cout << "Pilihan sorting tidak valid!" << endl;
    }

    tampiltabelbrg(n);
}

void editbrg()
{
    int n = hitungdatabrg();
    char carinama[50];

    cout << endl;
    cout << "============================================" << endl;
    cout << "                EDIT BARANG                 " << endl;
    cout << "============================================" << endl;

    if (n == 0)
    {
        cout << "Tidak ada data yang bisa diubah." << endl;
        return;
    }

    cout << "Masukan Nama Barang yang ingin diubah : ";
    cin.ignore(1000, '\n');
    cin.getline(carinama, 50);

    int indexedit = -1;
    for (int i = 0; i < n; i++)
    {
        if (bdg(barang[i].nama, carinama) == 0)
        {
            indexedit = i;
            break;
        }
    }

    if (indexedit != -1)
    {
        cout << "--------------------------------------------" << endl;
        cout << "Data Ditemukan!" << endl;
        cout << "Nama  : " << barang[indexedit].nama << endl;
        cout << "Harga : Rp " << barang[indexedit].harga << endl;
        cout << "Stok  : " << barang[indexedit].stok << " unit" << endl;
        cout << "--------------------------------------------" << endl;

        cout << "Masukan Data Baru" << endl;
        cout << "Nama Barang  : ";
        cin.getline(barang[indexedit].nama, 50);
        cout << "Harga Barang : ";
        cin >> barang[indexedit].harga;
        cout << "Stok Barang  : ";
        cin >> barang[indexedit].stok;

        simpandatabrg(n, "w");
        cout << "\nData berhasil diperbarui!" << endl;
    }
    else
    {
        cout << "\nData tidak ditemukan." << endl;
    }
}

void seqsearchbrg(const char* target)
{
    int n = hitungdatabrg();
    bool ketemu = false;
    for (int i = 0; i < n; i++)
    {
        if (bdg(barang[i].nama, target) == 0)
        {
            cout << endl;
            cout << "============================================" << endl;
            cout << "             Barang Ditemukan!              " << endl;
            cout << "============================================" << endl;
            cout << "Nama  : " << barang[i].nama << endl;
            cout << "Harga : Rp " << barang[i].harga << endl;
            cout << "Stok  : " << barang[i].stok << " unit" << endl;
            cout << "============================================" << endl;
            ketemu = true;
            break; 
        }
    }
    
    if (!ketemu) cout << endl << "Data Tidak ditemukan!" << endl;
}

void binsearchbrg(const char* target)
{
    int n = hitungdatabrg();
    bubblesortnamabrg(n);

    int awal = 0;
    int akhir = n - 1;
    bool ketemu = false;

    while (awal <= akhir)
    {
        int tengah = (awal + akhir) / 2;
        int res = bdg(target, barang[tengah].nama); 

        if (res == 0)
        {
            cout << endl;
            cout << "============================================" << endl;
            cout << "             Barang Ditemukan!              " << endl;
            cout << "============================================" << endl;
            cout << "Nama  : " << barang[tengah].nama << endl;
            cout << "Harga : Rp " << barang[tengah].harga << endl;
            cout << "Stok  : " << barang[tengah].stok << " unit" << endl;
            cout << "============================================" << endl;
            ketemu = true;
            break;
        }
        else if (res > 0)
        {
            awal = tengah + 1; 
        }
        else
        {
            akhir = tengah - 1; 
        }
    }

    if (!ketemu) cout << endl << "Data Tidak ditemukan!" << endl;
}

void caribrg()
{
    int n = hitungdatabrg();
    int metode;
    char target[50];

    cout << endl;
    cout << "============================================" << endl;
    cout << "                CARI BARANG                 " << endl;
    cout << "============================================" << endl;

    if (n == 0)
    {
        cout << "Tidak ada data yang bisa dicari." << endl;
        return;
    }

    cout << "1. Sequential Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "Pilih metode searching : ";
    cin >> metode;

    if (metode == 1 || metode == 2)
    {
        cout << "Masukan Nama Barang : ";
        cin.ignore(1000, '\n');
        cin.getline(target, 50);

        if (metode == 1) seqsearchbrg(target);
        else binsearchbrg(target);
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void menukaryawan()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "============================================" << endl;
        cout << "               Halo Karyawan!               " << endl;
        cout << "============================================" << endl;
        cout << "1. Tambah data barang" << endl;
        cout << "2. Lihat data barang" << endl;
        cout << "3. Edit data barang" << endl;
        cout << "4. Cari data barang" << endl;
        cout << "5. Logout" << endl;
        cout << "============================================" << endl;
        cout << "Pilih menu : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            do { tambahbrg(); } while (yatidak());
            break;
        case 2:
            do { lihatbrg(); } while (yatidak());
            break;
        case 3:
            do { editbrg(); } while (yatidak());
            break;
        case 4:
            do { caribrg(); } while (yatidak());
            break;
        case 5:
            cout << "Logout berhasil!" << endl;
            pause();
            break;
        default:
            cout << "Pilihan tidak tersedia mohon input pilihan ulang!" << endl;
            pause();
        }
    } while (pilihan != 5);
}

int main()
{
    int pilihmain;

    do
    {
        system("cls");
        cout << "============================================" << endl;
        cout << "          WELCOME TO COCOA HEAVEN           " << endl;
        cout << "============================================" << endl;
        cout << "1. Login Admin" << endl;
        cout << "2. Karyawan" << endl;
        cout << "3. Keluar" << endl;
        cout << "============================================" << endl;
        cout << "Masukkan pilihan menu : ";
        cin >> pilihmain;

        switch (pilihmain)
        {
        case 1:
            loginadmin();
            break;
        case 2:
            menukaryawan();
            break;
        case 3:
            cout << "\nSampai jumpa pengguna semoga harimu menyenangkan!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            pause();
        }
    } while (pilihmain != 3);

    return 0;
}
