#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char group[4];
} Donor;

typedef struct {
    Donor *data;
    int size;
    int capacity;
} DonorList;

int add_donor(DonorList *list, int id, const char *group)
{
    if (list->size == list->capacity) {
        int new_cap = (list->capacity == 0) ? 2 : list->capacity * 2;
        Donor *p = (Donor *)realloc(list->data, (size_t)new_cap * sizeof(Donor));
        if (p == NULL) {
            return 0;
        }
        list->data = p;
        list->capacity = new_cap;
    }
    list->data[list->size].id = id;
    strncpy(list->data[list->size].group, group, 3);
    list->data[list->size].group[3] = '\0';
    list->size++;
    return 1;
}

int main(void)
{
    int i;
    DonorList list = {NULL, 0, 0};
    const char *groups[5];
    groups[0] = "O+";
    groups[1] = "A+";
    groups[2] = "B-";
    groups[3] = "AB+";
    groups[4] = "O-";

    for (i = 0; i < 5; i++) {
        add_donor(&list, 7001 + i, groups[i]);
        printf("added %d (%s): size = %d, capacity = %d\n",
               list.data[i].id, list.data[i].group, list.size, list.capacity);
    }
    free(list.data);
    return 0;
}
