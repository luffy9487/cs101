#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
}node_t;

node_t* allocate_node(int data) {
   node_t *a = malloc(sizeof(node_t));
    a->data = data;
    a->next = NULL;
    return a;
}

void show_list(node_t* list) {
    node_t* tmp = list;
    while(tmp != NULL) {
        printf("[%d]->", tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

node_t* append_node(node_t* list, int new_data) {
    node_t* newNode = allocate_node(new_data);
    newNode->data = new_data;
    newNode->next     = NULL;
    if(list == NULL)
         list = newNode;
    else
    {
        node_t* lastNode = list;
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    return list;
}

void free_all_node(node_t* list) {
     while (list != NULL){ 
        node_t* temp = list; 
        list = list -> next;
        printf("free([%d])->",temp->data);
        free(temp);
    }
    printf("NULL");
}

int main() {
    node_t* head = NULL;
    head = append_node(head, 0);
    show_list(head);
    head = append_node(head, 11);
    show_list(head);
    head = append_node(head, 222);
    show_list(head);
    head = append_node(head, 3333);
    show_list(head);
    free_all_node(head);
}
