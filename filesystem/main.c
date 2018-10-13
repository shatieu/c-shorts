
//
// Created by Ondřej on 18. 5. 2018.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

typedef struct lengths{
    int U;
    int L;
    int G;
    int S;
    int N;
    int I;

}lengths;

typedef struct myfile{
    char R[11];
    int L;
    char U [50];
    char G [50];
    long long int S;
    char T [50];
    char N [256];
    int I;

}myfile;

int get_int_len (long long int value){
    int l = 1;
    while(value > 9){ l++; value /= 10; }
    return l;
}

void updateLengths(myfile file, lengths* lens){
    if(strlen(file.U) > (unsigned int)lens->U){
        lens->U = strlen(file.U);
    }
    if(strlen(file.G) > (unsigned int)lens->G){
        lens->G = strlen(file.G);
    }
    if(strlen(file.N) > (unsigned int)lens->N){
        lens->N = strlen(file.N);
    }
    if(get_int_len(file.S)> lens->S){
        lens->S = get_int_len(file.S);
    }
    if(get_int_len(file.L)> lens->L){
        lens->L = get_int_len(file.L);
    }
    if(get_int_len(file.I)> lens->I){
        lens->I = get_int_len(file.I);
    }
}
void removeNewline(char* toremove){
    char a = toremove[0];
    int pos = 0;
    while(a != '\n'){
        pos++;
        a = toremove[pos];
        if(a == '\0'){
            break;
        }
    }
    toremove[pos] = '\0';
}
int addMyfile(int pos, struct stat state, myfile* files, lengths* lens){
    struct passwd* user = getpwuid(state.st_uid);
    struct group* group1 = getgrgid(state.st_gid);

    if(user != NULL){
        strcpy(files[pos].U, user->pw_name);
    } else{
        perror("user name error");
        files[pos].U[0] = '\0';
    }
    if(user != NULL){
        strcpy(files[pos].G, group1->gr_name);
    } else{
        perror("group name error");
        files[pos].G[0] = '\0';
    }

    files[pos].I = state.st_ino;
    files[pos].L = state.st_nlink;
    files[pos].S = state.st_size;
    strcpy(files[pos].T, ctime(&state.st_mtime));
    removeNewline(files[pos].T);
    mode_to_string(state.st_mode, files[pos].R);
    updateLengths(files[pos], lens);
    return 0;
}

int compare (const void* a, const void *  b){
    char * st = (char*)a;
    char * nd = (char*)b;
    if(strcmp(st, ".") == 0) return -1;
    if(strcmp(nd, ".") == 0) return 1;
    if(strcmp(st, "..") == 0) return -1;
    if(strcmp(nd, "..") == 0) return 1;

    if(st[0] == '.'){
        if(nd[0] == '.'){
            return (strcmp(st,nd));
        }
        return (strcmp(st+1,nd));
    }
    if (nd[0] == '.'){
        return (strcmp(nd+1,nd));
    }
    return(strcmp(st,nd));
}
void init_lengths(lengths* lengths1){
    lengths1->N = 0;
    lengths1->I = 0;
    lengths1->G = 0;
    lengths1->L = 0;
    lengths1->S = 0;
    lengths1->U = 0;
}

void printOne (char* mode, myfile prt, lengths lens, int all){

    for (unsigned int i = 0; i < strlen(mode) ; ++i) {
        if(!all && prt.N[0] == '.'){
            continue;
        } else {
            switch (mode[i]) {
                case 'R':
                    printf("%s", prt.R);
                    break;
                case 'L':
                    printf("%*d", lens.L, prt.L);
                    break;
                case 'N':
                    printf("%-*s", lens.N, prt.N);
                    break;
                case 'I':
                    printf("%*d", lens.I, prt.I);
                    break;
                case 'G':
                    printf("%-*s", lens.G, prt.G);
                    break;
                case 'S':
                    printf("%*lld", lens.S, prt.S);
                    break;
                case 'U':
                    printf("%-*s", lens.U, prt.U);
                    break;
                case 'M':
                    printf("%s", prt.T);
                    break;
                default:
                    break;
            }
            if (i != strlen(mode) - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }

}
int allAlmostAll (int count, char * arg []){
    for (int i = 0; i < (count); i++) {
        if (arg[i][1] == 'a' && arg[i][0] == '-'){
            return 1;
        }
    }
    return 0;
}

void changeMode(int count ,char* lettermode, char* arg []){
    for (int i = 0; i < (count); i++) {
        if(strncmp(arg[i], "--show=",6) == 0){
            int z = 7;
            int nd = 0;
            char a = arg[i][z];
            while (a != '\0'){
                lettermode[nd] = a;
                z++;
                a = arg[i][z];
                nd++;
            }
            lettermode[nd] = '\0';
        }
    }
}


int main (int argc, char* argv[]){

    char cwd [1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        perror("getcwd error");
        return 1;
    }

    printf("%s",cwd);
    DIR * directory = opendir(cwd);
    myfile * files = malloc(8* sizeof(myfile));
    char mode[9] = "RLUSGMN";
    int myfileSize = 8;
    int pos = 0;
    if (directory) {    // connect to directory
        struct dirent *dirEntry = NULL;
        struct stat state;
        char name [256];
        strncpy(name, cwd, strlen(cwd));
        lengths lens;
        init_lengths(&lens);
        while ((dirEntry = readdir(directory)) != NULL) {
            strcat(name, dirEntry->d_name);
            stat(name, &state);
            if(pos == myfileSize){
                files = realloc(files, 2*myfileSize* sizeof(myfile));
                if (files == NULL){
                    perror("realloc trouble");
                    return 2;
                }
            }
            strcpy(files[pos].N, dirEntry->d_name);
            addMyfile(pos, state, files, &lens);
            pos++;
        }
        qsort(files,(size_t)pos, sizeof(myfile),compare);
        int allFlag = allAlmostAll(argc,argv);
        changeMode(argc, mode,argv);
        for (int i = 0; i < pos; ++i) {
            printOne(mode,files[i],lens, allFlag);
        }

    }
    free(files);

    return 0;
}