#include <stdio.h>
#include <string.h>
unsigned char xyz[200] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
};
unsigned char tag[200] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 
};
int main()
{
int i;
int t = 0;
int longueur1 = strlen(xyz);
int longueur2 = strlen(tag);
if (longueur1 == longueur2) {
for (i=0; i<200; i++){
if (xyz[i] != tag[i]) {
t=1;
}
}
} else {
t=1;
}
if (t==0) {
//do something good
printf("good");
} else {
//do something bad
printf("bad");
}
}

