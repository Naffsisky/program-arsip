#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data{
    char nama[50];
    char alamat[50];
    char no_telp[50];
    char email[50];
    struct Akun{
        char username[50];
        char password[50];
    } akun; 
}; typedef struct Data data;

struct Surat{
    char no_surat[50];
    char tanggal[50];
    char pengirim[50];
    char penerima[50];
    char perihal[50];
    char isi[50];
}; typedef struct Surat surat;

void menu();
void kirim();
void daftar_surat();
void login();
void regakun();
void profile();

int x = 1;

int main(x){
    int pilihan;
    while (x == 1){
        printf("--------------------------------------------\n");
        printf("Selamat Datang di Aplikasi Arsip Surat\n");
        printf("--------------------------------------------\n\n");
        printf("Silahkan Login Terlebih Dahulu\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n\n");
        printf("Masukan pilihan : ");
        scanf("%d", &pilihan);
        switch (pilihan){
            case 1:
                login();
                break;
            case 2:
                regakun();
                break;
            case 0:
                system("clear");
                printf("Terima Kasih Telah Menggunakan Aplikasi Ini\n");
                exit(0);
                break;
            default:
                system("clear");
                printf("Pilihan tidak ada!\n\n");
                main(x);
                break;
        }
    }
    exit(0);
}

void menu(){
    int pilihan;
    printf("--- Menu Utama ---\n");
    printf("1. Kirim Surat\n");
    printf("2. Daftar Surat\n");
    printf("9. Lihat Profile\n");
    printf("0. Logout\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);
    switch (pilihan){
        case 1:
            kirim();
            break;
        case 2:
            daftar_surat();
            break;
        case 9:
            profile();
            break;
        case 0:
            system("clear");
            main(x);
            break;
        default:
            printf("Pilihan tidak ada!\n\n");
            menu();
            break;
    }
}

void login(){
    char uname[50], pass[50];
    FILE *file;
    file = fopen("akun.txt", "r");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        exit(0);
    }
    data akun[100];
    int read = 0;
    int records = 0;
    do{
        read = fscanf(file, "%100[^,],%100[^,],%100[^,],%100[^,],%100[^,],%100[^\n]\n", akun[records].nama, akun[records].alamat, akun[records].no_telp, akun[records].email, akun[records].akun.username, akun[records].akun.password);
        if (read == 6){
            records++;
        }
        if (read != 6 && !feof(file)){
            printf("Format file salah!\n");
            exit(0);
        }
        if (ferror(file)){
            printf("Error memuat file!\n");
            exit(0);
        }
    } while (!feof(file));
    fclose(file);
    system("clear");
    printf("--- LOGIN ---\n");
    printf("Masukan username : ");
    fflush(stdin);
    gets(uname);
    printf("Masukan password : ");
    fflush(stdin);
    gets(pass);
    back:
    for (int i = 0; i < records; i++){
        if (strcmp(uname, akun[i].akun.username) == 0 && strcmp(pass, akun[i].akun.password) == 0){
            system("clear");
            printf("Login Berhasil!\n\n");
            printf("Selamat Datang %s\n\n", akun[i].nama);
            menu();
        }
    }
    goto back;
    system("clear");
    printf("\n\nUsername atau Password Salah!\n\n");
    main(x);
}

void regakun(){
    FILE *file;
    file = fopen("akun.txt", "a");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        exit(0);
    }
    data akun;
    system("clear");
    printf("--- DAFTAR AKUN ---\n");
    printf("Masukan Nama : ");
    fflush(stdin);
    gets(akun.nama);
    printf("Masukan Alamat : ");
    fflush(stdin);
    gets(akun.alamat);
    printf("Masukan No Hp : ");
    fflush(stdin);
    gets(akun.no_telp);
    printf("Masukan E-mail : ");
    fflush(stdin);
    gets(akun.email);
    printf("Masukan Username : ");
    fflush(stdin);
    gets(akun.akun.username);
    printf("Masukan Password : ");
    gets(akun.akun.password);
    fprintf(file, "\n%s,%s,%s,%s,%s,%s", akun.nama, akun.alamat, akun.no_telp, akun.email, akun.akun.username, akun.akun.password);
    fclose(file);
    system("clear");
    printf("Register Berhasil!\n\n");
    login();
}

