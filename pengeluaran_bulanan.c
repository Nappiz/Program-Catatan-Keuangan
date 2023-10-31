#include <stdio.h>
#include <string.h>

float konversiK(const char *K) {
    int pengali = 1;
    float value = 0;
    int len = strlen(K);

    for (int i = 0; i < len; i++) {
        if (K[i] == 'k' || K[i] == 'K') {
            pengali = 1000;
        } else if (K[i] >= '0' && K[i] <= '9') {
            value = value * 10 + (K[i] - '0');
        }
    }
    return value * pengali;
}

int main(){
    float uang;
    int jumlah_hari;
    float total_pengeluaran = 0;

    int urutanData = 1; //yang ada file nya untuk ngubah output ke data file
    FILE *urutanFile = fopen("urutan.txt", "r");
    if (urutanFile) {
        fscanf(urutanFile, "%d", &urutanData);
        fclose(urutanFile);
    }

    char fileName[20];
    sprintf(fileName, "data%d.txt", urutanData);
    
    FILE *file = fopen(fileName, "r");
    if (file) {
        fscanf(file, "%f", &total_pengeluaran);
        fscanf(file, "%f", &uang);
        fclose(file);
    }

    printf("Saldo awal: "); //ngitung uang
    char uangKeluar[20];
    scanf("%s", uangKeluar);
    uang = konversiK(uangKeluar);

    printf("Jumlah hari: ");
    scanf("%d", &jumlah_hari);

    file = fopen(fileName, "a");
    fprintf(file, "Saldo awal: %.2f\n", uang);
    fprintf(file, "Jumlah hari: %d\n", jumlah_hari);

    for(int hari = 1; hari <= jumlah_hari; hari++){
        printf("Hari ke-%d\n", hari);
        fprintf(file, "Hari ke-%d\n", hari);
        float total_hari = 0;

        for(char hal = 'a'; hal <= 'e'; hal++){
            char K[20];
            if(hal == 'a'){
                printf("Makan pagi: ");
            }else if(hal == 'b'){
                printf("Makan siang: ");
            }else if(hal == 'c'){
                printf("Makan malam: ");
            }else if(hal == 'd'){
                printf("Jajan: ");
            }else if(hal == 'e'){
                printf("Lainnya: ");
            }

            scanf("%s", K);
            float nilai = konversiK(K);
            total_hari += nilai;

            printf("%c: %.2f\n", hal, nilai);
            fprintf(file, "%c: %.2f\n", hal, nilai);
        }

        total_pengeluaran = total_hari + total_pengeluaran;
        printf("Total pengeluaran pada hari ke-%d: %.2f\n", hari, total_hari);
        fprintf(file, "Total pengeluaran pada hari ke-%d: %.2f\n", hari, total_hari);
    }
    
    printf("Uang tambahan: ");
    char uangTambahan[20];
    scanf("%s", uangTambahan);
    float uangAkhir = konversiK(uangTambahan);

    uangAkhir = uang + uangAkhir;

    float sisa_uang = uang - total_pengeluaran;

    printf("Uang tambahan: %.2f\n", uangAkhir);
    fprintf(file, "Uang tambahan: %.2f\n", uangAkhir);
    printf("Total pengeluaran bulan ini: %.2f\n", total_pengeluaran);
    fprintf(file, "Total pengeluaran bulan ini: %.2f\n", total_pengeluaran);
    printf("Uangmu sisa: %.2f\n", sisa_uang);
    fprintf(file, "Uangmu sisa: %.2f\n", sisa_uang);
    
    fclose(file); //ini kebawah output file

    urutanData++;
    urutanFile = fopen("urutan.txt", "w");
    fprintf(urutanFile, "%d", urutanData);
    fclose(urutanFile);

    return 0;
}