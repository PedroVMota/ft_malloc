#include <HeavyPerson.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct HeavyPerson* create_heavy_person(void) {
    struct HeavyPerson *person = ft_malloc(sizeof(struct HeavyPerson));
    if (!person) {
        fprintf(stderr, "Memory allocation failed for HeavyPerson\n");
        return NULL;
    }
    
    // Initialize all pointers to NULL
    person->first_name = NULL;
    person->last_name = NULL;
    person->middle_name = NULL;
    person->nickname = NULL;
    person->email = NULL;
    person->website = NULL;
    person->job_title = NULL;
    person->company = NULL;
    person->biography = NULL;
    person->notes = NULL;
    person->creation_location = NULL;
    person->friend_ids = NULL;
    person->next = NULL;
    
    // Initialize arrays and other fields
    memset(person->addresses, 0, sizeof(person->addresses));
    memset(person->phone_numbers, 0, sizeof(person->phone_numbers));
    memset(person->skills, 0, sizeof(person->skills));
    memset(person->profile_picture, 0, sizeof(person->profile_picture));
    memset(person->resume_data, 0, sizeof(person->resume_data));
    memset(person->medical_history, 0, sizeof(person->medical_history));
    memset(person->prescriptions, 0, sizeof(person->prescriptions));
    memset(person->yearly_income, 0, sizeof(person->yearly_income));
    memset(person->health_metrics, 0, sizeof(person->health_metrics));
    
    person->age = 0;
    person->id_number = 0;
    person->num_skills = 0;
    person->salary = 0.0;
    person->num_friends = 0;
    person->max_friends = 10;
    person->created_at = time(NULL);
    person->last_modified = time(NULL);
    
    // Allocate initial friend list
    person->friend_ids = ft_malloc(person->max_friends * sizeof(long));
    if (!person->friend_ids) {
        ft_free(person);
        return NULL;
    }
    
    return person;
}

// Fill person with data (including heavy data simulation)
void fill_heavy_person(struct HeavyPerson *person, const char *fname, const char *lname, int age, long id) {
    if (!person) return;
    
    // Allocate and set basic info
    person->first_name = ft_malloc(strlen(fname) + 1);
    strcpy(person->first_name, fname);
    
    person->last_name = ft_malloc(strlen(lname) + 1);
    strcpy(person->last_name, lname);
    
    person->age = age;
    person->id_number = id;
    
    // Fill with sample heavy data
    person->middle_name = ft_malloc(32);
    strcpy(person->middle_name, "MiddleName");
    
    person->email = ft_malloc(64);
    snprintf(person->email, 64, "%s.%s@example.com", fname, lname);
    
    person->job_title = ft_malloc(64);
    strcpy(person->job_title, "Senior Software Engineer");
    
    person->company = ft_malloc(64);
    strcpy(person->company, "Tech Corporation Inc.");
    
    // Large biography (2KB)
    person->biography = ft_malloc(2048);
    strcpy(person->biography, "This is a very long biography that contains extensive information about the person's life, achievements, hobbies, interests, education, and personal history. It goes on for many paragraphs describing various aspects of their life in great detail...");
    
    // Large notes field (4KB)
    person->notes = ft_malloc(4096);
    strcpy(person->notes, "Extensive notes about this person including meeting records, personal observations, project collaborations, and detailed interaction history...");
    
    // Fill addresses
    for (int i = 0; i < 3; i++) {
        snprintf(person->addresses[i], MAX_STRING_LEN, "%d Main Street, City %d, State, 12345", i+1, i+1);
    }
    
    // Fill skills
    const char *sample_skills[] = {"C Programming", "Python", "JavaScript", "Database Design", "System Architecture"};
    person->num_skills = 5;
    for (int i = 0; i < person->num_skills; i++) {
        strcpy(person->skills[i], sample_skills[i]);
    }
    
    // Fill medical history with dummy data
    strcpy(person->medical_history, "Comprehensive medical history including all past procedures, medications, allergies, and health incidents over the past 20 years...");
    
    // Fill yearly income with sample data
    for (int i = 0; i < 50; i++) {
        person->yearly_income[i] = 50000 + (i * 1000) + (rand() % 10000);
    }
    
    // Fill health metrics with sample data
    for (int i = 0; i < 365 * 10; i++) {
        person->health_metrics[i] = 70.0 + (rand() % 40); // Sample heart rate
    }
    
    person->salary = 85000.50;
    person->last_modified = time(NULL);
}

// Add person to the list
void add_person_to_list(struct HeavyPeople *people, struct HeavyPerson *person) {
    if (!people || !person) return;
    
    person->next = people->lst;
    people->lst = person;
    people->population++;
    people->total_memory_used += calculate_person_memory_size(person);
}

