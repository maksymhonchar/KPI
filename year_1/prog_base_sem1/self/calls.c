#include <stdio.h>
#include <stdlib.h>


int main(){
int h = 0;
int m = 0;
int code = 0;
int price = 0;
scanf("%d %d %d",&h,&m,&code);

	switch(code){
case 44:
price = m*0.44 + h*60*0.44;
break;

case 37:
price = m*1.05 + h*60*1.05;
break;

case 666:
price = m*666 + h*60*666;
break;

case 111:
price = m*111 + h*60*111;
break;

case 1:
price = m*30 + h*60*30;
break;

default:
return 1;
	}

printf("%d",price);
return 0;
}





