// ===============================================
// FILE: structures.h
// DESKRIPSI: Definisi struktur data (Model Data)
// ===============================================

#ifndef STRUCTURES_H
#define STRUCTURES_H

// Struktur untuk menyimpan ukuran layar terminal
typedef struct {
    int width;  // Lebar terminal
    int height; // Tinggi terminal
} TerminalSize;

// 1. DATA DOSEN
typedef struct {
    char nidn[20];         // Nomor Induk Dosen Nasional
    char nama[50];         // Nama Lengkap Dosen
    char email[50];        // Email Dosen
    char createdBy[50];    // Dibuat oleh siapa
    char createdDate[20];  // Tanggal dibuat
    char modifiedBy[50];   // Diedit oleh siapa
    char modifiedDate[20]; // Tanggal edit terakhir
} Dosen;

// 2. DATA MAHASISWA
typedef struct {
    char nim[20];          // Nomor Induk Mahasiswa
    char nama[50];         // Nama Mahasiswa
    char prodi[30];        // Program Studi
    char createdBy[50];    // Log pembuat data
    char createdDate[20];  // Log tanggal buat
    char modifiedBy[50];   // Log pengedit data
    char modifiedDate[20]; // Log tanggal edit
} Mahasiswa;

// 3. DATA MATA KULIAH
typedef struct {
    char kode[20];         // Kode Mata Kuliah
    char nama[50];         // Nama Mata Kuliah
    int sks;               // Jumlah SKS
    int semester;          // Semester berapa
    char createdBy[50];    // Log pembuat
    char createdDate[20];  // Log tanggal
    char modifiedBy[50];   // Log pengedit
    char modifiedDate[20]; // Log tanggal edit
} MataKuliah;

// 4. DATA PRODI (Program Studi)
typedef struct {
    char id[20];           // ID Prodi
    char nama[50];         // Nama Prodi
    char fakultas[50];     // Nama Fakultas
    char createdBy[50];    // Log pembuat
    char createdDate[20];  // Log tanggal
    char modifiedBy[50];   // Log pengedit
    char modifiedDate[20]; // Log tanggal edit
} Prodi;

// 5. DATA KELAS
typedef struct {
    char id[20];           // ID Kelas
    char nama[50];         // Nama Kelas (misal: TI-A)
    char ruang[20];        // Ruangan
    char createdBy[50];    // Log pembuat
    char createdDate[20];  // Log tanggal
    char modifiedBy[50];   // Log pengedit
    char modifiedDate[20]; // Log tanggal edit
} Kelas;

// 6. DATA MODUL AJAR (Materi Kuliah)
typedef struct {
    char id_modul[20];     // ID Modul
    char judul[100];       // Judul Materi
    char tipe[10];         // Tipe file (PDF/PPT)
    char kode_matkul[20];  // Relasi ke Mata Kuliah
    char id_prodi[20];     // Relasi ke Prodi
    char id_kelas[20];     // Relasi ke Kelas
    char createdBy[50];    // Log pembuat
    char createdDate[20];  // Log tanggal
    char modifiedBy[50];   // Log pengedit
    char modifiedDate[20]; // Log tanggal edit
} ModulAjar;

// 7. DATA JADWAL
typedef struct {
    char hari[15];         // Hari (Senin, Selasa, dst)
    char jam[15];          // Jam Kuliah
    char matkul[50];       // Nama Matkul
    char ruang[20];        // Ruangan
    char kelas[20];        // Kelas
} Jadwal;

// 8. DATA NILAI
typedef struct {
    char nim[20];          // NIM Mahasiswa
    char nama[50];         // Nama Mahasiswa
    int tugas;             // Nilai Tugas
    int uts;               // Nilai UTS
    int uas;               // Nilai UAS
    float nilaiAkhir;      // Perhitungan Nilai Akhir
    char grade[3];         // Grade Huruf (A, B, C...)
} MahasiswaNilai;

#endif