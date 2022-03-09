
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int countf() {
    int n;
    FILE *fp;
    if ((fp = fopen("count.bin","rb+")) == NULL) {
        n = 0;
        fp = fopen("count.bin","wb");
        fwrite(&n,sizeof(int),1,fp);
        fclose(fp);
    }
    fp = fopen("count.bin","rb+");
    fread(&n,sizeof(int),1,fp);
    fclose(fp);

    n = n + 1;
    fp = fopen("count.bin","wb+");
    fwrite(&n,sizeof(int),1,fp);
    return n;
}

void namef(char name[],int c) {
    for (int i = 8; i >= 5; i--,c /= 10) {
        name[i] = (c%10+'0');
    }
}


int main() {
    
    int x;
    FILE* fp;
    time_t t;
    time(&t);
    printf("請問您要購買幾組樂透彩：");
    scanf("%d",&x);
    printf("已為您購買的%d組樂透組合輸出至 lotto.txt",x);
    
    int count = countf();
    char name[10] = "lotto";
    namef(name,count);
    int lotto[7];
    
    fp = fopen(name,"w+");
    fprintf(fp, "電腦為您選出的%d組樂透彩號碼\n", x);
    fprintf(fp,"========+ %0*d +=========\n",6,count);
    fprintf(fp,"=%.*s =\n",24,ctime(&t));
    srand(time(NULL));
    for (int k = 1; k <= 5; k++) {
        if (k > x) {
            fprintf(fp,"[%d]: -- -- -- -- -- -- --\n",k);
        } else {
            fprintf(fp,"[%d]: ",k);
            int a[70];
            
            int s = rand() % 10+1;
            for (int i = 0; i < 70; i++) {
                a[i] = i+1;
            }
    
            for (int i = 0; i < 69; i++) {
                int r = rand() % 69, tmp = a[i];
                a[i] = a[r];
                a[r] = tmp;
            }
    
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5-j; k++) {
                    if (a[k] > a[k+1]) {
                        int b = a[k];
                        a[k] = a[k+1];
                        a[k+1] = b;
                    }
                }
            }
    
            for(int i = 0; i <= 5; i++) {
                fprintf(fp,"%0*d ",2,a[i]);
            }
            for(int i = 6; i <= 68; i++) {
                if(a[i] < 11) {
                    fprintf(fp,"%0*d\n",2,a[i]);
                    break;
                }
            }
        }
    
    }
    fprintf(fp,"======== csie@CGU =========\n");

    return 0;
}