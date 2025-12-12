// ===============================================
// FILE: admin_features.h
// DESKRIPSI: Fitur Manajemen untuk Admin (CRUD LENGKAP + VALIDASI)
// ===============================================

#ifndef ADMIN_FEATURES_H
#define ADMIN_FEATURES_H

#include "globals.h"
#include "utils.h"

// ==========================================================
// 1. MANAJEMEN DOSEN (Create, Update, Delete + Validasi)
// ==========================================================
void manageDosen(int x, int y, int w, int h) {
    int formH = 12; int tableH = h - formH - 1; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN DATA DOSEN ===");
        gotoxy(x + 2, listY); printf("%-3s %-10s %-20s %-15s", "NO", "NIDN", "NAMA DOSEN", "LAST UPDATED");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countDosen && i < tableH - 4; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-20s %-15s", i+1, dataDosen[i].nidn, dataDosen[i].nama, dataDosen[i].modifiedDate);
        }

        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Create  [U] Update  [D] Delete  [ESC] Kembali ");
        
        int key = _getch(); int formY = y + tableH; 
        
        if (key == KEY_ESC) running = 0;
        
        // --- CREATE DOSEN ---
        else if (key == 'c' || key == 'C') {
            if (countDosen >= MAX_DATA) { showMessage(x+2, formY+2, "Data Penuh!", COLOR_ERROR, 1000); continue; }
            drawFormArea(x, formY, w, "TAMBAH DOSEN BARU");
            
            char nidn[20], nama[50], email[50];
            gotoxy(x+2, formY+2); printf("NIDN  : "); inputString(x+10, formY+2, nidn, 15, 0);
            
            // VALIDASI DUPLIKASI
            int exist = 0;
            for(int i=0; i<countDosen; i++) if(strcmp(dataDosen[i].nidn, nidn) == 0) exist = 1;
            if(exist) { showMessage(x+2, formY+6, "Error: NIDN Sudah Ada!", COLOR_ERROR, 1500); continue; }
            if(strlen(nidn)==0) continue;

            gotoxy(x+2, formY+3); printf("Nama  : "); inputString(x+10, formY+3, nama, 40, 0);
            gotoxy(x+2, formY+4); printf("Email : "); inputString(x+10, formY+4, email, 40, 0);
            
            strcpy(dataDosen[countDosen].nidn, nidn); strcpy(dataDosen[countDosen].nama, nama);
            strcpy(dataDosen[countDosen].email, email);
            char dateNow[20]; getSystemDate(dateNow); strcpy(dataDosen[countDosen].modifiedDate, dateNow);
            countDosen++;
            showMessage(x+2, formY+6, "Data Berhasil Disimpan!", COLOR_SUCCESS, 1000);
        }

        // --- UPDATE DOSEN ---
        else if (key == 'u' || key == 'U') {
            drawFormArea(x, formY, w, "UPDATE DOSEN");
            char target[20];
            gotoxy(x+2, formY+2); printf("Cari NIDN: "); inputString(x+13, formY+2, target, 15, 0);
            
            int idx = -1;
            for(int i=0; i<countDosen; i++) if(strcmp(dataDosen[i].nidn, target)==0) idx = i;
            
            if(idx != -1) {
                gotoxy(x+2, formY+3); printf("Nama Baru : "); inputString(x+14, formY+3, dataDosen[idx].nama, 40, 0);
                gotoxy(x+2, formY+4); printf("Email Baru: "); inputString(x+14, formY+4, dataDosen[idx].email, 40, 0);
                char dateNow[20]; getSystemDate(dateNow); strcpy(dataDosen[idx].modifiedDate, dateNow);
                showMessage(x+2, formY+6, "Data Diupdate!", COLOR_SUCCESS, 1000);
            } else {
                showMessage(x+2, formY+6, "NIDN Tidak Ditemukan!", COLOR_ERROR, 1000);
            }
        }

        // --- DELETE DOSEN ---
        else if (key == 'd' || key == 'D') {
            drawFormArea(x, formY, w, "HAPUS DOSEN");
            char target[20];
            gotoxy(x+2, formY+2); printf("Hapus NIDN: "); inputString(x+14, formY+2, target, 15, 0);
            int idx = -1;
            for(int i=0; i<countDosen; i++) if(strcmp(dataDosen[i].nidn, target)==0) idx = i;
            
            if(idx != -1) {
                for(int i=idx; i<countDosen-1; i++) dataDosen[i] = dataDosen[i+1];
                countDosen--;
                showMessage(x+2, formY+6, "Data Dihapus!", COLOR_SUCCESS, 1000);
            } else {
                showMessage(x+2, formY+6, "NIDN Tidak Ditemukan!", COLOR_ERROR, 1000);
            }
        }
    }
}

