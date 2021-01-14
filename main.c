#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void menu();

struct Medicine {
    char name[50];
    char type[50];
    char company[50];
    char expireDate[50];
    int barcode;
    int count;
    float price;
};

struct node {
    struct Medicine medicine;
    struct Node *next;
};

struct node *head = NULL;
int number_of_medicines = 0;


void Add_new_medicine() {
    int count;
    printf("ENTER NUMBER OF NEW MEDICINES you want to add to list :\n");
    scanf("%d", &count);
    if (count + number_of_medicines > 100) {
        printf("list does not have enough space !\n");
        Add_new_medicine();
    } else {
        for (int i = 0; i < count; ++i) {
            struct Medicine new_medicine;
            printf("enter name: \n");
            scanf("%s", new_medicine.name);
            printf("enter type: \n");
            scanf("%s", new_medicine.type);
            printf("enter company: \n");
            scanf("%s", new_medicine.company);
            printf("enter expireDate: \n");
            scanf("%s", new_medicine.expireDate);
            printf("enter barcode: \n");
            scanf("%d", &new_medicine.barcode);
            printf("enter stock: \n");
            scanf("%d", &new_medicine.count);
            printf("enter price: \n");
            scanf("%f", &new_medicine.price);
            struct node *link = (struct node *) malloc(sizeof(struct node));
            link->medicine = new_medicine;
            link->next = head;
            head = link;
            number_of_medicines++;
        }
    }
    menu();
}

void delete_medicine() {
    int count;
    printf("ENTER NUMBER OF MEDICINES you delete from list :\n");
    scanf("%d", &count);
    if (count > number_of_medicines) {
        printf("list does not have enough medicine !\n");
        delete_medicine();
    } else {
        for (int i = 0; i < count; ++i) {
            char name[50];
            printf("ENTER NAME OF MEDICINE : \n");
            scanf("%s", name);
            struct node *current = head;
            struct node *previous = NULL;
            while (strcmp(current->medicine.name, name) != 0) {
                //if it is last node
                if (current->next == NULL) {
                    printf("medicine does not found !!");
                    break;
                } else {
                    previous = current;
                    current = current->next;
                }
            }
            if (current == head) {
                head = head->next;
            } else {
                previous->next = current->next;
            }
            number_of_medicines--;
        }
    }
    menu();
}

void change_stock() {
    struct node *current = head;
    if (head == NULL) {
        printf("list is empty ! \n");
        menu();
    }
    char name[50];
    printf("ENTER NAME of medicine :\n");
    scanf("%s", name);
    while (strcmp(current->medicine.name, name) != 0) {
        if (current->next == NULL) {
            printf("medicine does not found !");
            change_stock();
            break;
        } else {
            current = current->next;
        }
    }
    if (strcmp(current->medicine.name, name) == 0) {
        int new_stock;
        printf("ENter new stock :\n");
        scanf("%d", &new_stock);
        current->medicine.count = new_stock;
    } else {
        printf("medicine does not found !");
        change_stock();
    }
    menu();
}

void change_price() {
    struct node *current = head;
    if (head == NULL) {
        printf("list is empty ! \n");
        menu();
    }
    char name[50];
    printf("ENTER NAME of medicine :\n");
    scanf("%s", name);
    while (strcmp(current->medicine.name, name) != 0) {
        if (current->next == NULL) {
            printf("medicine does not found !");
            change_stock();
            break;
        } else {
            current = current->next;
        }
    }
    if (strcmp(current->medicine.name, name) == 0) {
        float new_price;
        printf("Enter new price :\n");
        scanf("%f", &new_price);
        current->medicine.price = new_price;
    } else {
        printf("medicine does not found !");
        change_price();
    }
    menu();
}

