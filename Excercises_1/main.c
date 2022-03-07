#include <stdio.h>
#include <math.h>

int powerCheck(int a, int b){
    if (a==1){
        return 1;
    }
    if (a%b!=0){
        return 0;
    }
    return powerCheck(a/b,b);
}

int main(){
    //1
    printf("\n\n\n1.");
    char name[11];
    printf("Input your name: ");
    scanf("%s", name);
    printf("Hello %s!\n", name);
    //2
    printf("\n\n\n2.");
    int value;
    printf("Input an integer (2): ");
    scanf("%d", &value);
    
    if (value < 0) {
        value*=-1;
    }   
    printf("The absolute value is: %d\n",value); 
    //3
    printf("\n\n\n3.");
    printf("Input an integer (3): ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Hello World! \n"); 
    }
    //4
    printf("\n\n\n4.");
    printf("Input an integer (4): ");    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j =0; j<=i;j++){
            printf("*");
        }
        printf("\n");
    }
    //5
    printf("\n\n\n5.");
    int hours, minutes, seconds;
    printf("Input a number of hours: ");
    scanf("%d", &hours);
    printf("Input a number of minutes: ");
    scanf("%d", &minutes);
    seconds = minutes*60+hours*60*60;
    printf("The number of seconds is %d \n",seconds);
    //6
    printf("\n\n\n6.");
    float kilometers,miles;
    printf("Input a number of kilometers: ");
    scanf("%f", &kilometers);
    miles = kilometers*0.621371192;
    printf("Number of miles is %f \n",miles);
    //7
    printf("\n\n\n7.");
    printf("Input a number of hours: ");
    scanf("%d", &hours);
    printf("Input a number of minutes: ");
    scanf("%d", &minutes);
    seconds = minutes*60+hours*60*60;
    printf("Input a number of kilometers: ");
    scanf("%f", &kilometers);
    miles = kilometers*0.621371192;
    float pace,speed;
    pace = seconds/miles;
    float hours_decimal,minutes_decimal;
    minutes_decimal  = minutes;
    hours_decimal = hours + (minutes_decimal/60);
    speed = kilometers/hours_decimal;
    printf("The speed is %f km/h \n",speed);
    printf("The pace is %f \n",pace);
    //8
    printf("\n\n\n8.");
    float r,volume;
    printf("Input the radius of the sphere:");
    scanf("%f",&r);
    volume = (4.0/3.0) * M_PI * r*r*r;
    printf("The volume is %f \n", volume);
    //9
    printf("\n\n\n9.");
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
    //10
    printf("\n\n\n10.");
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
    //11
    printf("\n\n\n11.");
    char *palindrome;
    printf("Input a string: ");
    scanf("%ms",&palindrome);
    printf("%s\n",palindrome);
    int length=0;
    while (palindrome[length]!=0){
        length+=1;
    }
    int p = 1;
    printf("%d\n",length );
    for (int i=0;i<length;i++){
        if (palindrome[i]!=palindrome[length-1-i]){
            p=0;
            break;
        }
    }
    if (p){
        printf("This is a palindrome \n");
    }
    else {
        printf("This is not a palindrome \n");
    }
    //12
    printf("\n\n\n12.");
    printf("input a: ");
    scanf("%d",&a); 
    printf("input b: ");
    scanf("%d",&b);
    if (powerCheck(a,b)){
        printf("Yes, %d is a power of %d \n",a,b);
    }
    else {
        printf("No, %d is not a power of %d \n",a,b);
    }
    return 0; 
}

