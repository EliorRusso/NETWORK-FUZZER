#include "AddProtocol.h"
#include <stdlib.h>
#include <stdio.h>

char* readline(){
    FILE *file;
    file = fopen("AddProtocol.h","r");
    char tmp[256]={0x0};
    char *tmpline;
    int numline = 1;
    while(file != NULL && fgets(tmp, sizeof(tmp),file) !=NULL)
    {
        tmpline = strstr(tmp,"_f");

        if(tmpline) {
            printf("%d - %s", numline, tmp);
    }

    numline++;
    }
    if (file != NULL) fclose(file);

    return 0;
}

int main(){
    struct Nissim x;
    x.src_f = 8388607;

    //pInstance = malloc(sizeof(struct InstanceProtocol));
    //pInstance-> src_f= 65535;
    //printf("%d", x.src_f);
    readline();
    //printf("%d", pInstance-> array[4]);
    //printf("%d", pInstance-> array[0]);
    //readline();
}