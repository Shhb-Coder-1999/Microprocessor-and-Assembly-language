#include<LPC17xx.h>
int x = 1;


 int main(){         
	 LPC_GPIO2->FIODIR=0xff; 
//set output led          

   while(1){    
LPC_GPIO2->FIOPIN = x;  
x=x*2;
 
if (x>128)x= 1;
	 }    
	
	
	while(1)
	{
	
	}
}
