
#include <stdio.h>

int func1(int* i, int* j) {
    int tmp;
    tmp = *i;
    *i = *j;
    *j = tmp;
    printf("after swap, n = %d, m = %d\n", *i, *j);
}

int swapArray(int a[10], int b[10], int size) {
    int tmp;
    for(int i = 0; i < size; i++) {
        tmp = *(a+i);
        *(a+i) = *(b+i);
        *(b+i) = tmp;
    }
}

void printfArray(int a[], int size) {
    for(int i = 0; i < size; i++) {
        if(i == (size-1)) {
            printf("%d",a[i]);
        } else {
            printf("%d, ", a[i]);
        }    
    }
    printf("]\n");
}

char* copy_string (char* s){
    int len = 0;
    while (*(s+len) != '\0') len++;
    char* New = calloc (len+1, sizeof(char));
    for (int i=0; i<=len; i++)  *(New+i) = *(s+i);
    return New;
}

int main()
{
    int n, m, size = 10;
    n = 1;
    m = 2;
    int source[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int dest[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    char str[] = "IU!IU!IU!IU!";
    char* cp_str = copy_string(str);
    
    printf("No.1 -------------------\n");
    func1(&n, &m);
    printf("No.2 -------------------\n");
    swapArray(source, dest, size);
    printf("after swap array, source array = [");
    printfArray(source, size);
    printf("after swap array, dest array = [");
    printfArray(dest, size);
    printf("No.3 -------------------\n");
    printf("copy string = %s\n", cp_str);
    free(cp_str);
    cp_str = NULL;

    return 0;
}
