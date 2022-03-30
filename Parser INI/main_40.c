#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct key {
    char* name;
    // char* value;
    struct key* NEXT;
};

struct section {
    char* name;
    struct key* keys;
    struct section* NEXT;
};

struct section *head = NULL;

void insertFirst(char* name) {
    char* n = (char*)malloc(sizeof(char)*strlen(name));
    stpncpy(n,name,strlen(name));
    struct section *link = (struct section*) malloc(sizeof(struct section));
    link->name = n;
    link->keys = NULL;
    link->NEXT = head;
    head = link;
}
void printList() { 
    struct section *ptr = head;
	int counter = 0;
    while(ptr != NULL) {
        printf("%s\n",ptr->name);
        ptr = ptr->NEXT;
        counter++;
    }
    printf("Num of nodes: %d",counter); 
	
}

struct section* findSection(char* name){
    struct section *ptr = head;
    while(ptr->NEXT!=NULL){
        if (strcmp(ptr->name,name)==0){
            return ptr;
        }
        ptr = ptr->NEXT;
    }
    return NULL;
}
int main(int argc, char *argv[])
{


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
    char line[100];
    char* current_section = (char *)malloc(sizeof(char) * 30);
    int found_section = 0;
    int found_key = 0;

    //  printf("TEST:%s, %d",current_section,strlen(current_section));
    while (fgets(line, sizeof line, fp) != NULL){
        // printf("%c", buf[0]);

        if(line[0]=='['){
            // current_section = line+1; // removes first character
            strncpy(current_section, line+1,30);
            current_section[strlen(current_section)-1] = '\0'; // removes last character
            current_section[strlen(current_section)-1] = '\0'; 
            
            printf("RESULT:  %s\n", current_section);
            insertFirst(current_section);
            // printf("NAME: %s\n", section_name);
            // printf  ("%d\n",strcmp(current_section,section_name));
            struct key *keyhead = NULL;
            continue;
        }
        // else{
        //     if(strlen(line)<=1){
        //         continue;
        //     }

        //     int j = 0;
        //     char* curr_key = (char *)malloc(sizeof(char) * 30);
        //     while(line[j]!=' '){
        //         curr_key[j] = line[j];
        //         j++;
        //     }
        //     printf("CURRENT  KEY %s\n", curr_key);
        //     // printf("%s",line);
        // }




    }
    printf("LIST:  ");
    printList();
    struct section* a = findSection(section_name);
    if (a!=NULL){   
        printf("\nFOUND: %s \n",a->name);
    }
    else{
        printf("AA");
    }
}
        
//         if (strcmp(current_section,section_name)==0){
//             found_section = 1;
//             // printf("LINE: %s\n", line);

//             if (strcmp(curr_key,key_name)==0){
//                 char* val = line+j+3;
//                 printf("%s", val);
//                 found_key = 1;
//                 break;
//             }
//         }
//     }
//     if(found_section==0){
//         printf("Failed to find section [%s]", section_name);
//     }
//     else if (found_key==0) {
//         printf("Failed to find key \"%s\" in section [%s]",key_name, section_name);
//     }
//     fclose(fp);
//     return 0;
// }
