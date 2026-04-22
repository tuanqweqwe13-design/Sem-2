#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

// Cấu trúc để quản lý dữ liệu tài khoản
typedef struct {
    char username[30];
    char password[30];
    char role[10]; 
} Account;

// Hàm nhập mật khẩu ẩn dấu *
void inputPassword(char *pass) {
    char ch;
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) { // Phím Enter
            pass[i] = '\0';
            break;
        } else if (ch == 8) { // Phím Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (i < 29) {
            pass[i++] = ch;
            printf("*");
        }
    }
}

// Hàm kiểm tra đăng nhập từ file txt
// Trả về: 1 - Admin, 2 - Staff, 0 - Sai thông tin
int checkLogin(char *user, char *pass, char *roleOut) {
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL) {
        // Nếu không có file, tạo file mẫu để tránh lỗi
        f = fopen("accounts.txt", "w");
        fprintf(f, "admin 123 admin\nstaff 123 staff");
        fclose(f);
        f = fopen("accounts.txt", "r");
    }

    Account acc;
    // Đọc từng dòng: Tài khoản - Mật khẩu - Quyền
    while (fscanf(f, "%s %s %s", acc.username, acc.password, acc.role) != EOF) {
        if (strcmp(user, acc.username) == 0 && strcmp(pass, acc.password) == 0) {
            strcpy(roleOut, acc.role); 
            fclose(f);
            if (strcmp(acc.role, "admin") == 0) return 1;
            return 2; 
        }
    }
    fclose(f);
    return 0;
}

int main() {
    // Thiết lập tiếng Việt và ẩn con trỏ
    SetConsoleOutputCP(65001);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Hiện con trỏ để người dùng biết chỗ nhập
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    char user[30], pass[30], role[10];

    // Vòng lặp vô tận cho đến khi đăng nhập đúng
    while (1) {
        system("cls");
        printf("\n=========================================");
        printf("\n        ĐĂNG NHẬP HỆ THỐNG             ");
        printf("\n=========================================");
        
        printf("\n\nTài khoản: ");
        scanf("%s", user);
        
        printf("Mật khẩu : ");
        inputPassword(pass);

        int result = checkLogin(user, pass, role);

        if (result > 0) {
            printf("\n\n-----------------------------------------");
            printf("\nĐăng nhập thành công!");
            printf("\nQuyền hạn: %s", (result == 1) ? "QUẢN LÝ (ADMIN)" : "NHÂN VIÊN (STAFF) \n");
            
            Beep(1000, 200);
            
            if (result == 1) {
                printf(" \n Chào mừng Admin! \n");
            } else {
                printf(" \n Chào mừng Staff!\n");
            }
                printf("\n(Nhấn phím bất kỳ để tiếp tục...)");
                getch();
            break; // Thoát vòng lặp đăng nhập
        } else {
            printf("\n\n[!] Sai tài khoản hoặc mật khẩu. Vui lòng thử lại!");
            Beep(400, 400);
            Sleep(1000); // Đợi 1s để người dùng kịp đọc thông báo lỗi
        }
    }
        return 0;
}