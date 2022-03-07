#include <stdio.h>
#include <math.h>

int power_check(int a, int b){
    if (a==1){
        return 1;
    }
    if (a%b!=0){
        return 0;
    }
    return power_check(a/b,b);
}
void task_1(){
    printf("1.");
    char name[11];
    printf("Input your name: ");
    scanf("%s", name);
    printf("Hello %s!\n", name);
}
void task_2() {
    printf("2.");
    int value;
    printf("Input an integer (2): ");
    scanf("%d", &value);
    if (value < 0) {
        value*=-1;
    }   
    printf("The absolute value is: %d\n",value); 
    
}
void task_3() {
    printf("3.");
    printf("Input an integer (3): ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Hello World! \n"); 
    }
}
void task_4() {
    int n;
    printf("4.");
    printf("Input an integer (4): ");    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j =0; j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
}
void task_5() {
    printf("5.");
    int hours, minutes, seconds;
    printf("Input a number of hours: ");
    scanf("%d", &hours);
    printf("Input a number of minutes: ");
    scanf("%d", &minutes);
    seconds = minutes*60+hours*60*60;
    printf("The number of seconds is %d \n",seconds);
}
void task_6() {
    printf("6.");
    float kilometers,miles;
    printf("Input a number of kilometers: ");
    scanf("%f", &kilometers);
    miles = kilometers*0.621371192;
    printf("Number of miles is %f \n",miles);
}
void task_7() {
    float hours, minutes, seconds, kilometers;
    printf("7.");
    printf("Input a number of hours: ");
    scanf("%f", &hours);
    printf("Input a number of minutes: ");
    scanf("%f", &minutes);
    seconds = minutes*60+hours*60*60;
    printf("Input a number of kilometers: ");
    scanf("%f", &kilometers);
    float pace,speed,miles;
    miles = kilometers*0.621371192;
    pace = seconds/miles;
    hours = hours + (minutes/60);
    speed = kilometers/hours;
    printf("The speed is %f km/h \n",speed);
    printf("The pace is %f \n",pace);
    
}
void task_8() {
    printf("8.");
    float r,volume;
    printf("Input the radius of the sphere:");
    scanf("%f",&r);
    volume = (4.0/3.0) * M_PI * r*r*r;
    printf("The volume is %f \n", volume);
}
void task_9() {
    printf("9.");
    int copies;
    float cost;
    printf("Input the number of copies: ");
    scanf("%d",&copies);
    cost = copies*40;
    if (copies>50){
        cost = cost *0.6;
    }
    if (copies>0){
        cost+=5+(copies-1)*0.5;
    }
    printf("The cost is %f \n",cost);
}
void task_10() {
    printf("10.");
    int a,b,c;
    printf("input a: ");
    scanf("%d",&a);
    printf("input b: ");
    scanf("%d",&b);
    printf("input c: ");
    scanf("%d",&c);
    if ((a+b>c) && (a+c>b) && (b+c>a)){
        printf("Yes \n");
    }
    else {
        printf("No");
    }
}
void task_11() {
    printf("11.");    
    char *palindrome;
    printf("Input a string: ");
    scanf("%ms",&palindrome);
    printf("%s\n",palindrome);
    int length=0;
    while (palindrome[length]!=0){
        length+=1;
    }
    int bool = 1;
    printf("%d\n",length );
    for (int i=0;i<length;i++){
        if (palindrome[i]!=palindrome[length-1-i]){
            bool=0;
            break;
        }
    }
    if (bool){
        printf("This is a palindrome \n");
    }
    else {
        printf("This is not a palindrome \n");
    }
}
void task_12() {
    int a,b;
    printf("12.");
    printf("input a: ");
    scanf("%d",&a); 
    printf("input b: ");
    scanf("%d",&b);
    if (a==0 || b==0){
        printf("No, %d is not a power of %d \n",a,b);
    }
    else{
        if (power_check(a,b)){
            printf("Yes, %d is a power of %d \n",a,b);
        }
        else {
            printf("No, %d is not a power of %d \n",a,b);
        }
    }
}

int main(){
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
    task_6();
    task_7();
    task_8();
    task_9();
    task_10();
    task_11();
    task_12();
    return 0; 
}

