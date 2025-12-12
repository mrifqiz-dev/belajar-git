// ===============================================
// FILE: globals.h
// DESKRIPSI: Variabel Global dan Inisialisasi Data
// ===============================================

#ifndef GLOBALS_H
#define GLOBALS_H

#include "config.h"     // Include konfigurasi
#include "structures.h" // Include struktur data

// --- VARIABEL STATE USER LOGIN ---
char CURRENT_USER_NAME[50] = "Guest"; // Menyimpan nama user yang sedang login
char CURRENT_USER_ID[20]   = "GUEST"; // Menyimpan ID user yang sedang login
char CURRENT_USER_ROLE[20] = "None";  // Menyimpan peran (Admin/Dosen)

// --- PENYIMPANAN DATA (DATABASE ARRAY) ---
Dosen dataDosen[MAX_DATA]; int countDosen = 0;       // Array data Dosen & hitungan jumlah
Mahasiswa dataMhs[MAX_DATA]; int countMhs = 0;       // Array data Mahasiswa & hitungan jumlah
MataKuliah dataMatkul[MAX_DATA]; int countMatkul = 0;// Array data Matkul & hitungan jumlah
Prodi dataProdi[MAX_DATA]; int countProdi = 0;       // Array data Prodi & hitungan jumlah
Kelas dataKelas[MAX_DATA]; int countKelas = 0;       // Array data Kelas & hitungan jumlah
ModulAjar dataModul[MAX_DATA]; int countModul = 0;   // Array data Modul & hitungan jumlah
Jadwal dataJadwal[MAX_DATA]; int countJadwal = 0;    // Array data Jadwal & hitungan jumlah
MahasiswaNilai dataNilai[MAX_DATA]; int countNilai = 0; // Array data Nilai & hitungan jumlah

// Fungsi Prototyping (agar bisa dipanggil sebelum didefinisikan)
void getSystemDate(char *buffer);

// --- LOGIKA HITUNG GRADE (Helper) ---
void calculateGrade(int index) {
    // Menghitung nilai akhir: 30% Tugas + 30% UTS + 40% UAS
    float akhir = (dataNilai[index].tugas * 0.3) + (dataNilai[index].uts * 0.3) + (dataNilai[index].uas * 0.4);
    dataNilai[index].nilaiAkhir = akhir; // Simpan ke struct
    
    // Konversi angka ke huruf
    if (akhir >= 85) strcpy(dataNilai[index].grade, "A");
    else if (akhir >= 70) strcpy(dataNilai[index].grade, "B");
    else if (akhir >= 55) strcpy(dataNilai[index].grade, "C");
    else if (akhir >= 40) strcpy(dataNilai[index].grade, "D");
    else strcpy(dataNilai[index].grade, "E");
}

// --- FUNGSI INISIALISASI DATA AWAL (DUMMY DATA) ---
void initData() {
    char dateNow[20]; 
    getSystemDate(dateNow); // Ambil tanggal sekarang

    // 1. Tambah Data Dosen Dummy
    strcpy(dataDosen[0].nidn, "001"); 
    strcpy(dataDosen[0].nama, "Dr. Budi Santoso");
    strcpy(dataDosen[0].email, "budi@univ.ac.id"); 
    strcpy(dataDosen[0].modifiedDate, dateNow);
    countDosen = 1; // Set jumlah dosen jadi 1

    // 2. Tambah Data Mahasiswa Dummy
    strcpy(dataMhs[0].nim, "09123001"); 
    strcpy(dataMhs[0].nama, "Ilham Kurniawan");
    strcpy(dataMhs[0].prodi, "TI"); 
    strcpy(dataMhs[0].modifiedDate, dateNow);
    countMhs = 1;

    // 3. Tambah Data Mata Kuliah Dummy
    strcpy(dataMatkul[0].kode, "MK001"); 
    strcpy(dataMatkul[0].nama, "Pemrograman C");
    dataMatkul[0].sks = 4; 
    dataMatkul[0].semester = 1; 
    strcpy(dataMatkul[0].modifiedBy, "SYSTEM");
    
    strcpy(dataMatkul[1].kode, "MK002"); 
    strcpy(dataMatkul[1].nama, "Struktur Data");
    dataMatkul[1].sks = 3; 
    dataMatkul[1].semester = 2; 
    strcpy(dataMatkul[1].modifiedBy, "SYSTEM");
    countMatkul = 2;

    // 4. Tambah Data Prodi Dummy
    strcpy(dataProdi[0].id, "TI"); 
    strcpy(dataProdi[0].nama, "T. Informatika");
    strcpy(dataProdi[0].fakultas, "Ilmu Komputer");
    countProdi = 1;

    // 5. Tambah Data Kelas Dummy
    strcpy(dataKelas[0].id, "K01"); 
    strcpy(dataKelas[0].nama, "TI-A 2023");
    strcpy(dataKelas[0].ruang, "R.304");
    countKelas = 1;

    // 6. Tambah Data Modul Dummy
    strcpy(dataModul[0].id_modul, "MDL01"); 
    strcpy(dataModul[0].kode_matkul, "MK001"); 
    strcpy(dataModul[0].judul, "Pengenalan C"); 
    strcpy(dataModul[0].tipe, "PDF");
    strcpy(dataModul[0].createdDate, dateNow);
    countModul = 1;

    // 7. Tambah Data Jadwal Dummy
    strcpy(dataJadwal[0].hari, "Senin"); 
    strcpy(dataJadwal[0].jam, "08:00 - 10:00"); 
    strcpy(dataJadwal[0].matkul, "Pemrograman C"); 
    strcpy(dataJadwal[0].ruang, "LAB-1"); 
    strcpy(dataJadwal[0].kelas, "TI-A");
    countJadwal = 1;

    // 8. Tambah Data Nilai Dummy
    strcpy(dataNilai[0].nim, "09123001"); 
    strcpy(dataNilai[0].nama, "Ilham Kurniawan"); 
    dataNilai[0].tugas=80; 
    dataNilai[0].uts=75; 
    dataNilai[0].uas=85; 
    calculateGrade(0); // Hitung grade otomatis
    countNilai = 1;
}

#endif