/*
 * A set implementation in C using a dynamic array of integers.
 */
#include <stdio.h>
#include <stdlib.h>

/* Macro to increase the size of an array by sizeof(int) bytes */
#define ENLARGE_SIZE(size) ((size) + sizeof(int))

/* A struct representing a set of integers */
typedef struct {
    int *head_ptr;  /* Pointer to array of integers (dynamically allocated) */
    int last_index; /* Index to the last cell in the array */
} Set;

/* Function declarations */

void add_to_set(Set *s, int num);

void print_set(Set *s);

void get_set(Set *s);

int main() {
    Set s;
    s.head_ptr = NULL;
    s.last_index = 0;

    /* Get a list of numbers from the user and add them to the set */
    printf("Enter a list of numbers (terminate with EOF):\n");
    get_set(&s);

    /* Print the distinct numbers in the order they were added */
    printf("\nDistinct numbers in order of arrival: \n");
    print_set(&s);

    /* Free the dynamically allocated memory */
    free(s.head_ptr);
    return 0;
}

/*
 * Adds a new integer to the set if it doesn't already exist.
 *
 * Parameters:
 * s: a pointer to a struct Set representing the set to add the integer to.
 * num: the integer to add to the set.
 */
void add_to_set(Set *s, int num) {
    int i;
    int *ptr = s->head_ptr;

    /* Check if it's the first time inserting an item to the set */
    if (s->head_ptr == NULL) {
        /* Allocate memory for the first item */
        s->head_ptr = realloc(s->head_ptr, sizeof(int));
        if (s->head_ptr == NULL) { /* check if the memory allocation failed */
            printf("Error: failed to allocate memory.\n");
            exit(1);
        }
        /* Add the new item to the set */
        *(s->head_ptr) = num;
        s->last_index++;
        return;
    }

    /* Check if the value already exists in the set */
    for (i = 0; i < s->last_index; i++) {
        if (*(ptr + i) == num) /* means the number is already in the set, and we can exit the function */
            return;
    }

    /* Add the new value to the end of the array and update the last index */
    s->head_ptr = realloc(s->head_ptr, ENLARGE_SIZE(s->last_index) * sizeof(int));
    if (s->head_ptr == NULL) {  /* check if the memory allocation failed */
        printf("Error: failed to allocate memory.\n");
        exit(1);
    }
    *(s->head_ptr + s->last_index) = num;
    s->last_index++;
}

/*
 * Prints the contents of a set in the order they were added.
 *
 * Parameters:
 * s: a pointer to a struct Set representing the set to print.
 */
void print_set(Set *s) {
    int i;
    int *ptr = s->head_ptr;
    /* Iterate over the set and print each item */
    for (i = 0; i < s->last_index; i++)
        printf("%d ", *(ptr + i));
}

/*
 * Reads a list of integers from the user and adds them to the set.
 *
 * Parameters:
 * s: a pointer to a struct Set representing the set to add integers to.
 */
void get_set(Set *s) {
    int num;
    printf("All numbers that were read: \n");
    while (scanf("%d", &num) == 1 && num != EOF) {
        printf("%d ", num); /* print all the numbers that were read from stdin */
        add_to_set(s, num);
    }
}
