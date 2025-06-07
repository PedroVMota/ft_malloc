#include <ft_malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct Person {
    char *first_name;
    char *last_name;
    int age;
    long id_number;
};

void show(struct Person *ptr){
    if(!ptr){
        printf("There is no ptr\n");
        return;
    }
    printf("First name: %s\n", ptr->first_name);
    printf("Last Name: %s\n", ptr->last_name);
    printf("Age: %d\n", ptr->age);
    printf("Identification number: %ld\n", ptr->id_number);
}

// Modified main for leak testing
int main() {
    printf("Person Sizeof %d\n", (int)sizeof(struct Person));
    struct Person *ptr = ft_malloc(sizeof(struct Person) * 1);
    if(!ptr){
        printf("Person was not allocated!\n");
        return 0;
    }
    ptr->age = 42;
    ptr->first_name = "Test";
    ptr->id_number = 1231231231231231;
    ptr->last_name = "Test";
    show(ptr);
    return 0;
}
