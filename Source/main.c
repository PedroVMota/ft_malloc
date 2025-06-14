#include <ft_malloc.h>
#include <HeavyPerson.h>

#include <stdlib.h>


int test_big_memory() {
    struct HeavyPeople people = {NULL, 0, 0};
    
    printf("Creating memory-heavy data structure demo...\n");
    
    // Create and add several people
    for (int i = 0; i < (5); i++) {
        struct HeavyPerson *person = create_heavy_person();
        if (person) {
            char fname[32], lname[32];
            snprintf(fname, sizeof(fname), "FirstName%d", i+1);
            snprintf(lname, sizeof(lname), "LastName%d", i+1);
            
            fill_heavy_person(person, fname, lname, 25 + i, 1000 + i);
            add_person_to_list(&people, person);
            
            printf("Added person %d with ID %ld\n", i+1, person->id_number);
        }
    }
    
    print_memory_usage(&people);
    
    // Find and print a person
    struct HeavyPerson *found = find_person_by_id(&people, 1002);
    if (found) {
        print_person_summary(found);
    }

    
    // Delete one person
    delete_person_by_id(&people, 1001);
    print_memory_usage(&people);
    
    // Clean up all memory
    delete_all_people(&people);
    return 0;
}


void ft(){
    int *size = ft_malloc(sizeof(int));
    if(!size)
        return;
    *size = 42;
    printf("Before free: %d\n", *size);
    ft_free(size);
    printf("after free: %d\n", *size);
    int newval = 1241;
    *size = newval;
    printf("Assing %d to var after free: %d\n", newval, *size);
}

void ml(){
    int *size = malloc(sizeof(int));
    if(!size)
        return;
    *size = 42;
    printf("Before free: %d\n", *size);
    free(size);
    printf("after free: %d\n", *size);
    *size = 42;
    int newval = 1241;
    *size = newval;
    printf("Assing %d to var after free: %d\n", newval, *size);
}

int main(void){
    ft();
    printf("\n ========== \n");
    ml();
    printf("\n ============ \n");
    test_big_memory();
    ft_debug();

}