
#include <stdio.h>

void p_addressvalue(int* p, int x) {
    for(int i = 0; i < 10; i++) {
		if(*(p + i) == x) {
			printf("&n[%d]->%p, n[%d] = %d, ", i, p, i, *(p + i));
			printf("p->%p, *p = %d\n", p, *(p + i));
		}
	}
}

void sort(int** ap) {
	for(int i = 0; i < 10; i++) {
		for(int j = i + 1; j < 10; j++) {
			if(*ap[i] > *ap[j]) {
				int* temp = ap[i];
				ap[i] = ap[j];
				ap[j] = temp;
			}
		}
		printf("&n[%d]->%p, n[%d] = %d, ", i, ap[i], i, *(ap[i]));
		printf("ap[%d]->%p, *ap[%d] = %d\n", i, ap[i], i, *(ap[i]));
	}
}

int main()
{
    int n[10] = {6,4,7,2,0,9,8,1,5,3};
    int* p = n;
    int x = 0;
    int* ap[10];
    for(int i = 0, j = 0; i < 10; i++) {
		ap[i] = &n[j++];
	}
    
    printf("No.1 -------------------\n");
    p_addressvalue(p,x);
    printf("No.2 -------------------\n");
    sort(ap);

    return 0;
}
