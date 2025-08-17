#include "cmd.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utils.h"

const int max_depth = 5;

static char *find_dir_path_rec(const char *base_path, const char *dir_entry, int depth) {
    
    if (depth >= max_depth) {
        return NULL;
    }

    struct dirent *de;
    struct stat st;

    DIR *dr = opendir(base_path);

    if (dr == NULL) {
        return NULL;
    }

    while ((de = readdir(dr)) != NULL) {
        char *full_path = safe_snprintf("%s\\%s", base_path, de->d_name);

        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            free(full_path);
            continue;
        }

        if (strcmp(de->d_name, dir_entry) == 0) {
            closedir(dr);
            return full_path;
        }

        if (stat(full_path, &st) == -1) {
            free(full_path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            char *sub_path = find_dir_path_rec(full_path, dir_entry, depth + 1);
            if (sub_path != NULL) {
                free(full_path);
                return sub_path;
            }
        }

        //printf("%s, type: %s\n", de->d_name, (S_ISDIR(st.st_mode)) ? "directory" : "other");
        free(full_path);
    }

    closedir(dr); 
    return NULL;
}

int code_cmd(int argc, char* argv[]) {
    char *project;
    if (argc < 3) {
        printf("short: No arguments provided, opening Dev\n");
        project = safe_snprintf("start cmd /K \"cd /d %s\\Dev\\ && code . && echo short: Finished Running\"", getenv("USERPROFILE"));
    } else {

        char *base_path = safe_snprintf("%s\\Dev", getenv("USERPROFILE"));
        char *dir_path = find_dir_path_rec(base_path, argv[2], 0);
        free(base_path);

        if (dir_path == NULL) {
            printf("short: Project %s not found in Dev\n", argv[2]);
            return 0;
        }

        printf("short: Opening project %s\n", argv[2]);
        project = safe_snprintf("start cmd /K \"cd /d %s && code . && echo short: Finished Running\"", dir_path);
    }
    printf("project opening: %s\n", project);
    system(project);
    free(project);

    return 1;
}