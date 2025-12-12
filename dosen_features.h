// ===============================================
// FILE: dosen_features.h
// DESKRIPSI: Fitur Manajemen untuk Dosen
// ===============================================

#ifndef DOSEN_FEATURES_H
#define DOSEN_FEATURES_H

#include "globals.h"
#include "utils.h"

// DOSEN: Lihat & Tambah Matkul
void dosenManageMatkul(int x, int y, int w, int h) {
    int tableH = h - 10;
    int listY = y + 1;
    int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== DATA MATA KULIAH (DOSEN VIEW) ===");
        gotoxy(x + 2, listY); 
        printf("%-5s %-10s %-30s %-5s %-5s", "NO", "KODE", "NAMA MATA KULIAH", "SKS", "SMT");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countMatkul && i < tableH; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-5d %-10s %-30s %-5d %-5d", 
                i+1, dataMatkul[i].kode, dataMatkul[i].nama, dataMatkul[i].sks, dataMatkul[i].semester);
        }
        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Tambah  [U] Edit  [D] Hapus  [ESC] Kembali");
        
        int key = _getch();
        int formY = y + tableH + 2;
        if (key == KEY_ESC) running = 0;
        else if (key == 'c' || key == 'C') { // CREATE
            if (countMatkul >= MAX_DATA) continue;
            drawFormArea(x, formY, w, "TAMBAH MATA KULIAH");
            char kode[20], nama[50]; int sks, smt;
            gotoxy(x+2, formY+2); printf("Kode MK : "); inputString(x+13, formY+2, kode, 10, 0);
            if(strlen(kode) == 0) continue;
            gotoxy(x+2, formY+3); printf("Nama MK : "); inputString(x+13, formY+3, nama, 35, 0);
            gotoxy(x+2, formY+4); printf("SKS     : "); inputInt(x+13, formY+4, &sks, 2);
            gotoxy(x+2, formY+5); printf("Semester: "); inputInt(x+13, formY+5, &smt, 2);
            if(sks > 0 && smt > 0) {
                strcpy(dataMatkul[countMatkul].kode, kode);
                strcpy(dataMatkul[countMatkul].nama, nama);
                dataMatkul[countMatkul].sks = sks; dataMatkul[countMatkul].semester = smt;
                countMatkul++;
                showMessage(x+2, formY+7, "Data Berhasil Disimpan!", COLOR_SUCCESS, 1000);
            }
        }
        else if (key == 'd' || key == 'D') { // DELETE
            drawFormArea(x, formY, w, "HAPUS MATKUL");
            char target[20];
            gotoxy(x+2, formY+2); printf("Kode Hapus: "); inputString(x+15, formY+2, target, 10, 0);
            int found = -1;
            for(int i=0; i<countMatkul; i++) if(strcmp(dataMatkul[i].kode, target)==0) found=i;
            if(found != -1) {
                for(int i=found; i<countMatkul-1; i++) dataMatkul[i]=dataMatkul[i+1]; // Geser array
                countMatkul--;
                showMessage(x+2, formY+4, "Terhapus!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+4, "Tak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

// DOSEN: Jadwal Mengajar
void dosenManageJadwal(int x, int y, int w, int h) {
    int tableH = h - 10;
    int listY = y + 1;
    int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x+2, y); printf("=== JADWAL MENGAJAR ===");
        gotoxy(x+2, y+2); 
        printf("%-3s %-10s %-15s %-20s %-10s %-10s", "NO", "HARI", "JAM", "MATA KULIAH", "RUANG", "KELAS");
        gotoxy(x+2, y+3); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i=0; i<countJadwal && i < tableH; i++) {
            gotoxy(x+2, y+4+i);
            printf("%-3d %-10s %-15s %-20s %-10s %-10s", 
                i+1, dataJadwal[i].hari, dataJadwal[i].jam, dataJadwal[i].matkul, dataJadwal[i].ruang, dataJadwal[i].kelas);
        }
        setColor(COLOR_SELECTED);
        gotoxy(x, y+h-1); printf(" [C] Tambah  [D] Hapus  [ESC] Kembali");
        
        int key = _getch(); int formY = y + tableH + 2;
        if (key == KEY_ESC) running = 0;
        else if (key == 'c' || key == 'C') { // CREATE
            if (countJadwal >= MAX_DATA) continue;
            drawFormArea(x, formY, w, "TAMBAH JADWAL BARU");
            char hari[15], jam[15], matkul[50], ruang[20], kelas[20];
            gotoxy(x+2, formY+2); printf("Hari    : "); inputString(x+12, formY+2, hari, 10, 0);
            if(strlen(hari) == 0) continue; 
            gotoxy(x+2, formY+3); printf("Jam     : "); inputString(x+12, formY+3, jam, 13, 0);
            gotoxy(x+2, formY+4); printf("Matkul  : "); inputString(x+12, formY+4, matkul, 30, 0);
            gotoxy(x+2, formY+5); printf("Ruang   : "); inputString(x+12, formY+5, ruang, 10, 0);
            gotoxy(x+2, formY+6); printf("Kelas   : "); inputString(x+12, formY+6, kelas, 10, 0);
            strcpy(dataJadwal[countJadwal].hari, hari); strcpy(dataJadwal[countJadwal].jam, jam);
            strcpy(dataJadwal[countJadwal].matkul, matkul); strcpy(dataJadwal[countJadwal].ruang, ruang);
            strcpy(dataJadwal[countJadwal].kelas, kelas); countJadwal++;
            showMessage(x+2, formY+8, "Jadwal Ditambah!", COLOR_SUCCESS, 1000);
        }
        else if (key == 'd' || key == 'D') { // DELETE
            drawFormArea(x, formY, w, "HAPUS JADWAL");
            int no;
            gotoxy(x+2, formY+2); printf("Nomor Hapus: "); inputInt(x+15, formY+2, &no, 3);
            if(no > 0 && no <= countJadwal) {
                int idx = no - 1;
                for(int i = idx; i < countJadwal - 1; i++) dataJadwal[i] = dataJadwal[i+1];
                countJadwal--;
                showMessage(x+2, formY+4, "Jadwal Dihapus!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+4, "Nomor Tidak Valid!", COLOR_ERROR, 1000);
        }
    }
}

// DOSEN: Modul Ajar
void dosenManageModul(int x, int y, int w, int h) {
    int tableH = h - 10; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MODUL PEMBELAJARAN ===");
        gotoxy(x + 2, listY); 
        printf("%-5s %-10s %-10s %-30s %-10s", "NO", "KODE", "MATKUL", "JUDUL MODUL", "TIPE");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");

        for(int i = 0; i < countModul && i < tableH; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-5d %-10s %-10s %-30s %-10s", 
                i+1, dataModul[i].id_modul, dataModul[i].kode_matkul, dataModul[i].judul, dataModul[i].tipe);
        }
        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Tambah  [D] Hapus  [ESC] Kembali");
        
        int key = _getch(); int formY = y + tableH + 2;
        if (key == KEY_ESC) running = 0;
        else if (key == 'c' || key == 'C') { // CREATE
            if (countModul >= MAX_DATA) continue;
            drawFormArea(x, formY, w, "TAMBAH MODUL BARU");
            char kode[20], matkul[20], judul[100], tipe[10];

            gotoxy(x+2, formY+2); printf("ID Modul: "); inputString(x+12, formY+2, kode, 10, 0);
            if(strlen(kode) == 0) continue;
            gotoxy(x+2, formY+3); printf("Kode MK : "); inputString(x+12, formY+3, matkul, 10, 0);
            gotoxy(x+2, formY+4); printf("Judul   : "); inputString(x+12, formY+4, judul, 40, 0);
            gotoxy(x+2, formY+5); printf("Tipe    : "); inputString(x+12, formY+5, tipe, 8, 0); 

            strcpy(dataModul[countModul].id_modul, kode);
            strcpy(dataModul[countModul].kode_matkul, matkul);
            strcpy(dataModul[countModul].judul, judul);
            strcpy(dataModul[countModul].tipe, tipe);
            
            char dateNow[20]; getSystemDate(dateNow);
            strcpy(dataModul[countModul].createdDate, dateNow);
            countModul++;
            showMessage(x+2, formY+7, "Modul Ditambahkan!", COLOR_SUCCESS, 1000);
        }
        else if (key == 'd' || key == 'D') { // DELETE
            drawFormArea(x, formY, w, "HAPUS MODUL");
            char target[20];
            gotoxy(x+2, formY+2); printf("Hapus ID: "); inputString(x+12, formY+2, target, 10, 0);
            int found = -1;
            for(int i=0; i<countModul; i++) if(strcmp(dataModul[i].id_modul, target)==0) found=i;
            if(found != -1) {
                for(int i=found; i<countModul-1; i++) dataModul[i] = dataModul[i+1];
                countModul--;
                showMessage(x+2, formY+4, "Modul Dihapus!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+4, "ID Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

// DOSEN: Manajemen Nilai
void dosenManageNilai(int x, int y, int w, int h) {
    int tableH = h - 10; int listY = y + 1; int running = 1;
    while(running) {
        clearRightPanel(x, y, w, h);
        setColor(COLOR_THEME);
        gotoxy(x + 2, y); printf("=== MANAJEMEN NILAI MAHASISWA ===");
        gotoxy(x + 2, listY); 
        printf("%-3s %-10s %-15s %-5s %-5s %-5s %-5s %-5s", "NO", "NIM", "NAMA", "TGS", "UTS", "UAS", "AKH", "GRD");
        gotoxy(x + 2, listY+1); for(int i=0; i<w-4; i++) printf("-");
        
        for(int i = 0; i < countNilai && i < tableH; i++) {
            gotoxy(x + 2, listY + 2 + i);
            printf("%-3d %-10s %-15s %-5d %-5d %-5d %-5.1f %-5s", 
                i+1, dataNilai[i].nim, dataNilai[i].nama, 
                dataNilai[i].tugas, dataNilai[i].uts, dataNilai[i].uas, 
                dataNilai[i].nilaiAkhir, dataNilai[i].grade);
        }   
        setColor(COLOR_SELECTED);
        gotoxy(x, y + h - 1); printf(" [C] Tambah  [U] Update Nilai  [D] Hapus  [ESC] Kembali");
        
        int key = _getch(); int formY = y + tableH + 2;
        if (key == KEY_ESC) running = 0;
        else if (key == 'c' || key == 'C') { // CREATE
            if (countNilai >= MAX_DATA) continue;
            drawFormArea(x, formY, w, "TAMBAH MAHASISWA KE NILAI");
            char nim[20], nama[50];
            gotoxy(x+2, formY+2); printf("NIM   : "); inputString(x+10, formY+2, nim, 15, 0);
            if(strlen(nim)==0) continue;
            gotoxy(x+2, formY+3); printf("Nama  : "); inputString(x+10, formY+3, nama, 30, 0);
            strcpy(dataNilai[countNilai].nim, nim);
            strcpy(dataNilai[countNilai].nama, nama);
            dataNilai[countNilai].tugas = 0; dataNilai[countNilai].uts = 0; dataNilai[countNilai].uas = 0;
            calculateGrade(countNilai); countNilai++;
            showMessage(x+2, formY+5, "Mahasiswa Ditambahkan!", COLOR_SUCCESS, 1000);
        }
        else if (key == 'u' || key == 'U') { // UPDATE
            drawFormArea(x, formY, w, "UPDATE NILAI");
            char target[20];
            gotoxy(x+2, formY+2); printf("Cari NIM : "); inputString(x+14, formY+2, target, 15, 0);
            int found = -1;
            for(int i=0; i<countNilai; i++) if(strcmp(dataNilai[i].nim, target)==0) found=i;
            if(found != -1) {
                gotoxy(x+2, formY+3); printf("Nama: %s", dataNilai[found].nama);
                int tgs, uts, uas;
                gotoxy(x+2, formY+4); printf("TGS: "); inputInt(x+7, formY+4, &tgs, 3);
                gotoxy(x+12, formY+4); printf("UTS: "); inputInt(x+17, formY+4, &uts, 3);
                gotoxy(x+22, formY+4); printf("UAS: "); inputInt(x+27, formY+4, &uas, 3);
                if(tgs >= 0) dataNilai[found].tugas = tgs;
                if(uts >= 0) dataNilai[found].uts = uts;
                if(uas >= 0) dataNilai[found].uas = uas;
                calculateGrade(found);
                showMessage(x+2, formY+6, "Nilai Disimpan!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+4, "NIM Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
        else if (key == 'd' || key == 'D') { // DELETE
            drawFormArea(x, formY, w, "HAPUS DATA NILAI");
            char target[20];
            gotoxy(x+2, formY+2); printf("Hapus NIM : "); inputString(x+14, formY+2, target, 15, 0);
            int found = -1;
            for(int i=0; i<countNilai; i++) if(strcmp(dataNilai[i].nim, target)==0) found=i;
            if(found != -1) {
                for(int i=found; i<countNilai-1; i++) dataNilai[i] = dataNilai[i+1];
                countNilai--;
                showMessage(x+2, formY+4, "Data Berhasil Dihapus!", COLOR_SUCCESS, 1000);
            } else showMessage(x+2, formY+4, "NIM Tidak Ditemukan!", COLOR_ERROR, 1000);
        }
    }
}

#endif