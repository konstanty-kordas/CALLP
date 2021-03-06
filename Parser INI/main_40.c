#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct key {
    char* name;
    char* value;
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
    while(ptr){
        if (strcmp(ptr->name,name)==0){
            return ptr;
        }
        ptr = ptr->NEXT;
    }
    return NULL;
}

struct key* findKey(char*section_name, char* key_name){
    struct section *parent = findSection(section_name);
    struct key* key_head = parent->keys;
    while(key_head){
        if (strcmp(key_head->name,key_name)==0){
            return key_head;
        }
        key_head = key_head->NEXT;
    }
    return NULL;
}

int checkString(char*str){
    for (int i=0;i<strlen(str);i++){
        if (!isalnum(str[i]) && str[i]!='-'){
            return 0;
        }
    }
    return 1;
}

void printKeys(char*name){
    struct section *ptr = findSection(name);
    struct key* ptr2 = ptr->keys;
    while (ptr2){
        printf("%s \n",ptr2->name);
        ptr2 = ptr2->NEXT;
    }
}
void printVals(char*name){
    struct section *ptr = findSection(name);
    struct key* ptr2 = ptr->keys;
    while (ptr2){
        printf("%s:",ptr2->name);
        printf("%s",ptr2->value);
        ptr2 = ptr2->NEXT;
    }
}
void insertKey(char*section_name,char*key_name,char*value) {
    struct key* link = (struct key*)malloc(sizeof(struct key));
    char* n = (char*)malloc(sizeof(char)*strlen(key_name));
    char* v = (char*)malloc(sizeof(char)*strlen(value));
    strcpy(n,key_name);
    strcpy(v,value);
    struct section* parentSection = findSection(section_name);
    link->NEXT = parentSection->keys; //head
    link->name = n;
    link->value = v;
    parentSection->keys = link;
}

int main(int argc, char *argv[]){
    if (argc<3){
        printf("Not enough arguments given. Use command in format ./main_40 {$INI FILE TO PARSE} {$SECTION}.{$KEY}");
        return 0;
    }
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
    char* current_section = (char *)malloc(sizeof(char) * 60);
    int found_section = 0;
    int found_key = 0;

    while (fgets(line, sizeof line, fp) != NULL){
        if(line[0]=='['){
            strncpy(current_section, line+1,30);
            current_section[strlen(current_section)-1] = '\0'; // removes last character
            current_section[strlen(current_section)-1] = '\0'; 
            if (checkString(current_section)==0){
                printf("FOUND ILLEGAL ON %s", current_section);
                return 0;
            }
            insertFirst(current_section);
            struct key *keyhead = NULL;
            continue;
        }
        else{
            if(strlen(line)<=1){
                continue;
            }
            int j = 0;
            char* curr_key = (char *)calloc(1,sizeof(char) * 60);
            while(line[j]!=' '){
                curr_key[j] = line[j];
                j++;
            }
            if (checkString(curr_key)==0){
                printf("FOUND ILLEGAL ON %s", curr_key);
                return 0;
            }
            j+=3;
            char* curr_val = (char *)calloc(1,sizeof(char) * 60);
            curr_val = line+j;
            insertKey(current_section,curr_key,curr_val);
            
        }
    }
    
    struct section* a = findSection(section_name);
    if (a!=NULL){   
        struct key* b = findKey(section_name,key_name);
        printf("FOUND: %s\n",a->name);
        if (b!=NULL){
            printf("KEY: %s \n",b->value);
        }
        else{
            printf("Failed to find key [%s] in section %s\n",key_name,section_name);
        }
    }
    else{
        printf("Failed to find section %s", section_name);
    }
}
