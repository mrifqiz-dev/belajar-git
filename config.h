// ===============================================
// FILE: config.h
// DESKRIPSI: Berisi library, konstanta warna, dan tombol
// ===============================================

#ifndef CONFIG_H // Cek apakah CONFIG_H belum didefinisikan (untuk mencegah duplikasi)
#define CONFIG_H // Definisikan CONFIG_H

// --- LIBRARY STANDAR ---
#include <stdio.h>      // Untuk input output standar (printf, scanf)
#include <stdlib.h>     // Untuk fungsi umum (system, atoi, malloc)
#include <string.h>     // Untuk manipulasi string (strcpy, strcmp)
#include <time.h>       // Untuk mengambil waktu sistem
#include <windows.h>    // Untuk fungsi API Windows (gotoxy, warna, sleep)
#include <conio.h>      // Untuk input tanpa enter (_getch)

// --- KONSTANTA TOMBOL KEYBOARD ---
#define KEY_UP 72       // Kode ASCII untuk panah atas
#define KEY_DOWN 80     // Kode ASCII untuk panah bawah
#define KEY_LEFT 75     // Kode ASCII untuk panah kiri
#define KEY_RIGHT 77    // Kode ASCII untuk panah kanan
#define KEY_ENTER 13    // Kode ASCII untuk tombol Enter
#define KEY_ESC 27      // Kode ASCII untuk tombol Escape
#define KEY_BACKSPACE 8 // Kode ASCII untuk tombol Backspace

// --- DEFINISI WARNA ---
// Kombinasi warna foreground (teks)
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// TEMA WARNA APLIKASI
// Latar Biru, Teks Putih Terang (Tema Utama)
#define COLOR_THEME (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY) 
// Latar Abu-abu (Campuran RGB background)
#define COLOR_BG_GRAY (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE) 
// Warna saat item dipilih (Biru dengan teks putih terang)
#define COLOR_SELECTED (BACKGROUND_BLUE | FOREGROUND_WHITE | FOREGROUND_INTENSITY) 
// Warna normal (Hitam)
#define COLOR_NORMAL (0) 
// Warna untuk pesan error (Merah)
#define COLOR_ERROR (FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
// Warna untuk pesan sukses (Hijau)
#define COLOR_SUCCESS (0 | BACKGROUND_GREEN | BACKGROUND_INTENSITY)

// Warna Khusus Tampilan Login
#define COLOR_LOGIN_INPUT (BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define COLOR_LOGIN_BG (0) // Latar belakang login (Hitam)

// --- BATASAN DATA ---
#define MAX_DATA 200 // Jumlah maksimal data array yang bisa disimpan

#endif // Akhir dari pengecekan CONFIG_H