void kirim(){
    FILE *file;
    file = fopen("daftarsurat.txt", "a");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        exit(0);
    }
    surat surat;
    printf("Masukan No Surat : ");
    fflush(stdin);
    gets(surat.no_surat);
    printf("Masukan Tanggal : ");
    fflush(stdin);
    gets(surat.tanggal);
    printf("Masukan Pengirim : ");
    fflush(stdin);
    gets(surat.pengirim);
    printf("Masukan Penerima : ");
    fflush(stdin);
    gets(surat.penerima);
    printf("Masukan Perihal : ");
    fflush(stdin);
    gets(surat.perihal);
    printf("Masukan Isi : ");
    fflush(stdin);
    gets(surat.isi);
    fprintf(file, "\n%s, %s, %s, %s, %s, %s", surat.no_surat, surat.tanggal, surat.pengirim, surat.penerima, surat.perihal, surat.isi);
    fclose(file);
    system("clear");
    printf("Surat Berhasil Dikirim!\n");
    menu();
}

void daftar_surat(){
    FILE *file;
    file = fopen("daftarsurat.txt", "r");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        exit(0);
    }
    surat surat[100];
    int read = 0;
    int records = 0;
    do{
        read = fscanf(file, "%100[^,],%100[^,],%100[^,],%100[^,],%100[^,],%100[^\n]\n", surat[records].no_surat, surat[records].tanggal, surat[records].pengirim, surat[records].penerima, surat[records].perihal, surat[records].isi);
        if (read == 6){
            records++;
        }
        if (read != 6 && !feof(file)){
            printf("Format file salah!\n");
            exit(0);
        }
        if (ferror(file)){
            printf("Error memuat file!\n");
            exit(0);
        }
    } while (!feof(file));
    fclose(file);
    printf("No Surat\tTanggal\t\tPengirim\tPenerima\tPerihal\t\tIsi\n");
    for (int i = 0; i < records; i++){
        printf("%s\t\t%s\t%s\t%s\t%s\t%s\n", surat[i].no_surat, surat[i].tanggal, surat[i].pengirim, surat[i].penerima, surat[i].perihal, surat[i].isi);
    }
    if (records == 0){
        printf("Tidak ada surat yang dikirim\n");
    }
    menu();
}

void profile(){
    FILE *file;
    file = fopen("akun.txt", "r");
    if (file == NULL){
        printf("File tidak ditemukan\n");
        exit(0);
    }
    data akun[100];
    int read = 0;
    int records = 0;

    do{
        read = fscanf(file, "%100[^,],%100[^,],%100[^,],%100[^,],%100[^,],%100[^\n]\n", akun[records].nama, akun[records].alamat, akun[records].no_telp, akun[records].email, akun[records].akun.username, akun[records].akun.password);
        if (read == 6){
            records++;
        }
        if (read != 6 && !feof(file)){
            printf("Format file salah!\n");
            exit(0);
        }
        if (ferror(file)){
            printf("Error memuat file!\n");
            exit(0);
        }
    } while (!feof(file));
    fclose(file);
    printf("--- DATA DIRI ---\n");
    for (int i = 0; i < records; i++){
        printf("Nama : %s\n", akun[i].nama);
    }
    for (int i = 0; i < records; i++){
        printf("Alamat : %s\n", akun[i].alamat);
    }
    for (int i = 0; i < records; i++){
        printf("No Hp : %s\n", akun[i].no_telp);
    }
    for (int i = 0; i < records; i++){
        printf("E-mail : %s\n", akun[i].email);
    }
    for (int i = 0; i < records; i++){
        printf("Username : %s\n", akun[i].akun.username);
    }
    for (int i = 0; i < records; i++){
        printf("Password : %s\n", akun[i].akun.password);
    }
    menu();
}
