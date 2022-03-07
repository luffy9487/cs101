
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void turn_number ( int a[], int n) {
	int tmp = 0;
	for (int i = 0; i < n; i++ ) {
    	for (int j = 0; j < i; j++ ) {
      		if (a[j] > a[i]) {
        		tmp = a[j];
        		a[j] = a[i];
        		a[i] = tmp;
      		}
    	}
  	}
}

int main()
{
    int a = 0, n = 5, tmp = 0;
    int s[70] = {0};
    srand((unsigned) time(NULL));
    time_t curtime;
    time(&curtime);
    FILE* fp;
    
    printf("請問您要買幾組樂透彩:");
    scanf("%d", &a);
    printf("以為您購買的%d組樂透彩組合輸出至 lotto.txt\n", a);
    fp = fopen("lotto.txt", "w+");
    fprintf(fp, "電腦為您選出的%d組樂透彩號碼\n", a);
    fprintf(fp, "%s", ctime(&curtime));
    for ( int i = 1; i <= 5; i++ ) {
        fprintf(fp, "[%d]:", i);
        if ( i > a) {
            for ( int i = 0; i <= n; i++ ) {
                fprintf(fp, "-- ");
            }
        } else {
            for ( int i = 0; i < 69; i++ ) {
                s[i] = i+1;
            }
            for ( int i = 0; i < 69; i++ ) {
                int r = rand() % 69, tmp = s[i];
                s[i] = s[r];
                s[r] = tmp;
            }
            turn_number(s, n);
            for ( int i = 0; i < n; i++ ) {
                fprintf(fp, "%0*d ", 2, s[i]);
            }
            for ( int i = 5; i < 70; i++ ) {
                if ( s[i] < 11 ) {
                    fprintf(fp, "%0*d\n", 2, s[i]);
                    break;
                }
            }
        }
    }
    fclose(fp);
    
    return 0;
}
