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
void init(int argc, char* argv[]) {
    printf("Short: Running shortcut: %s.\n", argv[1]);
    if (argc < 3) {
        printf("Short: No arguments provided\n");
        exit(1);
    } else if (!strcmp(argv[2], "c") || !strcmp(argv[2], "C") || !strcmp(argv[2], "cpp") || !strcmp(argv[2], "CPP")) {
        printf("Short: Initializing C project\n");
        char* names[] = {"src", "include", "bin", "test", "lib"};
        mkdirs(5, names);
    } else {
        printf("Short: Unknown project type\n");
    }
}
void code(int argc, char* argv[]) {
    //system("start cmd /K \"cd /d C:\\ && dir && echo Hello, World!\"");
    if (argc < 3) {
        printf("Short: No arguments provided, opening Dev\n");
        system("start cmd /K \"cd /d C:\\Users\\aarus\\Dev\\ && echo Short: Finished Running && code .\"");
    } else if (!strcmp(argv[2], "jarvis") || !strcmp(argv[2], "Jarvis")) {
        printf("Short: Opening Jarvis\n");
        system("start cmd /K \"cd /d C:\\Users\\aarus\\Dev\\.py\\Jarvis\\ && echo Short: Finished Running && code .\"");
    } else {
        printf("Short: Opening project %s\n", argv[2]);
        char project[100];
        sprintf(project, "start cmd /K \"cd /d C:\\Users\\aarus\\Dev\\%s\\ && echo Short: Finished Running && code .\"", argv[2]);
        system(project);
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Short: No arguments provided.\n");
        return 1;
    }

    if (!strcmp(argv[1], "init")) {
        init(argc, argv);
    } else if (!strcmp(argv[1], "code")) {
        code(argc, argv);
    } else {
        printf("Short: Unknown command.\n");
    }

    printf("Short: Finished running.\n");
    return 0;
}