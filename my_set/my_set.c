#include <stdio.h>
#include <stdlib.h>

#define ENLARGE_SIZE(size) ((size) + sizeof(int))

struct Set {
    int *head_ptr;  /* pointer to array of integers (dynamically allocated) */
    int last_index; /* index to the last cell in the array */
};

void add_to_set(struct Set *s, int num) {
    int i;
    int *ptr = s->head_ptr;

    /* Check if it's the first time inserting an item to the set */
    if (s->head_ptr == NULL) {
        s->head_ptr = realloc(s->head_ptr, sizeof(int));
        *(s->head_ptr) = num;
        s->last_index++;
        return;
    }

    /* Check if the value already exists in the set */
    for (i = 0; i < s->last_index; i++) {
        if (*(ptr + i) == num) /* means the number is already in the set, and we can exit the function*/
            return;
    }

    /* Add the new value to the end of the array and update the last index */
    s->head_ptr = realloc(s->head_ptr, ENLARGE_SIZE(s->last_index) * sizeof(int));
    *(s->head_ptr + s->last_index) = num;
    s->last_index++;
}

void print_set(struct Set *s) {
    int i;
    int *ptr = s->head_ptr;
    for (i = 0; i < s->last_index; i++)
        printf("%d ", *(ptr + i));
}

void get_set(struct Set *s) {
    int num;
    while (scanf("%d ", &num) == 1 && num != EOF) {
        add_to_set(s, num);
    }
}

int main() {
    struct Set s;
    s.head_ptr = NULL;
    s.last_index = 0;

    printf("Enter a list of numbers (terminate with EOF):\n");
    get_set(&s);

    printf("Distinct numbers in order of arrival: ");
    print_set(&s);

    free(s.head_ptr);
    return 0;
}
