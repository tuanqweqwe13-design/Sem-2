#include <stdio.h>
#include <windows.h>

// Hàm dịch chuyển con trỏ
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void setColor(int foreground, int background) {
    WORD color = (background << 4) | foreground;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void get_console_center(int *x, int *y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *x = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
    *y = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
}

int main() {
    SetConsoleOutputCP(65001);

    int cx, cy;
    get_console_center(&cx, &cy);

    // 1. Vẽ chữ WELCOME màu đỏ (Red: 12)
    int welcomeY = cy - 8;
    gotoxy(cx - 28, welcomeY++); printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗");
    gotoxy(cx - 28, welcomeY++); printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝");
    gotoxy(cx - 28, welcomeY++); printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ");
    gotoxy(cx - 28, welcomeY++); printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ");
    gotoxy(cx - 28, welcomeY++); printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗");
    gotoxy(cx - 28, welcomeY++); printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝");

    // 2. Vẽ lời chào màu xanh lá (Green: 10)
    gotoxy(cx - 24, cy - 1);
    printf("Chao mung ban den voi he thong quan ly nha hang!");

// 3. Thanh Loading - SỬA LỖI Ở ĐÂY
    int width = 35;
    int startX = cx - (width / 2);
    int startY = cy + 2;

    for (int i = 0; i <= width; i++) {
        gotoxy(startX, startY);
        
        // Vẽ phần đã chạy (Nền trắng, in khoảng trắng)
        setColor(15, 15); 
        for (int j = 0; j < i; j++) printf(" ");
        
        // Vẽ phần còn lại (Nền xám, in khoảng trắng)
        setColor(8, 8); 
        for (int j = i; j < width; j++) printf(" ");

        // In phần trăm (Reset về nền đen để in chữ)
        setColor(7, 0);
        printf("] %d%%", (i * 100 / width));

        if (i % 3 == 0) Beep(750, 30);
        Sleep(60); 
    }
    Beep(800, 100); 
    Beep(1200, 200); // Tiếng sau cao hơn tiếng trước tạo cảm giác tích cực
  // 4. Nhấn Enter để tiếp tục (Màu trắng mặc định)
    setColor(7, 0); 
    gotoxy(startX + 5, startY + 2);
    printf("Nhan Enter de tiep tuc...");
    
    rewind(stdin);
    while (getchar() != '\n'); 

    // Xóa màn hình
    system("cls");
    printf("He thong da san sang!");

    return 0;
}
