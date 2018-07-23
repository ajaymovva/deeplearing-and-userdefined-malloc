
#define _CRT_SECURE_NO_WARNINGS
# include "implement_user_malloc.h"
//#include<Header.h>


void call_to_allocation()
{

	/*int *arr = (int *)ajay_alloc(10);
	printf("%d\n", arr);
	ajay_free((void*)arr);
	int *arr1 = (int *)ajay_alloc(4);
	printf("%d\n", arr1);
	int *arr2 = (int *)ajay_alloc(10);
	printf("%d\n", arr2);*/
	/*int *arr = (int *)ajay_alloc(100);
	printf("%d\n", arr);
	ajay_free((void*)arr);
	int *arr1 = (int *)ajay_alloc(400);
	printf("%d\n", arr1);
	int *arr2 = (int *)ajay_alloc(1000);
	printf("%d\n", arr2);*/
	int *arr = (int *)ajay_alloc(1000);
	printf("%d\n", arr);
	print();
	//
	ajay_free((void*)arr);
	print();
	int *arr1 = (int *)ajay_alloc(1000);
	printf("%d\n", arr1);
	print();
	int *arr2 = (int *)ajay_alloc(1000);
	printf("%d\n", arr2);
	print();
}







int main()
{
	//print_hello();
	int option;
	while (1)
	{
		printf("\t\t [1] to ajay_alloc [2]->[EXIT] \n ");
		scanf("%d", &option);
		switch (option)
		{

		case 1:
			call_to_allocation();
			break;
		case 2:
			break;
		default:
			break;
		}
		if (option == 2)
		{
			break;
		}
	}
	system("pause");
	return 0;
}