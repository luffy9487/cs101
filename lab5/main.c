
#include <stdio.h>
#include <stdlib.h>

int* get_int_array(int n) {
    return (int*)calloc(n, sizeof(int));
}

void set_value(int* p, int v) {
    *p = v;
}

void print_array(int* p, int n) {
    for(int i = 0; i < n; i++) {
        if(i == (n-1)) {
            printf("%d",*p+i);
        } else {
            printf("%d, ", *p+i);
        }
    }
}

typedef struct array_list {
    int n ;
    int* (*func_ptr1)(int);
    void (*func_ptr2)(int* , int);
    void (*func_ptr3)(int* , int);
    int* ip;
} array_list_t;

int main()
{
    int n = 10;
    int* ip = get_int_array(n);
    
    for(int i = 0; i < n; i++) {
        set_value(ip+i, i+1);
    }
    
    array_list_t a;
    a.n = 20;
    a.func_ptr1 = get_int_array;
    a.func_ptr2 = set_value;
    a.func_ptr3 = print_array;
    a.ip = a.func_ptr1(a.n);
    for(int i = 0; i < a.n; i++) {
        a.func_ptr2(a.ip+i, i+1);
    }
    
    
    printf("No.1 -------------------\n");
    printf("[");
    print_array(ip, n);
    printf("]\n");
    printf("No.2 -------------------\n");
    printf("[");
    a.func_ptr3(a.ip, a.n);
    printf("]\n");
    return 0;
}
