#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void buildprotocolname(){
    char sentence[100];
    char sentence2[29] = "\", \"Custom Protocol\")";
    char protocolname[20];
    int currentlen = 29;
    // creating file pointer to work with files
    FILE *fptr;

    // opening file in writing mode
    fptr = fopen("program1.lua", "w");
    // exiting program 
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }
    printf("Enter the protocol name:\n");
    fgets(protocolname, sizeof(protocolname), stdin);
    strcpy(sentence, "local proto_ns = Proto.new(\"");
    strcat(sentence, protocolname);
    currentlen += strlen(protocolname);
    sentence[currentlen-2] = '\0';
    fprintf(fptr, "%s%s", sentence,sentence2);
    fclose(fptr);
}
int main() {
    buildprotocolname();
}