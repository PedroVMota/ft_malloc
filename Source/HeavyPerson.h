
#ifndef HEAVYPERSON_H
#define HEAVYPERSON_H

#define MAX_STRING_LEN 256
#define MAX_SKILLS 50
#define MAX_ADDRESSES 10
#define MAX_PHONE_NUMBERS 5
#define BUFFER_SIZE 8192


#include <stdio.h>
#include <time.h>
#include <ft_malloc.h>

struct HeavyPerson {
    // Basic info
    char *first_name;
    char *last_name;
    char *middle_name;
    char *nickname;
    int age;
    long id_number;
    
    // Contact information
    char addresses[MAX_ADDRESSES][MAX_STRING_LEN];
    char phone_numbers[MAX_PHONE_NUMBERS][32];
    char *email;
    char *website;
    
    // Professional info
    char *job_title;
    char *company;
    char skills[MAX_SKILLS][64];
    int num_skills;
    double salary;
    
    // Personal details
    char *biography;           // Large text field
    char *notes;              // Another large text field
    char profile_picture[BUFFER_SIZE];  // Simulated image data
    char resume_data[BUFFER_SIZE * 2];  // Large resume content
    
    // Medical records (heavy data)
    char medical_history[BUFFER_SIZE];
    char prescriptions[BUFFER_SIZE / 2];
    
    // Social connections
    long *friend_ids;         // Dynamic array of friend IDs
    int num_friends;
    int max_friends;
    
    // Timestamps and metadata
    time_t created_at;
    time_t last_modified;
    char *creation_location;
    
    // Large arrays for demonstration
    int yearly_income[50];    // 50 years of income data
    double health_metrics[365 * 10]; // 10 years of daily health data
    
    // Linked list pointer
    struct HeavyPerson *next;
};

struct HeavyPeople {
    struct HeavyPerson *lst;
    long long population;
    long long total_memory_used;
};

// Function prototypes
struct HeavyPerson* create_heavy_person(void);
void fill_heavy_person(struct HeavyPerson *person, const char *fname, const char *lname, int age, long id);
void add_person_to_list(struct HeavyPeople *people, struct HeavyPerson *person);
struct HeavyPerson* find_person_by_id(struct HeavyPeople *people, long id);
void delete_person_by_id(struct HeavyPeople *people, long id);
void delete_all_people(struct HeavyPeople *people);
void print_person_summary(struct HeavyPerson *person);
void print_memory_usage(struct HeavyPeople *people);
long calculate_person_memory_size(struct HeavyPerson *person);

#endif