void show_list() {
    int i, j, k;
    struct Medicine tempData;
    struct node *current;
    struct node *next;
    k = number_of_medicines;
    for (i = 0; i < number_of_medicines - 1; i++, k--) {
        current = head;
        next = head->next;
        for (j = 1; j < k; j++) {
            if (current->medicine.name[0] > next->medicine.name[0]) {
                tempData = current->medicine;
                current->medicine = next->medicine;
                next->medicine = tempData;
            }
            current = current->next;
            next = next->next;
        }
    }
    struct node *ptr = head;
    while (ptr != NULL) {
        printf("Name : %s \t type : %s \t stock : %d \t price : %f \n", ptr->medicine.name, ptr->medicine.type,
               ptr->medicine.count, ptr->medicine.price);
        ptr = ptr->next;
    }
    menu();
}

void search() {
    struct node *current = head;
    if (head == NULL) {
        printf("list is empty ! \n");
        menu();
    }
    int input;
    char name[50];
    int barcode;
    printf("1 ) by name \t 2 ) by barcode ");
    scanf("%d", &input);
    if (input == 1) {
        printf("ENTER NAME of medicine :\n");
        scanf("%s", name);
        while (strcmp(current->medicine.name, name) != 0) {
            if (current->next == NULL) {
                printf("medicine does not found !");
                search();
                break;
            } else {
                current = current->next;
            }
        }
    } else {
        printf("ENTER barcode of medicine :\n");
        scanf("%d", &barcode);
        while (current->medicine.barcode != barcode) {
            printf("#### \n");
            if (current->next == NULL) {
                printf("medicine does not found !");
                search();
                break;
            } else {
                current = current->next;
            }
        }
    }
    if (strcmp(current->medicine.name, name) == 0 || current->medicine.barcode == barcode) {
        printf("Name : %s \t type : %s \t stock : %d \t price : %f \n", current->medicine.name, current->medicine.type,
               current->medicine.count, current->medicine.price);
    } else {
        printf("medicine does not found !");
        search();
    }
    menu();
}

void save_list() {
    FILE *fptr;
    fptr = fopen("program.bin", "wb");
    struct node *ptr = head;
    while (ptr != NULL) {
        fwrite(&ptr->medicine, sizeof(struct Medicine), 1, fptr);
        ptr = ptr->next;
    }
    fclose(fptr);
}

void load_list() {
    FILE *fptr;
    if ((fptr = fopen("program.bin", "rb")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    int count;
    printf("ENTER number of medicines\n");
    scanf("%d", &count);
    for (int i = 0; i < count; ++i) {
        struct Medicine medicine;
        fread(&medicine, sizeof(struct Medicine), 1, fptr);
        printf(" name : %s \t price : %f \n", medicine.name, medicine.price);
        struct node *link = (struct node *) malloc(sizeof(struct node));
        link->medicine = medicine;
        link->next = head;
        head = link;
        number_of_medicines++;
    }
    fclose(fptr);
}

void menu() {
    printf("1 ) Add new Medicine to list \n");
    printf("2 ) Delete Medicine from list \n");
    printf("3 ) change stock of a medicine \n");
    printf("4 ) change price Of a medicine \n");
    printf("5 ) See stocks Alphabetically \n");
    printf("6 ) Search by name or barcode \n");
    printf("7 ) Save List and Exit \n");
    int input;
    scanf("%d", &input);
    switch (input) {
        case 1:
            Add_new_medicine();
            break;
        case 2:
            delete_medicine();
            break;
        case 3:
            change_stock();
            break;
        case 4:
            change_price();
            break;
        case 5:
            show_list();
            break;
        case 6:
            search();
            break;
        case 7:
            save_list();
            break;
        default:
            printf("invalid input \n");
            menu();
            break;
    }
}


int main() {
    load_list();
    char user_name[20], pass[20];
    printf("PLEASE ENTER USER NAME : \n");
    scanf("%s", &user_name);
    printf("PLEASE ENTER YOUR PASSWORD : \n");
    scanf("%s", pass);
    if (strcmp("admin", user_name) == 0 && strcmp("admin", pass) == 0)
        menu();
    else
        printf("Wrong userName Or password ! , try again");
    return 0;
}
