#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

void mkdirs(int l, char* names[]) {
    int i = 0;
    while (i < l) {
        char* name = names[i];
        int result = _mkdir(name);

        if (result == 0) {
            printf("Short: Successfully created directory with name %s\n", name);
        } else {
            printf("Short: Error creating directory with name %s\n", name);
        }
        i++;
    }
}
int init(int argc, char** argv) {
    printf("Short: Running shortcut: %s.\n", argv[1]);
    if (argc < 3) {
        printf("Short: No arguments provided\n");
        return 1;
    } else if (!strcmp(argv[2], "c") || !strcmp(argv[2], "C") || !strcmp(argv[2], "cpp") || !strcmp(argv[2], "CPP")) {
        printf("Short: Initializing C project\n");
        char* names[] = {"src", "include", "bin", "test", "lib"};
        mkdirs(5, names);
    } else {
        printf("Short: Unknown project type\n");
    }

    return 0;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Short: No arguments provided.\n");
        return 1;
    }

    if (!strcmp(argv[1], "init")) {
        exit(init(argc, argv));
    }

    printf("Finished running.\n");
    return 0;
}