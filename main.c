// ===============================================
// SISTEM INFORMASI AKADEMIK - MERGED VERSION
// FILE UTAMA: main.c
// ===============================================

// Memanggil modul-modul program secara berurutan
#include "config.h"         // 1. Konfigurasi
#include "structures.h"     // 2. Data Model
#include "globals.h"        // 3. Global Variable & Init
#include "utils.h"          // 4. Utilitas UI
#include "admin_features.h" // 5. Fitur Admin
#include "dosen_features.h" // 6. Fitur Dosen
#include "screens.h"        // 7. Layar Utama

int main() {
    setupScreen();   // Persiapkan layar (Full screen, hide cursor)
    initData();      // Isi data dummy awal
    loadingScreen(); // Tampilkan animasi loading
    
    // Loop Utama Program
    while(1) {
        // Tampilkan Login Screen dan ambil role user (1=Admin, 2=Dosen, 0=Exit)
        int role = loginScreen();
        
        if (role == 1) {
            // JIKA LOGIN SEBAGAI ADMIN
            dashboardAdminScreen(); 
        } else if (role == 2) {
            // JIKA LOGIN SEBAGAI DOSEN
            dashboardDosenScreen();
        } else {
            // JIKA EXIT
            break;
        }
    }

    // Penutup program
    setColor(COLOR_NORMAL | FOREGROUND_WHITE);
    system("cls");
    printf("Aplikasi Ditutup. Terima Kasih.\n");
    return 0;
}