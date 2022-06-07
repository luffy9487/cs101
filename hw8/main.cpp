#include <iostream>
using namespace std;

class node {
    public:
    int data;
    node* next;
    node(int num) {
        data = num;
        next = NULL;
    }
};

class Linkedlist {
    private:
    node* head = NULL;
    node* list = NULL;
    public:
    ~Linkedlist() {
        node* tmp;
        while (list != NULL){ 
        tmp = list; 
        list = list -> next;
        cout << "free(["<< tmp->data << "]->" ;
        delete tmp;
        }
       cout << "NULL" << endl;
    }
    
    
    node* allocate_node(int data) {
    node *newNode = new node(data);
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
    }

    void show_list() {
    node* tmp = list;
    while(tmp != NULL) {
        cout <<"["<<tmp->data << "]" << "->";
        tmp = tmp->next;
    }
    cout <<"NULL" << endl;
    }

    void append_node(int new_data) {
    node* newNode = new node(new_data);
    newNode->data = new_data;
    newNode->next = NULL;
    if(list == NULL)
         list = newNode;
    else
    {
        node* lastNode = list;
        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    show_list();
    }

    void del_node(int n) {
     node* temp = list;
    if (n == 0){
        list = temp->next;   
        delete temp;               
    }else {
        for (int i=0; temp!=NULL && i<n-1; i++)
         temp = temp->next;
        if (temp != NULL || temp->next != NULL) {
            node* next = temp->next->next;
            delete temp->next;  
            temp->next = next;  
        }
    }
    show_list();
    }
};



int main() {
    Linkedlist mylink;
    mylink.append_node(0);
    mylink.append_node(1);
    mylink.append_node(2);
    mylink.append_node(3);
    mylink.del_node(1);
    return 0;
}
