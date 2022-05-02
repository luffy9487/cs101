#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

int userf(int n[],int a) {
    FILE *fp;
    fp = fopen("user.bin","wb+");
    fprintf(fp,"user_");
    fwrite(&n[a],sizeof(int),1,fp);
    fclose(fp);

}

void namef(char name[],int c) {
    for (int i = 8; i >= 5; i--,c /= 10) {
        name[i] = (c%10+'0');
    }
}



int main() {
    
    int x,d;
    int n[6] = {'0','1','2','3','4','5'};
    FILE* fp;
    time_t t;
    time(&t);
    int count = countf();
    char name[10] = "lotto";
    namef(name,count);
    int lotto[7];
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請輸入操作人員ID:(0-5):");
    scanf("%d",&d);
    printf("請問您要購買幾組樂透彩：");
    scanf("%d",&x);
    printf("已為您購買的%d組樂透組合輸出至 lotto%05d",x,count);
    userf(n,d);
    fp = fopen(name,"w+");
    fprintf(fp,"======== lotto649 =========\n");
    fprintf(fp,"========+ No.%0*d +=========\n",3,count);
    fprintf(fp,"=%.*s =\n",24,ctime(&t));
    srand(time(NULL));
    
    char szbuff[32],szbuff2[32];
    time_t now = time(0);
    strftime(szbuff,100,"%Y%m%d",localtime(&now));
    strftime(szbuff2,100,"%H:%M:%S",localtime(&now));
    
    FILE* fp2;
    if ((fp2 = fopen("records.bin","r"))==NULL) {
        fp2 = fopen("records.bin", "wb");
	    fclose(fp2);
    }
    
    
    typedef struct lotto_record_t {
        int lotto_no;
        int lotto_receipt;
        int emp_id;
        char lotto_date[32];
        char lotto_time[32];
    } typelotto;
    
    typelotto lo_i;
    lo_i.lotto_no=count;
    lo_i.lotto_receipt=count*50*1.1;
    lo_i.emp_id=d;
    strcpy(lo_i.lotto_date,szbuff);
    strcpy(lo_i.lotto_time,szbuff2);
    
    fp2 =fopen("recoeds.bin","ab");
    fwrite(&lo_i,sizeof(lo_i),1,fp2);
    fclose(fp2);
    
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
    fprintf(fp,"========* OP.%0*d *========\n",3,d);
    fprintf(fp,"======== csie@CGU =========\n");
    return 0;
}
