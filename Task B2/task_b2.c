#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME 16

typedef struct {
    int id;
    char name[MAX_NAME];
    char blood_group[4];
} Donor;

int is_valid_blood_group(const char *bg)
{
    int i;
    const char *valid[8];
    valid[0] = "A+";
    valid[1] = "A-";
    valid[2] = "B+";
    valid[3] = "B-";
    valid[4] = "AB+";
    valid[5] = "AB-";
    valid[6] = "O+";
    valid[7] = "O-";
    for (i = 0; i < 8; i++) {
        if (strcmp(bg, valid[i]) == 0) return 1;
    }
    return 0;
}

void clear_stdin_line(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void demo_safe_fgets(void)
{
    char name[MAX_NAME];
    size_t len;
    printf("Enter long donor name (buffer size %d): ", MAX_NAME);
    if (fgets(name, sizeof(name), stdin) != NULL) {
        len = strlen(name);
        if (len > 0 && name[len - 1] == '\n') {
            name[len - 1] = '\0';
        } else {
            clear_stdin_line();
        }
        printf("Safely stored name (%zu chars): '%s'\n", strlen(name), name);
    }
}

int demo_file_error(const char *filename, const char *mode)
{
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        perror(filename);
        return 0;
    }
    fclose(fp);
    return 1;
}

void demo_dynamic_cleanup(void)
{
    size_t cap = 4;
    Donor *list = (Donor *)malloc(cap * sizeof(Donor));
    if (list == NULL) {
        perror("malloc");
        return;
    }
    list[0].id = 1001;
    strncpy(list[0].name, "Aravind", MAX_NAME - 1);
    list[0].name[MAX_NAME - 1] = '\0';
    strncpy(list[0].blood_group, "O+", 3);
    list[0].blood_group[3] = '\0';

    printf("Allocated donor %d (%s, %s)\n", list[0].id, list[0].name, list[0].blood_group);

    free(list);
    list = NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s find <blood_group>\n", argv[0]);
        fprintf(stderr, "  %s issue <blood_group> <units>\n", argv[0]);
        fprintf(stderr, "  %s filetest <path> <mode>\n", argv[0]);
        fprintf(stderr, "  %s nametest\n", argv[0]);
        fprintf(stderr, "  %s memtest\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "find") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: 'find' requires exactly 1 argument (<blood_group>).\n");
            return 1;
        }
        if (!is_valid_blood_group(argv[2])) {
            fprintf(stderr, "Error: Invalid blood group '%s'.\n", argv[2]);
            return 1;
        }
        printf("Searching eligible donors for blood group %s...\n", argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "issue") == 0) {
        char *endptr = NULL;
        long units;
        if (argc != 4) {
            fprintf(stderr, "Error: 'issue' requires 2 arguments (<blood_group> <units>).\n");
            return 1;
        }
        if (!is_valid_blood_group(argv[2])) {
            fprintf(stderr, "Error: Invalid blood group '%s'.\n", argv[2]);
            return 1;
        }
        errno = 0;
        units = strtol(argv[3], &endptr, 10);
        if (errno != 0 || endptr == argv[3] || *endptr != '\0' || units <= 0) {
            fprintf(stderr, "Error: Invalid unit count '%s'.\n", argv[3]);
            return 1;
        }
        printf("Issuing %ld units of %s...\n", units, argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "filetest") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: 'filetest' requires <path> <mode>.\n");
            return 1;
        }
        if (!demo_file_error(argv[2], argv[3])) {
            return 1;
        }
        printf("Opened '%s' successfully.\n", argv[2]);
        return 0;
    }

    if (strcmp(argv[1], "nametest") == 0) {
        demo_safe_fgets();
        return 0;
    }

    if (strcmp(argv[1], "memtest") == 0) {
        demo_dynamic_cleanup();
        return 0;
    }

    fprintf(stderr, "Error: Unknown command '%s'.\n", argv[1]);
    return 1;
}
