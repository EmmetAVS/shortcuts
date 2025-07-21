#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>

int should_exit;

void make_file(char* name) {
    FILE* file = fopen(name, "w");
    if (file) {
        fclose(file);
        printf("short: successfully created file %s\n", name);
    } else {
        printf("short: error creating file %s\n", name);
    }
}

void write_file(char* name, char* content) {
    FILE* file = fopen(name, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
        printf("short: successfully wrote to file %s\n", name);
    } else {
        printf("short: error writing to file %s\n", name);
    }
}

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
    printf("short: running shortcut: %s.\n", argv[1]);
    const char* type = argv[2];
    if (argc < 3) {
        printf("short: no arguments provided\n");
        exit(1);
    } else if (!strcmp(type, "c") || !strcmp(type, "C") || !strcmp(type, "cpp") || !strcmp(type, "CPP")) {
        printf("short: Initializing C project\n");
        char* names[] = {"src", "include", "bin", "test", "lib"};
        mkdirs(5, names);
    } else if (!strcmp(type, "fastapi") || !strcmp(type, "FastAPI") || !strcmp(type, "webapp")) {
        printf("short: Initializing Python webapp project\n");
        char* names[] = {"static", "static/styles", "static/assets", "static/scripts", "templates"};
        char* content = "from fastapi import FastAPI"
        "\nfrom fastapi import Cookie"
        "\nfrom fastapi.staticfiles import StaticFiles"
        "\nfrom fastapi.staticfiles import StaticFiles"
        "\nfrom fastapi.responses import HTMLResponse"
        "\nfrom fastapi.responses import JSONResponse"
        "\nfrom fastapi.responses import RedirectResponse"
        "\nfrom fastapi.templating import Jinja2Templates"
        "\nfrom fastapi.requests import Request"
        "\n\napp = FastAPI()"
        "\n\napp.mount(\"/static\", StaticFiles(directory=\"static\"), name=\"static\")"
        "\n\ntemplates = Jinja2Templates(directory=\"templates\")";
        write_file("main.py", content);
        mkdirs(5, names);
    } else {
        printf("short: Unknown project type\n");
    }
}

void code(int argc, char* argv[]) {
    //system("start cmd /K \"cd /d C:\\ && dir && echo Hello, World!\"");
    char project[256];
    if (argc < 3) {
        printf("short: No arguments provided, opening Dev\n");
        sprintf(project, "start cmd /K \"cd /d %s\\Dev\\ && code . && echo short: Finished Running\"", getenv("USERPROFILE"));
    } else {
        printf("short: Opening project %s\n", argv[2]);
        sprintf(project, "start cmd /K \"cd /d %s\\Dev\\%s\\ && code . && echo short: Finished Running\"", getenv("USERPROFILE"), argv[2]);
    }
    system(project);
    should_exit = 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("short: no arguments provided.\n");
        return 1;
    }

    if (!strcmp(argv[1], "init")) {
        init(argc, argv);
    } else if (!strcmp(argv[1], "code")) {
        code(argc, argv);
    } else {
        printf("short: unknown command.\n");
    }

    should_exit ? system("exit") : (void)0; 
    return 0;
}