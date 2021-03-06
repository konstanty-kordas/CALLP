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
    char* n = strdup(name);
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
    printf("Num of nodes: %d\n",counter); 
	
}

struct section* findSection(char* name){
    if (head==NULL){
        return NULL;
    }
    struct section *ptr = head;
    while(ptr){
        int compare;
        compare = strcmp(ptr->name,name);
        if (compare==0){
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
        int cmp = strcmp(key_head->name,key_name);
        if (cmp==0){
            return key_head;
        }
        key_head = key_head->NEXT;
    }
    return NULL;
}

int checkString(char*str){
    int l = strlen(str);
    for (int i=0;i<l;i++){
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
    char* n = strdup(key_name);
    char* v = strdup(value);
    struct section* parentSection = findSection(section_name);
    link->NEXT = parentSection->keys; //head
    link->name = n;
    link->value = v;
    parentSection->keys = link;
}

void split(char*input, char**arg1, char**arg2, char* delimeter){
    *arg1 = strtok(input,delimeter);
    *arg2 = strtok(NULL,delimeter);
    
}

char* solve(char* section_name, char* key_name){
    struct section* a;
    a = findSection(section_name);
    if (a!=NULL){   
        struct key* b = findKey(section_name,key_name);
        printf("FOUND: %s\n",a->name);
        if (b!=NULL){
            printf("KEY: %s \n",b->value);
            return b->value;
        }
        else{
            printf("Failed to find key [%s] in section {%s}\n",section_name,key_name);
        }
    }
    else{
        printf("Failed to find section [%s]\n", section_name);
    }
    return NULL;
}

int checkType(char*str){
    int len = strlen(str);
    for (int i=0;i<len;i++){
        if (!isdigit(str[i])){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    if (argc<3){
        printf("Not enough arguments given. Use command in format ./main_40 {$INI FILE TO PARSE} {$SECTION}.{$KEY}");
        return 0;
    }
    char* fname;
    fname = argv[1];
    char* temp;
    temp = argv[2];
    char* section_name;
    char* key_name;
    split(temp,&section_name,&key_name,".");
    char*operation;
    char* section2;
    char*section_name2;
    char*key_name2;
    if (argc>3){
        operation = strdup(argv[3]);
        section2=strdup(argv[4]);
        split(section2, &section_name2, &key_name2,".");
        // printf("SECTION NAME %s, KEY NAME %s \n", section_name2, key_name2);
    }
    FILE*fp = fopen(fname, "r");

    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    char* line;
    int ch;
    char* current_section;
    int pos;
    int size = 0;
    int file_size;
    
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    int redo;
    int comment= 0;
    do{
        redo=0;
        size=0;
        comment= 0;
        pos = ftell(fp);
        while ((ch=fgetc(fp))!='\n'){
            if ((size==0) && (ch==';')){
                comment=1;
            }
            size++;
            if (ch==-1){
                break;
            }
        }
        if (size==0) {
            redo=1;
        }

        if (pos>=file_size){
            break;
        }
        line = (char*)calloc(size+2,sizeof(char));
        fseek(fp,pos,SEEK_SET);
        fgets(line, size+2, fp);
        if (comment){
            continue;
        }
        if(line[0]=='['){
            current_section = (char*)calloc(sizeof(char), size+2);
            current_section = strdup(line+1);
            current_section[strlen(current_section)-1] = '\0'; // removes last character
            current_section[strlen(current_section)-1] = '\0'; 
            if (checkString(current_section)==0){
                printf("FOUND ILLEGAL ON %s", current_section);
                return 0;
            }
            insertFirst(current_section);
            continue;
        }
        if(strlen(line)<=1){
            continue;
        }
        char* curr_key;
        char* curr_val;
        split(line,&curr_key,&curr_val,"=");

        curr_val = curr_val+1;
        curr_key[strlen(curr_key)-1] = '\0';
        curr_val[strlen(curr_val)-1] = '\0';

        if (checkString(curr_key)==0){
            printf("FOUND ILLEGAL ON %s", curr_key);
            return 0;
        }
        insertKey(current_section,curr_key,curr_val);

    }
    while (size || redo );
    fclose(fp);
    char* val = solve(section_name,key_name);
    if (argc>3){

        char* val2 = solve(section_name2,key_name2);
        if (val==NULL || val2==NULL){
            return 0;
        }
        int type1 = checkType(val);
        int type2 = checkType(val2);
        if (type1!=type2){
            printf("Keys are of a diffrent type\n");
            return 0;
        }
        if (type1==0 && type2==0){
            if (strcmp(operation,"+")!=0){
                printf("Cannot perform %s on strings\n", operation);
                return 0;
            }
            else{
                char*result = (char*)malloc(sizeof(char)*(strlen(val)+strlen(val2)+1));
                result = strcat(result, val);
                result = strcat(result, val2);
                printf("Concatenation results in: %s\n",result);
                return 0;
            }
        }
        else{
            printf("BOTH INTS!\n");
            int v1 = atoi(val);
            int v2 = atoi(val2);
            if (strcmp(operation,"+")==0){
                int result = v1+v2;
                printf("Sum is %d\n", result);
                return 0;
            }
            if (strcmp(operation,"-")==0){
                int result = v1-v2;
                printf("Diffrence is %d\n", result);
                return 0;
            }
            if (strcmp(operation,"*")==0){
                int result = v1*v2;
                printf("Product is %d\n", result);
                return 0;
            }
            if (strcmp(operation,"/")==0){
                int result = v1/v2;
                printf("Quotient is %d\n", result);
                return 0;
            }
        }
    }
}
