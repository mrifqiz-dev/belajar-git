// ===============================================
// FILE: screens.h
// DESKRIPSI: Tampilan Utama (Screen) Aplikasi
// ===============================================

#ifndef SCREENS_H
#define SCREENS_H

#include "globals.h"
#include "utils.h"
#include "admin_features.h"
#include "dosen_features.h"

// Tampilan Loading Awal
void loadingScreen() {
    updateTermSize();
    clearScreen();
    int centerX = getTermWidth() / 2;
    int centerY = getTermHeight() / 2;
    char *msg = "MEMUAT SISTEM INFORMASI AKADEMIK...";
    gotoxy(centerX - (strlen(msg)/2), centerY - 2);
    setColor(COLOR_NORMAL | FOREGROUND_WHITE); 
    printf("%s", msg);
    
    int barWidth = 40;
    int barX = centerX - (barWidth / 2);
    drawProgressBar(barX, centerY, barWidth, 30); // Gambar progress bar
    setColor(COLOR_NORMAL);
    Sleep(500);
}

// Tampilan Login
int loginScreen() {
    int firstRun = 1;
    while(1) {
        if(firstRun) { Sleep(100); firstRun = 0; }
        updateTermSize();
        clearScreenColor(COLOR_LOGIN_BG);
        
        // Perhitungan posisi kotak tengah
        int boxW = 50; int boxH = 14; 
        int cx = getTermWidth() / 2; int cy = getTermHeight() / 2;
        int boxX = cx - (boxW / 2); int boxY = cy - 4;

        // Gambar ASCII ART
        setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        int asciiY = cy - 12;
        gotoxy(cx - 30, asciiY++); printf("   _____ _____          _  __          _____  ");
        gotoxy(cx - 30, asciiY++); printf("  / ____|_   _|   /\\   | |/ /    /\\   |  __ \\ ");
        gotoxy(cx - 30, asciiY++); printf(" | (___   | |    /  \\  | ' /    /  \\  | |  | |");
        gotoxy(cx - 30, asciiY++); printf("  \\___ \\  | |   / /\\ \\ |  <    / /\\ \\ | |  | |");
        gotoxy(cx - 30, asciiY++); printf("  ____) |_| |_ / ____ \\| . \\  / ____ \\| |__| |");
        gotoxy(cx - 30, asciiY++); printf(" |_____/|_____/_/    \\_\\_|\\_\\/_/    \\_\\_____/ ");
        gotoxy(cx - 30, asciiY+1); for(int i=0; i<60; i++) printf("-");

        // Gambar Kotak Login
        drawBlock(boxX, boxY, boxW, boxH, COLOR_THEME);
        setColor(COLOR_THEME);
        // Bingkai kotak
        gotoxy(boxX, boxY); printf("%c", 201); for(int i=0; i<boxW-2; i++) printf("%c", 205); printf("%c", 187);
        for(int i=1; i<boxH-1; i++) {
            gotoxy(boxX, boxY+i); printf("%c", 186);
            gotoxy(boxX+boxW-1, boxY+i); printf("%c", 186);
        }
        gotoxy(boxX, boxY+boxH-1); printf("%c", 200); for(int i=0; i<boxW-2; i++) printf("%c", 205); printf("%c", 188);

        char *title = " Masuk ";
        gotoxy(cx - (strlen(title)/2), boxY + 2); printf("%s", title);
        gotoxy(boxX+2, boxY+3); for(int i=0; i<boxW-4; i++) printf("-");

        gotoxy(boxX + 5, boxY + 5); printf("Nama Pengguna");
        gotoxy(boxX + 5, boxY + 9); printf("Kata Sandi");
        setColor(COLOR_LOGIN_BG | FOREGROUND_INTENSITY); 
        gotoxy(boxX + 15, boxY + 12); printf(" Tekan [ESC] untuk keluar ");

        char id[20] = ""; char pass[20] = "";
        
        // Input Username
        inputLogin(boxX + 5, boxY + 6, id, 40, 0);
        if (strlen(id) == 0 && id[0] == '\0') return 0; // Exit program

        // Input Password
        inputLogin(boxX + 5, boxY + 10, pass, 40, 1);
        if (strlen(pass) == 0 && pass[0] == '\0') continue;

        gotoxy(cx - 5, boxY + boxH + 2);
        setColor(FOREGROUND_WHITE); printf("Verifikasi Kredensial..."); Sleep(800);

        // Validasi Hardcoded
        if (strcmp(id, "ADM001") == 0 && strcmp(pass, "superadmin") == 0) {
            strcpy(CURRENT_USER_NAME, "Super Admin");
            strcpy(CURRENT_USER_ID, "ADM001");
            strcpy(CURRENT_USER_ROLE, "Admin");
            return 1; // Role Admin
        } 
        else if (strcmp(id, "DSN001") == 0 && strcmp(pass, "dosen") == 0) {
            strcpy(CURRENT_USER_NAME, "Dr. Fikri Basev"); 
            strcpy(CURRENT_USER_ID, "DSN001");
            strcpy(CURRENT_USER_ROLE, "Dosen");
            return 2; // Role Dosen
        } 
        else {
            showMessage(boxX + 5, boxY + 12, "MASUK GAGAL! Coba lagi.", COLOR_ERROR, 1500);
        }
    }
}