// Find person by ID
struct HeavyPerson* find_person_by_id(struct HeavyPeople *people, long id) {
    if (!people) return NULL;
    
    struct HeavyPerson *current = people->lst;
    while (current) {
        if (current->id_number == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Calculate approximate memory size of a person
long calculate_person_memory_size(struct HeavyPerson *person) {
    if (!person) return 0;
    
    long size = sizeof(struct HeavyPerson);
    
    // Add dynamic allocations
    if (person->first_name) size += strlen(person->first_name) + 1;
    if (person->last_name) size += strlen(person->last_name) + 1;
    if (person->middle_name) size += strlen(person->middle_name) + 1;
    if (person->email) size += strlen(person->email) + 1;
    if (person->job_title) size += strlen(person->job_title) + 1;
    if (person->company) size += strlen(person->company) + 1;
    if (person->biography) size += strlen(person->biography) + 1;
    if (person->notes) size += strlen(person->notes) + 1;
    if (person->friend_ids) size += person->max_friends * sizeof(long);
    
    return size;
}

// Delete person by ID
void delete_person_by_id(struct HeavyPeople *people, long id) {
    if (!people || !people->lst) return;
    
    struct HeavyPerson *current = people->lst;
    struct HeavyPerson *prev = NULL;
    
    while (current) {
        if (current->id_number == id) {
            // Remove from list
            if (prev) {
                prev->next = current->next;
            } else {
                people->lst = current->next;
            }
            
            // Update stats
            people->population--;
            people->total_memory_used -= calculate_person_memory_size(current);
            
            // ft_free all allocated memory
            ft_free(current->first_name);
            ft_free(current->last_name);
            ft_free(current->middle_name);
            ft_free(current->nickname);
            ft_free(current->email);
            ft_free(current->website);
            ft_free(current->job_title);
            ft_free(current->company);
            ft_free(current->biography);
            ft_free(current->notes);
            ft_free(current->creation_location);
            ft_free(current->friend_ids);
            ft_free(current);
            
            printf("Person with ID %ld deleted successfully.\n", id);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    printf("Person with ID %ld not found.\n", id);
}

// Delete all people and ft_free memory
void delete_all_people(struct HeavyPeople *people) {
    if (!people) return;
    
    struct HeavyPerson *current = people->lst;
    while (current) {
        struct HeavyPerson *next = current->next;
        
        // ft_free all allocated memory for this person
        ft_free(current->first_name);
        ft_free(current->last_name);
        ft_free(current->middle_name);
        ft_free(current->nickname);
        ft_free(current->email);
        ft_free(current->website);
        ft_free(current->job_title);
        ft_free(current->company);
        ft_free(current->biography);
        ft_free(current->notes);
        ft_free(current->creation_location);
        ft_free(current->friend_ids);
        ft_free(current);
        
        current = next;
    }
    
    people->lst = NULL;
    people->population = 0;
    people->total_memory_used = 0;
    printf("All people deleted and memory ft_freed.\n");
}

// Print person summary
void print_person_summary(struct HeavyPerson *person) {
    if (!person) return;
    
    printf("\n=== Person Summary ===\n");
    printf("Name: %s %s\n", person->first_name ? person->first_name : "N/A", 
           person->last_name ? person->last_name : "N/A");
    printf("ID: %ld\n", person->id_number);
    printf("Age: %d\n", person->age);
    printf("Email: %s\n", person->email ? person->email : "N/A");
    printf("Job: %s at %s\n", 
           person->job_title ? person->job_title : "N/A",
           person->company ? person->company : "N/A");
    printf("Salary: $%.2f\n", person->salary);
    printf("Skills (%d): ", person->num_skills);
    for (int i = 0; i < person->num_skills && i < MAX_SKILLS; i++) {
        printf("%s%s", person->skills[i], (i < person->num_skills - 1) ? ", " : "");
    }
    printf("\nMemory footprint: %ld bytes\n", calculate_person_memory_size(person));
    printf("=====================\n");
}

// Print memory usage statistics
void print_memory_usage(struct HeavyPeople *people) {
    if (!people) return;
    
    printf("\n=== Memory Usage Statistics ===\n");
    printf("Total population: %lld\n", people->population);
    printf("Total memory used: %lld bytes (%.2f MB)\n", 
           people->total_memory_used, 
           people->total_memory_used / (1024.0 * 1024.0));
    if (people->population > 0) {
        printf("Average memory per person: %lld bytes\n", 
               people->total_memory_used / people->population);
    }
    printf("==============================\n");
}

// Example usage