// ==========================================================
// 2. MANAJEMEN MAHASISWA (Create, Update, Delete + Validasi)
// ==========================================================
void manageMahasiswa(int x, int y, int w, int h) {
    int formH = 12; int tableH = h - formH - 1; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN DATA MAHASISWA ===");
        gotoxy(x + 2, listY); printf("%-3s %-10s %-20s %-15s", "NO", "NIM", "NAMA MAHASISWA", "PRODI");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countMhs && i < tableH - 4; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-20s %-15s", i+1, dataMhs[i].nim, dataMhs[i].nama, dataMhs[i].prodi);
        }

        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Create  [U] Update  [D] Delete  [ESC] Kembali ");
        
        int key = _getch(); int formY = y + tableH;
        if (key == KEY_ESC) running = 0;
        
        // --- CREATE MHS ---
        else if (key == 'c' || key == 'C') {
             if (countMhs >= MAX_DATA) continue;
             drawFormArea(x, formY, w, "TAMBAH MAHASISWA");
             char nim[20], nama[50], prodi[30];
             gotoxy(x+2, formY+2); printf("NIM   : "); inputString(x+10, formY+2, nim, 15, 0);
             
             // VALIDASI DUPLIKASI
             int exist = 0;
             for(int i=0; i<countMhs; i++) if(strcmp(dataMhs[i].nim, nim) == 0) exist = 1;
             if(exist) { showMessage(x+2, formY+6, "Error: NIM Sudah Ada!", COLOR_ERROR, 1500); continue; }
             if(strlen(nim)==0) continue;

             gotoxy(x+2, formY+3); printf("Nama  : "); inputString(x+10, formY+3, nama, 30, 0);
             gotoxy(x+2, formY+4); printf("Prodi : "); inputString(x+10, formY+4, prodi, 10, 0);
             
             strcpy(dataMhs[countMhs].nim, nim); strcpy(dataMhs[countMhs].nama, nama);
             strcpy(dataMhs[countMhs].prodi, prodi);
             char dateNow[20]; getSystemDate(dateNow); strcpy(dataMhs[countMhs].modifiedDate, dateNow);
             countMhs++;
             showMessage(x+2, formY+6, "Data Berhasil Disimpan!", COLOR_SUCCESS, 1000);
        }

        // --- UPDATE MHS ---
        else if (key == 'u' || key == 'U') {
            drawFormArea(x, formY, w, "UPDATE MAHASISWA");
            char target[20];
            gotoxy(x+2, formY+2); printf("Cari NIM : "); inputString(x+12, formY+2, target, 15, 0);
            int idx = -1;
            for(int i=0; i<countMhs; i++) if(strcmp(dataMhs[i].nim, target)==0) idx = i;
            
            if(idx != -1) {
                gotoxy(x+2, formY+3); printf("Nama Baru: "); inputString(x+12, formY+3, dataMhs[idx].nama, 30, 0);
                gotoxy(x+2, formY+4); printf("Prodi    : "); inputString(x+12, formY+4, dataMhs[idx].prodi, 10, 0);
                char dateNow[20]; getSystemDate(dateNow); strcpy(dataMhs[idx].modifiedDate, dateNow);
                showMessage(x+2, formY+6, "Data Diupdate!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+6, "NIM Tidak Ditemukan!", COLOR_ERROR, 1000);
        }

        // --- DELETE MHS ---
        else if (key == 'd' || key == 'D') {
            drawFormArea(x, formY, w, "HAPUS MAHASISWA");
            char target[20];
            gotoxy(x+2, formY+2); printf("Hapus NIM: "); inputString(x+12, formY+2, target, 15, 0);
            int idx = -1;
            for(int i=0; i<countMhs; i++) if(strcmp(dataMhs[i].nim, target)==0) idx = i;
            if(idx != -1) {
                for(int i=idx; i<countMhs-1; i++) dataMhs[i] = dataMhs[i+1];
                countMhs--;
                showMessage(x+2, formY+6, "Data Dihapus!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+6, "NIM Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

// ==========================================================
// 3. MANAJEMEN MATA KULIAH (Create, Update, Delete + Validasi)
// ==========================================================
void manageMatkulAdmin(int x, int y, int w, int h) {
    int formH = 12; int tableH = h - formH - 1; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN MATA KULIAH (ADMIN) ===");
        gotoxy(x + 2, listY); printf("%-3s %-10s %-20s %-5s %-5s", "NO", "KODE", "NAMA MATKUL", "SKS", "SMT");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countMatkul && i < tableH - 4; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-20s %-5d %-5d", i+1, dataMatkul[i].kode, dataMatkul[i].nama, dataMatkul[i].sks, dataMatkul[i].semester);
        }

        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Create  [U] Update  [D] Delete  [ESC] Kembali ");
        
        int key = _getch(); int formY = y + tableH;
        if (key == KEY_ESC) running = 0;
        
        // --- CREATE MATKUL ---
        else if (key == 'c' || key == 'C') { 
             drawFormArea(x, formY, w, "TAMBAH MATKUL");
             char kode[20], nama[50]; int sks, smt;
             gotoxy(x+2, formY+2); printf("Kode : "); inputString(x+10, formY+2, kode, 10, 0);
             
             // VALIDASI DUPLIKASI
             int exist = 0;
             for(int i=0; i<countMatkul; i++) if(strcmp(dataMatkul[i].kode, kode) == 0) exist = 1;
             if(exist) { showMessage(x+2, formY+6, "Error: Kode MK Sudah Ada!", COLOR_ERROR, 1500); continue; }
             if(strlen(kode)==0) continue;

             gotoxy(x+2, formY+3); printf("Nama : "); inputString(x+10, formY+3, nama, 30, 0);
             gotoxy(x+2, formY+4); printf("SKS  : "); inputInt(x+10, formY+4, &sks, 2);
             gotoxy(x+2, formY+5); printf("Smt  : "); inputInt(x+10, formY+5, &smt, 2);
             
             if(sks>0){
                 strcpy(dataMatkul[countMatkul].kode, kode); strcpy(dataMatkul[countMatkul].nama, nama);
                 dataMatkul[countMatkul].sks = sks; dataMatkul[countMatkul].semester = smt;
                 countMatkul++;
                 showMessage(x+2, formY+6, "Disimpan!", COLOR_SUCCESS, 1000);
             }
        }
        
        // --- UPDATE MATKUL (BARU) ---
        else if (key == 'u' || key == 'U') {
             drawFormArea(x, formY, w, "UPDATE MATKUL");
             char target[20];
             gotoxy(x+2, formY+2); printf("Cari Kode: "); inputString(x+13, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countMatkul; i++) if(strcmp(dataMatkul[i].kode, target)==0) idx = i;
             
             if(idx != -1) {
                 gotoxy(x+2, formY+3); printf("Nama Baru: "); inputString(x+13, formY+3, dataMatkul[idx].nama, 30, 0);
                 int newSks = -1; int newSmt = -1;
                 gotoxy(x+2, formY+4); printf("SKS Baru : "); inputInt(x+13, formY+4, &newSks, 2);
                 gotoxy(x+2, formY+5); printf("Smt Baru : "); inputInt(x+13, formY+5, &newSmt, 2);
                 
                 if(newSks > 0) dataMatkul[idx].sks = newSks;
                 if(newSmt > 0) dataMatkul[idx].semester = newSmt;
                 showMessage(x+2, formY+6, "Data Diupdate!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "Kode MK Tidak Ditemukan!", COLOR_ERROR, 1000);
        }

        // --- DELETE MATKUL ---
        else if (key == 'd' || key == 'D') {
             drawFormArea(x, formY, w, "HAPUS MATKUL");
             char target[20];
             gotoxy(x+2, formY+2); printf("Hapus Kode: "); inputString(x+14, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countMatkul; i++) if(strcmp(dataMatkul[i].kode, target)==0) idx = i;
             
             if(idx != -1) {
                 for(int i=idx; i<countMatkul-1; i++) dataMatkul[i] = dataMatkul[i+1];
                 countMatkul--;
                 showMessage(x+2, formY+6, "Terhapus!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "Kode MK Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

// ==========================================================
// 4. MANAJEMEN PRODI (Create, Update, Delete + Validasi) - SEKARANG FULL CRUD
// ==========================================================
void manageProdi(int x, int y, int w, int h) {
    int formH = 12; int tableH = h - formH - 1; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN DATA PRODI ===");
        gotoxy(x + 2, listY); printf("%-3s %-10s %-20s %-15s", "NO", "ID", "NAMA PRODI", "FAKULTAS");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countProdi && i < tableH - 4; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-20s %-15s", i+1, dataProdi[i].id, dataProdi[i].nama, dataProdi[i].fakultas);
        }
        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Create  [U] Update  [D] Delete  [ESC] Kembali ");
        
        int key = _getch(); int formY = y + tableH;
        if (key == KEY_ESC) running = 0;

        // --- CREATE PRODI ---
        else if (key == 'c' || key == 'C') {
             drawFormArea(x, formY, w, "TAMBAH PRODI");
             char id[20], nama[50], fakultas[50];
             gotoxy(x+2, formY+2); printf("ID Prodi : "); inputString(x+13, formY+2, id, 10, 0);
             
             // VALIDASI DUPLIKASI
             int exist = 0;
             for(int i=0; i<countProdi; i++) if(strcmp(dataProdi[i].id, id) == 0) exist = 1;
             if(exist) { showMessage(x+2, formY+6, "Error: ID Prodi Sudah Ada!", COLOR_ERROR, 1500); continue; }
             if(strlen(id)==0) continue;

             gotoxy(x+2, formY+3); printf("Nama     : "); inputString(x+13, formY+3, nama, 30, 0);
             gotoxy(x+2, formY+4); printf("Fakultas : "); inputString(x+13, formY+4, fakultas, 30, 0);
             
             strcpy(dataProdi[countProdi].id, id); 
             strcpy(dataProdi[countProdi].nama, nama);
             strcpy(dataProdi[countProdi].fakultas, fakultas);
             countProdi++;
             showMessage(x+2, formY+6, "Disimpan!", COLOR_SUCCESS, 1000);
        }

        // --- UPDATE PRODI ---
        else if (key == 'u' || key == 'U') {
             drawFormArea(x, formY, w, "UPDATE PRODI");
             char target[20];
             gotoxy(x+2, formY+2); printf("Cari ID : "); inputString(x+12, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countProdi; i++) if(strcmp(dataProdi[i].id, target)==0) idx = i;
             
             if(idx != -1) {
                 gotoxy(x+2, formY+3); printf("Nama Baru: "); inputString(x+13, formY+3, dataProdi[idx].nama, 30, 0);
                 gotoxy(x+2, formY+4); printf("Fak. Baru: "); inputString(x+13, formY+4, dataProdi[idx].fakultas, 30, 0);
                 showMessage(x+2, formY+6, "Data Diupdate!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "ID Tidak Ditemukan!", COLOR_ERROR, 1000);
        }

        // --- DELETE PRODI ---
        else if (key == 'd' || key == 'D') {
             drawFormArea(x, formY, w, "HAPUS PRODI");
             char target[20];
             gotoxy(x+2, formY+2); printf("Hapus ID: "); inputString(x+12, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countProdi; i++) if(strcmp(dataProdi[i].id, target)==0) idx = i;
             
             if(idx != -1) {
                 for(int i=idx; i<countProdi-1; i++) dataProdi[i] = dataProdi[i+1];
                 countProdi--;
                 showMessage(x+2, formY+6, "Terhapus!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "ID Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

// ==========================================================
// 5. MANAJEMEN KELAS (Create, Update, Delete + Validasi) - SEKARANG FULL CRUD
// ==========================================================
void manageKelas(int x, int y, int w, int h) {
    int formH = 12; int tableH = h - formH - 1; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN DATA KELAS ===");
        gotoxy(x + 2, listY); printf("%-3s %-10s %-25s %-15s", "NO", "ID KELAS", "NAMA KELAS", "RUANG");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countKelas && i < tableH - 4; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-25s %-15s", i+1, dataKelas[i].id, dataKelas[i].nama, dataKelas[i].ruang);
        }
        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Create  [U] Update  [D] Delete  [ESC] Kembali ");
        
        int key = _getch(); int formY = y + tableH;
        if (key == KEY_ESC) running = 0;

        // --- CREATE KELAS ---
        else if (key == 'c' || key == 'C') {
             drawFormArea(x, formY, w, "TAMBAH KELAS");
             char id[20], nama[50], ruang[20];
             gotoxy(x+2, formY+2); printf("ID Kelas : "); inputString(x+13, formY+2, id, 10, 0);
             
             // VALIDASI DUPLIKASI
             int exist = 0;
             for(int i=0; i<countKelas; i++) if(strcmp(dataKelas[i].id, id) == 0) exist = 1;
             if(exist) { showMessage(x+2, formY+6, "Error: ID Kelas Sudah Ada!", COLOR_ERROR, 1500); continue; }
             if(strlen(id)==0) continue;

             gotoxy(x+2, formY+3); printf("Nama     : "); inputString(x+13, formY+3, nama, 30, 0);
             gotoxy(x+2, formY+4); printf("Ruang    : "); inputString(x+13, formY+4, ruang, 20, 0);
             
             strcpy(dataKelas[countKelas].id, id); 
             strcpy(dataKelas[countKelas].nama, nama);
             strcpy(dataKelas[countKelas].ruang, ruang);
             countKelas++;
             showMessage(x+2, formY+6, "Disimpan!", COLOR_SUCCESS, 1000);
        }

        // --- UPDATE KELAS ---
        else if (key == 'u' || key == 'U') {
             drawFormArea(x, formY, w, "UPDATE KELAS");
             char target[20];
             gotoxy(x+2, formY+2); printf("Cari ID : "); inputString(x+12, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countKelas; i++) if(strcmp(dataKelas[i].id, target)==0) idx = i;
             
             if(idx != -1) {
                 gotoxy(x+2, formY+3); printf("Nama Baru: "); inputString(x+13, formY+3, dataKelas[idx].nama, 30, 0);
                 gotoxy(x+2, formY+4); printf("Ruang Baru: "); inputString(x+14, formY+4, dataKelas[idx].ruang, 20, 0);
                 showMessage(x+2, formY+6, "Data Diupdate!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "ID Tidak Ditemukan!", COLOR_ERROR, 1000);
        }

        // --- DELETE KELAS ---
        else if (key == 'd' || key == 'D') {
             drawFormArea(x, formY, w, "HAPUS KELAS");
             char target[20];
             gotoxy(x+2, formY+2); printf("Hapus ID: "); inputString(x+12, formY+2, target, 10, 0);
             int idx = -1;
             for(int i=0; i<countKelas; i++) if(strcmp(dataKelas[i].id, target)==0) idx = i;
             
             if(idx != -1) {
                 for(int i=idx; i<countKelas-1; i++) dataKelas[i] = dataKelas[i+1];
                 countKelas--;
                 showMessage(x+2, formY+6, "Terhapus!", COLOR_SUCCESS, 1000);
             } else showMessage(x+2, formY+6, "ID Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

#endif