#include<LPC17xx.h>

int x1 =1;
int x2 = 128;
int i;

int main(){
	LPC_GPIO2->FIODIR = 0xff;

	while(1){
		int x3=x1|x2;
	
		LPC_GPIO2->FIOPIN =x3 ;
		
		for(i=0;i<2000000;i++){}
		
		if (x1==8 ){
			x1 = 1;
		}
		else {x1=x1*2;}
		
		
		if (x2==16 ){
			x2 = 128;
		}
		else {x2=x2/2;}
		
	}
	
}