#include <iostream> 
using namespace std; 

int main () 
{ 
    int a, b, c; 
    printf("Thanks for viewing my code!\n");
    cin >> a >> b >> c; 
    if (c*c == a*a + b*b)   
    { 
        printf("rectangular\n");
    } 
    else if (c*c<a*a+b*b)
    { 
        printf("acute\n");
    } 
    else if (c*c>a*a+b*b) 
    { 
        printf("obtuse\n");
    } 
    else { 
        printf("impossible\n"); 
    } 
    return 0; 
}