// ===============================================
// FILE: utils.h
// DESKRIPSI: Utilitas Grafis (UI) dan Input
// ===============================================

#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include "structures.h" // <--- TAMBAHKAN BARIS INI (PENTING!)

// Sekarang TerminalSize sudah dikenali karena kita sudah include structures.h
static TerminalSize termSize = {0, 0}; 

// Mengambil ukuran terminal saat ini
void updateTermSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    termSize.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;  
    termSize.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; 
}

// ... (Sisa kode di bawahnya tetap sama, tidak perlu diubah)
// ...
// ...

int getTermWidth() { return termSize.width; }   
int getTermHeight() { return termSize.height; } 

void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info; info.dwSize = 100; info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info; info.dwSize = 100; info.bVisible = TRUE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setupScreen() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    Sleep(100);
    updateTermSize(); 
    hideCursor();     
    system("cls");    
}

void clearScreen() { system("cls"); } 

void clearScreenColor(int color) { 
    setColor(color); 
    system("cls"); 
}

void getSystemDate(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void drawBlock(int x, int y, int w, int h, int color) {
    setColor(color);
    for (int i = 0; i < h; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < w; j++) printf(" "); 
    }
}

void drawBox(int x, int y, int w, int h, int color, const char* title) {
    drawBlock(x, y, w, h, color); 
    if (title != NULL) {
        setColor(color);
        gotoxy(x + (w/2) - (strlen(title)/2), y + 1); 
        printf("%s", title); 
    }
}

void clearRightPanel(int x, int y, int w, int h) {
    drawBlock(x, y, w, h, COLOR_THEME); 
}

void drawFormArea(int x, int y, int w, const char* title) {
    int formH = 12; int formY = y + 1;
    setColor(COLOR_THEME); 
    drawBox(x, formY, w, formH, COLOR_THEME, title); 
    setColor(COLOR_THEME);
    gotoxy(x, formY); for(int i=0; i<w; i++) printf("-"); 
}

void showMessage(int x, int y, const char* message, int color, int delay) {
    setColor(color);
    gotoxy(x, y); printf(" %s ", message);
    if (delay > 0) Sleep(delay); 
}

void drawProgressBar(int x, int y, int width, int duration) {
    setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(x - 1, y); printf("["); 
    gotoxy(x + width, y); printf("]"); 
    setColor(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
    for (int i = 0; i < width; i++) {
        gotoxy(x + i, y); printf(" "); 
        Sleep(duration); 
    }
}

void inputString(int x, int y, char *buffer, int maxLen, int isPassword) {
    showCursor(); 
    setColor(COLOR_THEME); 
    gotoxy(x, y); for(int i=0; i<maxLen; i++) printf(" "); 
    gotoxy(x, y); 
    
    int index = 0; int ch;
    while (1) {
        ch = _getch(); 
        if (ch == KEY_ENTER) break; 
        else if (ch == KEY_ESC) { buffer[0] = '\0'; hideCursor(); return; } 
        else if (ch == KEY_BACKSPACE) {
            if (index > 0) { index--; printf("\b \b"); } 
        } 
        else if (index < maxLen && ch >= 32 && ch <= 126) {
            buffer[index++] = (char)ch; 
            if (isPassword) printf("*"); else printf("%c", ch); 
        }
    }
    buffer[index] = '\0'; 
    hideCursor(); 
}

void inputLogin(int x, int y, char *buffer, int maxLen, int isPassword) {
    showCursor();
    setColor(COLOR_LOGIN_INPUT);
    gotoxy(x, y); for(int i=0; i<maxLen; i++) printf(" ");
    gotoxy(x, y); 
    int index = 0; int ch;
    while (1) {
        ch = _getch();
        if (ch == KEY_ENTER) break;
        else if (ch == KEY_ESC) { buffer[0] = '\0'; hideCursor(); return; }
        else if (ch == KEY_BACKSPACE) { if (index > 0) { index--; printf("\b \b"); } } 
        else if (index < maxLen && ch >= 32 && ch <= 126) {
            buffer[index++] = (char)ch;
            if (isPassword) printf("*"); else printf("%c", ch);
        }
    }
    buffer[index] = '\0';
    hideCursor();
}

void inputInt(int x, int y, int *value, int maxLen) {
    char buffer[20];
    inputString(x, y, buffer, maxLen, 0); 
    if (strlen(buffer) > 0) *value = atoi(buffer); else *value = -1; 
}

#endif