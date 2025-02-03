#include <stdio.h>

int main()
{
	void sortDescending(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (arr[i] < arr[j]) {
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
	void sort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (arr[i] > arr[j]) {
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
	long int x,a,b,c,g;
	printf("Enter a number, ");
	printf("there should be atleast one digit different digit ");
	printf("[0000, 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999 are prohibited]");
	printf("=>");
	scanf("%ld",&x);

	
	for(x; x!=0;)
	{
		a=x%10;
		g=x/10;
		b=g%10;
		g=g/10;
		c=g%10;
		g=g/10;
		
		if (b == a && a==g && g==c ) 
		{printf("Not Cpmpatible");
break;}
		else{
			int digits [4]= {a,b,c,g};

			sortDescending(digits, 4);
			long int l = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];

			sort(digits, 4);

			long int s=  digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
printf("The GREATEST number which can be fabricted by rearranging the digits of %ld is %ld\n",x,l);
printf("The SMALLEST number which can be fabricted by rearranging the digits of %ld is %ld",x,s);
			x = l-s;
			if (x!=6174)
			printf("\n The difference of the GREATEST and the SMALLEST number is  %ld\n",x);
			else 
				{
				   printf("\n The difference of the GREATEST and the SMALLEST number is %ld this is KAPREKAR'S CONSTANT",x);
				break;
				}	
			
		
	}

}

	return 0;
}