#include <ft_malloc.h>
#include <HeavyPerson.h>

// int main() {
//     struct HeavyPeople people = {NULL, 0, 0};
    
//     printf("Creating memory-heavy data structure demo...\n");
    
//     // Create and add several people
//     for (int i = 0; i < 5; i++) {
//         struct HeavyPerson *person = create_heavy_person();
//         if (person) {
//             char fname[32], lname[32];
//             snprintf(fname, sizeof(fname), "FirstName%d", i+1);
//             snprintf(lname, sizeof(lname), "LastName%d", i+1);
            
//             fill_heavy_person(person, fname, lname, 25 + i, 1000 + i);
//             add_person_to_list(&people, person);
            
//             printf("Added person %d with ID %ld\n", i+1, person->id_number);
//         }
//     }
    
//     print_memory_usage(&people);
    
//     // Find and print a person
//     struct HeavyPerson *found = find_person_by_id(&people, 1002);
//     if (found) {
//         print_person_summary(found);
//     }
    
//     // Delete one person
//     delete_person_by_id(&people, 1001);
//     print_memory_usage(&people);
    
//     // Clean up all memory
//     delete_all_people(&people);
    
//     return 0;
// }

#include <stdlib.h>

int main(void){

    printf("FT_MALLOC EXAMPLE: ");
    char *msg = ft_malloc(sizeof(char) * 4);
    msg[0] = 'O';
    msg[1] = 'L';
    msg[2] = 'A';
    
    msg[4] = '\0';
    printf("[BEFORE FREE] %s\n\n", msg);
    ft_debug();
    ft_free(msg);
    printf("[AFTER FREE] %s\n", msg);
    msg[2] = 'E';
    printf("[AFTER FREE] changing one char: %s\n", msg);


    printf("\n\nMALLOC EXAMPLE: \n");
    msg = malloc(sizeof(char) * 4);
    msg[0] = 'O';
    msg[1] = 'L';
    msg[2] = 'A';
    msg[4] = '\0';
    printf("[BEFORE FREE] %s\n", msg);
    free(msg);
    printf("[AFTER FREE] %s\n", msg);
    msg[2] = 'E';
    printf("[AFTER FREE] changing one char: %s\n", msg);

}