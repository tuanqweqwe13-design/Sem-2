#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define MAX 36
#define MAX_CHON 5
#define MAX_DON 100

char dsachtenmon[MAX][50] = {
    "Pho Bo Tai Lan","Bun Cha Ha Noi","Bun Bo Hue","Vit Quay Bac Kinh","Nem Ran","Goi Cuon",
    "Mien Ga","Com Chien","My Cay","Lau Thai","Ga Xao","Muc Hap",
    "Bo Luc Lac","Ca Kho","Com Tam",
    "Rau Muong","Canh Kho Qua","Ca Phao","Dau Hu","Nom","Kim Chi",
    "Khoai Tay","Khoai Nghien","Mang Tay","Salad",
    "Bia","Tra Dao","Ruou","Tra Chanh","Coca","Nuoc Suoi"
};

float dsachgiamon[MAX] = {
    75000,65000,85000,450000,55000,50000,
    95000,110000,95000,550000,125000,185000,
    165000,145000,65000,
    45000,55000,30000,45000,40000,65000,
    55000,35000,45000,40000,
    15000,15000,120000,50000,35000,45000
};

char dsachma[MAX][5] = {
    "1A","2A","3A","4A","5A","6A","7A","8A","9A","10A","11A","12A","13A","14A","15A",
    "1B","2B","3B","4B","5B","6B","7B","8B","9B","10B",
    "1C","2C","3C","4C","5C","6C"
};

typedef struct {
    char username[30];
    char password[30];
    char role[10]; 
} Account;

char maGD[MAX_DON][20];
long tongTienDon[MAX_DON];
int soDon = 0;
int soMon = 31;
int thongKeMon[MAX] = {0};
char maNgayDon[MAX_DON][20];

//========================Nguyên mẫu hàm========================
//hàm chung
void gotoxy(int x, int y); // hàm đẩy chuột
void setColor(int foreground, int background); // hàm chỉnh màu
void get_console_center(int *x, int *y); // hàm căn giữa
//hàm loading + login
void loading ();
int login();
void inputPassword(char *pass);
int checkLogin(char *user, char *pass, char *roleOut);
// hàm chính nè
    // in menu và hóa đơn
void menu();
void inHoaDonTamTinh(int maMon[], int soLuong[], int n);
long inHoaDon(int maMon[], int soLuong[], int n, char ghiChuDon[]);
void capNhatThongKe(int maMon[], int soLuong[], int n);
    // hàm đặt món + xóa món khi đặt
long datMon();
    // thống kê món đặt + quản lý món khi đặt 
void monBanNhieuNhat();
void timTheoMaNgay();
void bangXepHang();
void thongKe();
    // quản lý món
void xemDanhSachMon();
void themMon();
void xoaMon();
void suaGiaMon();
void quanLyMon();
    //ghi vòa file 
void ghiFile();


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    int chon;
    char ma[20], maNgay[20];
    int userPermission = login();
// phần menuloading 
    loading ();
    system("cls");

// phần đăng nhập 
    login ();
    system("cls");