// Helper untuk Menggambar Layout Dasar Dashboard
void drawDashboardLayout(int leftW, int topH) {
    int gap = 1; int margin = 2;
    int rightW = getTermWidth() - leftW - (margin*2) - gap;
    int bottomH = getTermHeight() - topH - (margin*2) - gap;
    
    int x1 = margin; int x2 = margin + leftW + gap;
    int y1 = margin; int y2 = margin + topH + gap;

    // 1. Panel Profil (Kiri Atas)
    drawBlock(x1, y1, leftW, topH, COLOR_THEME);
    setColor(COLOR_THEME);
    gotoxy(x1 + 2, y1 + 3); printf("MASUK SEBAGAI:");
    gotoxy(x1 + 2, y1 + 5); printf("Nama : %s", CURRENT_USER_NAME);
    gotoxy(x1 + 2, y1 + 6); printf("Role : %s", CURRENT_USER_ROLE);
    if(strcmp(CURRENT_USER_ROLE, "Dosen") == 0) {
        gotoxy(x1 + 2, y1 + 7); printf("NIDN : %s", CURRENT_USER_ID);
    }

    // 2. Panel Header (Kanan Atas)
    drawBlock(x2, y1, rightW, topH, COLOR_THEME);
    setColor(COLOR_THEME);
    int tx = x2 + (rightW / 2) - 30; if (tx < x2 + 2) tx = x2 + 2; int ty = y1 + 2;
    gotoxy(tx, ty++); printf("     _    _  __    _    ____  _____ __  __ ___ _  __ ");
    gotoxy(tx, ty++); printf("    / \\  | |/ /   / \\  |  _ \\| ____|  \\/  |_ _| |/ / ");
    gotoxy(tx, ty++); printf("   / _ \\ | ' /   / _ \\ | | | |  _| | |\\/| || || ' /  ");
    gotoxy(tx, ty++); printf("  / ___ \\| . \\  / ___ \\| |_| | |___| |  | || || . \\  ");
    gotoxy(tx, ty++); printf(" /_/   \\_\\_|\\_\\/_/   \\_\\____/|_____|_|  |_|___|_|\\_\\ ");
    
    // Subtitle
    if(strcmp(CURRENT_USER_ROLE, "Admin") == 0) {
        gotoxy(tx + 10, ty++); printf("SUPER ADMIN DASHBOARD - V.2.0");
    } else {
        gotoxy(tx + 12, ty++); printf("TAMPILAN DOSEN - V.2.0");
    }

    // 3. Panel Menu (Kiri Bawah)
    drawBlock(x1, y2, leftW, bottomH, COLOR_THEME);
    setColor(COLOR_THEME);
    gotoxy(x1 + 2, y2 + 6); printf("MENU UTAMA:");
    
    // 4. Panel Konten (Kanan Bawah)
    drawBlock(x2, y2, rightW, bottomH, COLOR_THEME);
}

