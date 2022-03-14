#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{


    // printf("In main, first %s \n", argv[1]);

    char* fname = argv[1];
    char* temp = argv[2];
    int offset = 0;
    while(temp[offset] != '.'){
        offset++;
    }

    int len = strlen(temp);
    char* section_name;
    section_name = (char *)malloc(sizeof(char) * offset+1);
    char* key_name;
    key_name = (char *)malloc(sizeof(char) * len-offset+1);

    strncpy(section_name, temp,offset);
    strncpy(key_name,temp+(offset+1),len-(offset+1));


    printf("SECTION NAME %s, KEY NAME %s \n", section_name, key_name);
    FILE* fp = fopen(fname, "r");

    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    char ch;
    int i;
    while((ch = fgetc(fp)) != EOF){
        if (ch=='[') {
            char* section;
            section = (char*)malloc(sizeof(char) * 30);
            i = 0;
            while ((ch = fgetc(fp)) != ']'){
                section[i++] = (char)ch;
            } 
            printf("%s \n", section);
            // if (strcmp(section,section_name)==0){
            //     char * key = (char*)malloc(sizeof(char) * 30);
            //     i=0;
            //     while (ch = fgetc(fp)){
            //         if (ch=='\n'){
            //             printf("%s \n", key);
            //             key = realloc(key,sizeof(char) * 30);
            //             i=0;

            //             continue;
            //         }
            //         if (ch==' '){
            //             if (strcmp(key,key_name)==0){
            //                 printf("%s, aaaa", key);
            //             }
            //             key = realloc(key,sizeof(char) * 30);
            //             i=0;
            //             continue;
            //         }
            //         key[i] = ch;
            //         i++;
            //     }
            // }
            free(section);  
        }
        // printf("%c", ch);
    }

    fclose(fp);
    return 0;
}