// phần menu chính 
    printf("Nhập mã ngày: ");
    scanf("%s", maNgay);

    do {
        printf("\n+===========================================+\n");
        printf("|          MENU CHÍNH                         |\n");
        printf("+=============================================+\n");
        printf("| 1. Đặt món                                  |\n");
        printf("| 2. Quản lý món (admin only)                 |\n");
        printf("| 3. Tìm theo mã ngày (admin only)            |\n");
        printf("| 4. Bảng xếp hạng món ăn (admin only)        |\n");
        printf("| 0. Kết thúc                                 |\n");
        printf("+=============================================+\n");
        printf("Chọn: ");
        scanf("%d", &chon);
        system ("cls");

    if(chon == 1){

        if (soDon >= MAX_DON) {
            printf("Đã đạt giới hạn đơn hàng!\n");
            continue;}

        menu();

        while (1) {

            printf("\nNhập mã giao dịch : ");
            scanf("%s", ma);

            if (strcmp(ma, maNgay) == 0) {
                printf(">>> Đã nhập MÃ NGÀY. Thoát chế độ đặt món!\n");
                break;
            }

            int trung = 0;
            for(int i = 0; i < soDon; i++){
                if(strcmp(maGD[i], ma) == 0){
                    trung = 1;
                    break;
                }
            }

            if(trung){
                printf("Mã giao dịch bị trùng! Nhập lại.\n");
                continue;
            }

            strcpy(maGD[soDon], ma);
            strcpy(maNgayDon[soDon], maNgay);

            long tong = datMon();

            tongTienDon[soDon] = tong;
            soDon++;

            printf("\n>>> Đặt xong 1 đơn. Tiếp tục hoặc nhập MÃ NGÀY (%s) để thoát.\n",maNgay);

            if (soDon >= MAX_DON) {
                printf("Đã đạt giới hạn đơn hàng!\n");
                break;
            }
        }
    }

        else if(chon == 2 && userPermission == 1){
            quanLyMon(); 
            system("cls");
        }

        else if(chon == 3 && userPermission == 1){
            timTheoMaNgay();      
            system("cls");

        }
        else if (chon==4 && userPermission == 1){
            bangXepHang();
            system("cls");

        }
        else if (chon==1 && userPermission == 2 || chon == 2 && userPermission == 2 || chon == 3 && userPermission == 2 || chon == 4 && userPermission == 2){
            printf ("Bạn không có quyền này, hãy chọn lại!");
            system("cls");
            continue;
        }

    } while(chon != 0);
    
    system("cls");
    thongKe();
    monBanNhieuNhat();
    ghiFile();

    return 0;
}

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
void loading (){
    int cx, cy;
    get_console_center(&cx, &cy);

    int welcomeY = cy - 8;
    gotoxy(cx - 28, welcomeY++); printf("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗");
    gotoxy(cx - 28, welcomeY++); printf("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝");
    gotoxy(cx - 28, welcomeY++); printf("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  ");
    gotoxy(cx - 28, welcomeY++); printf("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  ");
    gotoxy(cx - 28, welcomeY++); printf("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗");
    gotoxy(cx - 28, welcomeY++); printf(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝");

    gotoxy(cx - 24, cy - 1);
    printf("Chao mung ban den voi he thong quan ly nha hang!");

    int width = 35;
    int startX = cx - (width / 2);
    int startY = cy + 2;

    for (int i = 0; i <= width; i++) {
        gotoxy(startX, startY);
        
        setColor(15, 15); 
        for (int j = 0; j < i; j++) printf(" ");
        
        setColor(8, 8); 
        for (int j = i; j < width; j++) printf(" ");

        setColor(7, 0);
        printf("] %d%%", (i * 100 / width));

        if (i % 3 == 0) Beep(750, 30);
        Sleep(60); 
    }
    Beep(800, 100); 
    Beep(1200, 200); 
    setColor(7, 0); 
    gotoxy(startX + 5, startY + 2);
    printf("Nhan Enter de tiep tuc...");
    rewind(stdin);
    while (getchar() != '\n'); 
}
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
int checkLogin(char *user, char *pass, char *roleOut) {
    int role1 = 0 ;
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL) {
        f = fopen("accounts.txt", "w");
        fprintf(f, "admin 123 admin\nstaff 123 staff");
        fclose(f);
        f = fopen("accounts.txt", "r");
    }

    Account acc;
    while (fscanf(f, "%s %s %s", acc.username, acc.password, acc.role) != EOF) {
        if (strcmp(user, acc.username) == 0 && strcmp(pass, acc.password) == 0) {
            strcpy(roleOut, acc.role); 
            fclose(f);
            if (strcmp(acc.role, "admin") == 0) {role1 = 1; return 1;}
            if (strcmp(acc.role, "staff") == 0) {role1 = 2; return 2;}
            return 3; 
        }
    }
    fclose(f);
    return role1;
}
int login(){
    SetConsoleOutputCP(65001);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; 
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    char user[30], pass[30], role[10];
    int cx, cy;
    get_console_center(&cx, &cy);
    int permission;
    while (1) {
        system("cls");
        int welcomeY = cy - 8;
        gotoxy(cx - 27, welcomeY++); printf("██╗      ██████╗  ██████╗ ██╗███╗   ██╗");
        gotoxy(cx - 27, welcomeY++); printf("██║     ██╔═══██╗██╔════╝ ██║████╗  ██║");
        gotoxy(cx - 27, welcomeY++); printf("██║     ██║   ██║██║  ███╗██║██╔██╗ ██║");
        gotoxy(cx - 27, welcomeY++); printf("██║     ██║   ██║██║   ██║██║██║╚██╗██║");
        gotoxy(cx - 27, welcomeY++); printf("███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║");
        gotoxy(cx - 27, welcomeY++); printf("╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝");        
        
        printf("\n\nTài khoản: ");
        scanf("%s", user);

        printf("Mật khẩu : ");
        inputPassword(pass);

        permission = checkLogin(user, pass, role);

        if (permission > 0) {
            printf("\n\n-----------------------------------------");
            printf("\nĐăng nhập thành công!");
            printf("\nQuyền hạn: %s", (permission == 1) ? "QUẢN LÝ (ADMIN)" : "NHÂN VIÊN (STAFF) \n");
            
            Beep(1000, 200);
            
            if (permission == 1 ) {
                printf(" \n Chào mừng Admin! \n");
            } else {
                printf(" \n Chào mừng Staff!\n");
            }
                printf("\n(Nhấn phím bất kỳ để tiếp tục...)");
                getch();
            break; 
        } else {
            printf("\n\n[!] Sai tài khoản hoặc mật khẩu. Vui lòng thử lại!");
            Beep(400, 400);
            Sleep(1000); 
        }
    }
    return permission;
}
// Hàm cho menu
void menu() {
    printf("\n");
    printf("+===========================================================================================================+\n");
    printf("|                                BK RESTAURANT                                                              |\n");
    printf("|                            THUC DON NHA HANG                                                              |\n");
    printf("+===========================================================================================================+\n");
    printf("|                              A. MON CHINH                                                                 |\n");
    printf("+===========================================================================================================+\n");

    int dem = 0;
    for(int i = 0; i < soMon; i++){
        if(dsachma[i][strlen(dsachma[i]) - 1] == 'A'){

            if(dem % 3 == 0) printf("|");

            printf(" %-3s %-20s %8.0f |",
                   dsachma[i], dsachtenmon[i], dsachgiamon[i]);

            dem++;

            if(dem % 3 == 0) printf("\n");
        }
    }
    if(dem % 3 != 0) printf("\n");

    printf("+===========================================================================================================+\n");
    printf("|                              B. MON PHU                                                                   |\n");
    printf("+===========================================================================================================+\n");

    dem = 0;
    for(int i = 0; i < soMon; i++){
        if(dsachma[i][strlen(dsachma[i]) - 1] == 'B'){

            if(dem % 3 == 0) printf("|");

            printf(" %-3s %-20s %8.0f |",
                   dsachma[i], dsachtenmon[i], dsachgiamon[i]);

            dem++;

            if(dem % 3 == 0) printf("\n");
        }
    }
    if(dem % 3 != 0) printf("\n");

    printf("+===========================================================================================================+\n");
    printf("|                              C. MON NUOC                                                                  |\n");
    printf("+===========================================================================================================+\n");

    dem = 0;
    for(int i = 0; i < soMon; i++){
        if(dsachma[i][strlen(dsachma[i]) - 1] == 'C'){

            if(dem % 3 == 0) printf("|");

            printf(" %-3s %-20s %8.0f |",
                   dsachma[i], dsachtenmon[i], dsachgiamon[i]);

            dem++;

            if(dem % 3 == 0) printf("\n");
        }
    }
    if(dem % 3 != 0) printf("\n");

    printf("+===========================================================================================================+\n");
    printf("|                 * Tren 2 trieu giam 25%%                                                                   |\n");
    printf("+===========================================================================================================+\n");
}
void inHoaDonTamTinh(int maMon[], int soLuong[], int n) {
    long tamTinh = 0;

    printf("\n+=====================================================+\n");
    printf("|                HOA DON TAM TINH                     |\n");
    printf("+=====================================================+\n");
    printf("| %-25s | %-5s | %-15s |\n", "TEN MON", "SL", "THANH TIEN");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < n; i++) {
        long thanhTien = (long)dsachgiamon[maMon[i]] * soLuong[i];
        tamTinh += thanhTien;

        printf("| %-25s | %-5d | %-15ld |\n",
               dsachtenmon[maMon[i]],
               soLuong[i],
               thanhTien);
    }

    printf("+-----------------------------------------------------+\n");
    printf("| %-25s | %-5s | %-15ld |\n", "TONG TAM TINH", "", tamTinh);
    printf("+=====================================================+\n");

    if (tamTinh >= 2000000)
        printf(">>> DA DU DIEU KIEN GIAM GIA 25%%\n");

    printf("+=====================================================+\n\n");
}
long inHoaDon(int maMon[], int soLuong[], int n, char ghiChuDon[]) {
    long tong = 0;
    float chietkhau = 0;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    printf("\n+===========================================================+\n");
    printf("|                    HOA DON BAN HANG                       |\n");
    printf("+===========================================================+\n");

    printf("| Ngay: %02d/%02d/%04d  Gio: %02d:%02d:%02d                           |\n",
           tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

    printf("+----+---------------------------+-------+------------------+\n");
    printf("| STT| TEN MON                   |  SL   |   THANH TIEN     |\n");
    printf("+----+---------------------------+-------+------------------+\n");

    for (int i = 0; i < n; i++) {
        long tien = (long)dsachgiamon[maMon[i]] * soLuong[i];
        tong += tien;

        printf("| %-3d| %-25s | %-5d | %-16ld |\n",
               i + 1,
               dsachtenmon[maMon[i]],
               soLuong[i],
               tien);
    }

    printf("+----+---------------------------+-------+------------------+\n");
    printf("| %-30s | %-24ld |\n", "TONG TIEN", tong);
    printf("+===========================================================+\n");

    printf("| Ghi chu: %-48s |\n", ghiChuDon);
    printf("+===========================================================+\n");

    if (tong >= 2000000) {
        chietkhau = 0.25;
        long giam = tong * chietkhau;

        printf("| Giam gia (25%%): %-37ld |\n", giam);
        tong -= giam;
    } else {
        printf("| Giam gia: 0%%%-46s|\n", "");
    }

    printf("| THANH TOAN: %-45ld |\n", tong);
    printf("+===========================================================+\n");

    long tienDua;
    do {
        printf("| Khach dua:");
        scanf("%ld", &tienDua); 
        if (tienDua < tong)
            printf("Khong du tien, nhap lai!\n");

    } while (tienDua < tong);

    printf("| Tien thoi: %-46ld |\n", tienDua - tong);
    printf("+===========================================================+\n");
    printf("|        CAM ON QUY KHACH - HEN GAP LAI!                    |\n");
    printf("+===========================================================+\n");
    return tong;
}
void capNhatThongKe(int maMon[], int soLuong[], int n){
    for(int i = 0; i < n; i++){
        thongKeMon[maMon[i]] += soLuong[i];
    }
}
long datMon() {
    char ma[5];
    int sl;
    int maMon[MAX_CHON];
    int soLuong[MAX_CHON];
    char ghiChuDon[200];
    int n = 0;

    while (1) {
    printf("Nhập mã món + số lượng (0 0 để chốt, MA 0 để xóa): ");
    scanf("%s %d", ma, &sl);

    if (strcmp(ma,"0")==0 && sl==0) break;

    int idx = -1;
    for(int i=0;i<soMon;i++){
        if(strcmp(ma, dsachma[i])==0){
            idx = i;
            break;
        }
    }

    if(idx == -1){
        printf("Sai mã món!\n");
        continue;
    }
    if(sl < 0 || sl > 1000){
        printf("Số lượng không hợp lý!\n");
        continue;
    }

    int viTriTrongGio = -1;
    for(int i=0;i<n;i++){
        if(maMon[i] == idx){
            viTriTrongGio = i;
            break;
        }
    }

    if(sl == 0){
        if(viTriTrongGio != -1){

            for(int i=viTriTrongGio;i<n-1;i++){
                maMon[i] = maMon[i+1];
                soLuong[i] = soLuong[i+1];
            }
            n--;
            printf("Đã xóa món!\n");
        } else {
            printf("Món chưa có để xóa!\n");
        }
        continue;
    }

    
    if(viTriTrongGio != -1){
        
        soLuong[viTriTrongGio] = sl;
        
        printf("Đã cập nhật!\n");
    }
   
    else {
    if(n < MAX_CHON){
        maMon[n] = idx;
        soLuong[n] = sl;
        n++;

        printf("Đã thêm món!\n");

        if(n == MAX_CHON){
            printf("Đã đạt tối đa 5 món .Chốt đơn ! \n");
            break;
        }
    } else {
        printf("Giỏ hàng đầy!\n");
        break;
    }
}
    if(n > 0) inHoaDonTamTinh(maMon, soLuong, n);
}
    getchar(); 
    printf("Nhập ghi chú cho đơn (Enter để bỏ qua): ");
    fgets(ghiChuDon, 200, stdin);
    ghiChuDon[strcspn(ghiChuDon, "\n")] = 0;

    long tong =inHoaDon(maMon,soLuong,n,ghiChuDon);
    capNhatThongKe(maMon,soLuong,n); 

return tong;
}
void monBanNhieuNhat() {
    int max = 0, idx = -1;

    for(int i=0;i<soMon;i++){
        if(thongKeMon[i] > max){
            max = thongKeMon[i];
            idx = i;
        }
    }

    if(idx != -1){
        printf("\nMón bán nhiều nhất: %s (%d lượt)\n",
               dsachtenmon[idx], max);
    }
}
void xemDanhSachMon() {

    printf("\n");
    printf("======================== DANH SACH MON AN====================\n");
    

    printf("+------+--------------------------------+-------------------+\n");
    printf("| %-4s | %-30s | %-17s |\n",
           "MA", "TEN MON", "GIA");
    printf("+------+--------------------------------+-------------------+\n");

    for(int i = 0; i < soMon; i++) {

        printf("| %-4s | %-30s | %-17.0f |\n",
               dsachma[i],
               dsachtenmon[i],
               dsachgiamon[i]);
    }

    printf("+------+--------------------------------+-------------------+\n");
    printf("| %-37s | %-17d |\n",
           "TONG SO MON",
           soMon);
    printf("+----------------------------------------+-------------------+\n");
}
void themMon() {

    if(soMon >= MAX){
        printf("Danh sách đầy!\n");
        return;
    }

    char ma[10];
    char ten[50];
    int i;
    int trung;

    do {
        trung = 0;

        printf("Nhập mã món: ");
        scanf("%s", ma);

        for(i = 0; i < soMon; i++){
            if(strcmp(dsachma[i], ma) == 0){
                trung = 1;
                printf("Mã bị trùng! Nhập lại.\n");
                break;
            }
        }

    } while(trung == 1);

    getchar();

    do {
        trung = 0;

        printf("Nhập tên món: ");
        fgets(ten, 50, stdin);
        ten[strcspn(ten, "\n")] = 0;

        for(i = 0; i < soMon; i++){
            if(strcmp(dsachtenmon[i], ten) == 0){
                trung = 1;
                printf("Tên bị trùng! Nhập lại.\n");
                break;
            }
        }

    } while(trung == 1);

    do {
        printf("Nhập giá: ");
        scanf("%f", &dsachgiamon[soMon]);

        if(dsachgiamon[soMon] < 0){
            printf("Giá không hợp lệ! Nhập lại.\n");
        }

    } while(dsachgiamon[soMon] < 0);

    strcpy(dsachma[soMon], ma);
    strcpy(dsachtenmon[soMon], ten);

    soMon++;

    printf("Thêm món thành công!\n");
}
void xoaMon() {

    char ma[10];
    int i, pos = -1;

    printf("Nhap mã món cần xóa: ");
    scanf("%s", ma);

    for(i = 0; i < soMon; i++){
        if(strcmp(dsachma[i], ma) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("Không tìm thấy món!\n");
        return; 
    }

    for(i = pos; i < soMon - 1; i++){
        strcpy(dsachma[i], dsachma[i+1]);
        strcpy(dsachtenmon[i], dsachtenmon[i+1]);
        dsachgiamon[i] = dsachgiamon[i+1];
    }

    soMon--;

    printf("Đã xóa món!\n");
}
void suaGiaMon() {

    char ma[5];
    int i;
    int found;

    do {
        found = 0;

        printf("Nhap mã món: ");
        scanf("%s", ma);

        for(i = 0; i < soMon; i++){
            if(strcmp(ma, dsachma[i]) == 0){

                printf("Gia mới: ");
                scanf("%f", &dsachgiamon[i]);

                printf("Đã cập nhật!\n");

                found = 1;
                break;
            }
        }

        if(found == 0){
            printf("Không tìm thấy món! Nhập lại.\n");
        }

    } while(found == 0);
}
void quanLyMon() {
    int chon;

    do {
        printf("\n+================================+\n");
        printf("|        QUẢN LÝ MÓN ĂN         |\n");
        printf("+================================+\n");
        printf("| 1. Xem danh sách món           |\n");
        printf("| 2. Thêm món                    |\n");
        printf("| 3. Xóa món                     |\n");
        printf("| 4. Sửa giá món                 |\n");
        printf("| 0. Quay về                     |\n");
        printf("+================================+\n");
        printf("Chọn: ");
        scanf("%d", &chon);

        if(chon == 1){
            xemDanhSachMon();
        }
        else if(chon == 2){
             themMon();
        }
        else if(chon == 3){
           xoaMon();
}
else if(chon == 4){
            suaGiaMon();
            }

    } while(chon != 0);
}
void timTheoMaNgay() {
    char maNgay[20];
    printf("Nhập mã ngày cần tìm: ");
    scanf("%s", maNgay);

    int found = 0;
    long tong = 0;

    printf("\n===== ĐƠN HÀNG NGÀY %s =====\n", maNgay);

    for(int i=0;i<soDon;i++){
        if(strcmp(maNgayDon[i], maNgay) == 0){
            printf("Mã GD: %s - Tổng: %ld VND\n",
                   maGD[i], tongTienDon[i]);
            tong += tongTienDon[i];
            found = 1;
        }
    }

    if(!found){
        printf("Không có đơn!\n");
    } else {
        printf("Tổng doanh thu: %ld VND\n", tong);
    }
}
void bangXepHang() {
    long doanhThu[MAX];

    printf("\n");
    printf("=========================BẢNG XẾP HẠNG MÓN ĂN=============================\n");

    printf("+-----+------------------------------+---------------+-------------------+\n");
    printf("| %-3s | %-28s | %-13s | %-17s |\n",
           "TOP", "TEN MON", "LUOT DAT", "DOANH THU");
    printf("+-----+------------------------------+---------------+-------------------+\n");

    for(int i = 0; i < soMon; i++) {
        doanhThu[i] = thongKeMon[i] * dsachgiamon[i];
    }

    int daXet[MAX] = {0};

    for(int top = 0; top < soMon; top++) {

        int idx = -1;
        long max = -1;

        for(int i = 0; i < soMon; i++) {
            if(!daXet[i] && doanhThu[i] > max) {
                max = doanhThu[i];
                idx = i;
            }
        }

        if(idx == -1 || doanhThu[idx] == 0)
            break;

        printf("| %-3d | %-28s | %-13d | %-17ld |\n",
               top + 1,
               dsachtenmon[idx],
               thongKeMon[idx],
               doanhThu[idx]);

        daXet[idx] = 1;
    }

    printf("+-----+------------------------------+---------------+-------------------+\n");

    int tongLuot = 0;
    long tongTien = 0;

    for(int i = 0; i < soMon; i++) {
        tongLuot += thongKeMon[i];
        tongTien += doanhThu[i];
    }

    printf("| %-34s | %-13d | %-17ld |\n",
           "TONG",
           tongLuot,
           tongTien);

    printf("+----------------------------------------------------+-------------------+\n");
}
void thongKe() {
    printf("\n===== Thống Kê Đơn Hàng =====\n");

    for(int i=0;i<soDon;i++) {
        printf("%d. Mã GD: %s - Tổng tiền: %ld VND\n",
               i+1,maGD[i],tongTienDon[i]);
    }
}
void ghiFile() {
    FILE *f;
    f = fopen("donhang.txt", "a+");
    if(f == NULL) {
        printf("Không mở được file!\n");
        return;
    }

    fprintf(f,"THỐNG KÊ ĐƠN HÀNG TRONG NGÀY\n");

    for(int i=0;i<soDon;i++) {
        fprintf(f,"%d. Mã GD: %s - Tổng: %ld VND\n",
                i+1,maGD[i],tongTienDon[i]);
    }
    int max = 0, idx = -1;
    for(int i=0;i<soMon;i++){
        if(thongKeMon[i] > max){
            max = thongKeMon[i];
            idx = i;
        }
    }

    if(idx != -1){
        fprintf(f,"Món bán chạy nhất  : %s (%d)\n", dsachtenmon[idx], max);
    }

    fclose(f);
}