// DASHBOARD ADMIN
void dashboardAdminScreen() {
    int selected = 0;
    char *menuItems[] = { "Dashboard", "Data Mahasiswa", "Data Dosen",  "Data Mata Kuliah", "Data Prodi",  "Data Kelas", "Keluar" };
    int menuCount = 7; int running = 1;

    updateTermSize();
    clearScreenColor(COLOR_BG_GRAY);
    drawDashboardLayout(35, 10); // Gambar layout

    int margin=2; int gap=1; int leftW=35; int topH=10;
    int xLeft = margin; int yBottom = margin + topH + gap;
    int xRight = margin + leftW + gap; 
    int rightW = getTermWidth() - leftW - (margin*2) - gap;
    int bottomH = getTermHeight() - topH - (margin*2) - gap;

    while(running) {
        // Update Menu Selection
        for(int i = 0; i < menuCount; i++) {
            if (i == selected) setColor(COLOR_SELECTED); else setColor(COLOR_THEME);
            gotoxy(xLeft + 2, yBottom + 9 + (i*2)); 
            printf("%s %-25s ", (i == selected) ? ">" : " ", menuItems[i]);
        }

        // Update Content Area
        clearRightPanel(xRight, yBottom, rightW, bottomH); 
        setColor(COLOR_THEME);

        if(selected == 0) { // Dashboard Stats
            int cy = yBottom + 3; int cx = xRight + 5;
            gotoxy(cx, cy++); printf("=== DASHBOARD STATISTIK ===");
            gotoxy(cx, cy++); printf("Total Mahasiswa  : %d", countMhs);
            gotoxy(cx, cy++); printf("Total Dosen      : %d", countDosen);
            gotoxy(cx, cy++); printf("Total Mata Kuliah: %d", countMatkul);
            gotoxy(cx, cy++); printf("Total Prodi      : %d", countProdi);
            gotoxy(cx, cy++); printf("Total Kelas      : %d", countKelas);
        } else if (selected == 6) {
            gotoxy(xRight+5, yBottom+3); printf("Tekan ENTER untuk Log Out.");
        } else {
             gotoxy(xRight+5, yBottom+3); printf("Tekan ENTER untuk Mengelola Data.");
        }

        // Input Navigation
        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == KEY_UP) { selected--; if (selected < 0) selected = menuCount - 1; } 
            else if (key == KEY_DOWN) { selected++; if (selected >= menuCount) selected = 0; }
        } else if (key == KEY_ENTER) {
            if (selected == 6) { running = 0; }
            else {
                // Buka Sub-menu
                if (selected == 1) manageMahasiswa(xRight, yBottom, rightW, bottomH);
                else if (selected == 2) manageDosen(xRight, yBottom, rightW, bottomH);
                else if (selected == 3) manageMatkulAdmin(xRight, yBottom, rightW, bottomH);
                else if (selected == 4) manageProdi(xRight, yBottom, rightW, bottomH);
                else if (selected == 5) manageKelas(xRight, yBottom, rightW, bottomH);
                
                // Redraw Layout setelah kembali dari sub-menu
                updateTermSize();
                clearScreenColor(COLOR_BG_GRAY);
                drawDashboardLayout(35, 10);
            }
        }
    }
}

// DASHBOARD DOSEN
void dashboardDosenScreen() {
    int selected = 0;
    char *menuItems[] = { "Dashboard", "Data Mata Kuliah", "Jadwal Pertemuan", "Modul Pembelajaran", "Manajemen Nilai",  "Logout" };
    int menuCount = 6; int running = 1;

    updateTermSize();
    clearScreenColor(COLOR_BG_GRAY);
    drawDashboardLayout(35, 10);

    int margin=2; int gap=1; int leftW=35; int topH=10;
    int xLeft = margin; int yBottom = margin + topH + gap;
    int xRight = margin + leftW + gap; 
    int rightW = getTermWidth() - leftW - (margin*2) - gap;
    int bottomH = getTermHeight() - topH - (margin*2) - gap;

    while(running) {
        for(int i = 0; i < menuCount; i++) {
            if (i == selected) setColor(COLOR_SELECTED); else setColor(COLOR_THEME);
            gotoxy(xLeft + 2, yBottom + 9 + (i*2)); 
            printf("%s %-25s ", (i == selected) ? ">" : " ", menuItems[i]);
        }

        clearRightPanel(xRight, yBottom, rightW, bottomH);
        setColor(COLOR_THEME);

        if (selected == 0) {
            gotoxy(xRight + 4, yBottom + 3); printf("=== SELAMAT DATANG, %s ===", CURRENT_USER_NAME);
            gotoxy(xRight + 4, yBottom + 5); printf("Mata Kuliah     : %d Matkul", countMatkul);
            gotoxy(xRight + 4, yBottom + 6); printf("Jadwal Mengajar : %d Kelas", countJadwal);
            gotoxy(xRight + 4, yBottom + 7); printf("Modul Ajar      : %d File", countModul);
            gotoxy(xRight + 4, yBottom + 8); printf("Total Nilai Mhs : %d Mahasiswa", countNilai);
        } 
        else if (selected == 5) {
            gotoxy(xRight + 4, yBottom + 3); printf("Tekan ENTER untuk Keluar.");
        }
        else {
             gotoxy(xRight + 4, yBottom + 3); printf("Tekan ENTER untuk Mengelola %s", menuItems[selected]);
        }

        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == KEY_UP) { selected--; if (selected < 0) selected = menuCount - 1; } 
            else if (key == KEY_DOWN) { selected++; if (selected >= menuCount) selected = 0; }
        } else if (key == KEY_ENTER) {
            if (selected == 5) { running = 0; }
            else {
                if (selected == 1) dosenManageMatkul(xRight, yBottom, rightW, bottomH);
                else if (selected == 2) dosenManageJadwal(xRight, yBottom, rightW, bottomH);
                else if (selected == 3) dosenManageModul(xRight, yBottom, rightW, bottomH);
                else if (selected == 4) dosenManageNilai(xRight, yBottom, rightW, bottomH);

                updateTermSize();
                clearScreenColor(COLOR_BG_GRAY);
                drawDashboardLayout(35, 10);
            }
        }
    }
}

#endif