#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main() {
    int x;
    scanf("%d", &x);
    int y = x;
    fflush(stdin);
    getchar();
    char structt2[15] = "typedef struct ";
    char protocolname[10];
    FILE *fptr;
    fptr = fopen("AddProtocol.h", "w");
    printf("Enter the protcol name:");
    fgets(protocolname, sizeof(protocolname), stdin);
    fprintf(fptr, "%s%s{\n", structt2, protocolname); //protocol name
    while(x>0){
        char unsignedint[15] = "unsigned int ";
        fprintf(fptr, "%s\n", unsignedint);
        char field[15]; //name of field
        int size = 0;
        printf("Enter a field:");
        fgets(field, sizeof(field), stdin);
        strcat(field, ":");
        printf("Enter a size:");
        scanf("%d",&size);
        fprintf(fptr, "%s", field);
        fprintf(fptr,"%d;\n",size);
        x--;
        fflush(stdin);
        memset(field, 0, sizeof(field));
        getchar();
    }
    fflush(stdin);
    char close[19] = "} InstanceProtocol;";
    char close2[25] = "};";
    fprintf(fptr, "%s\n", close);
    fclose(fptr);
    fflush(stdin);
    printf("\n");

}