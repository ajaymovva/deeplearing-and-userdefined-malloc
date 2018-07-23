# include<stdio.h>
# include<stdlib.h>

# define BLOCK_SIZE 1024
# define _CRT_SECURE_NO_WARNINGS




struct free_list
{
	void *free_start_address;
	int size;
	struct free_list *link;
}*free_head=NULL,*free_last=NULL;





int total_blocks = 0;
void *allocated_address;

void allocate_respected_memory()
{
	allocated_address = malloc(BLOCK_SIZE);
	total_blocks++;
	free_list *new_node = (free_list *)malloc(sizeof(free_list));
	new_node->free_start_address = allocated_address;
	new_node->size = BLOCK_SIZE;
	new_node->link = NULL;
	if (free_head == NULL)
	{
		free_head = free_last = new_node;
	}
	else
	{
		free_last->link = new_node;
	}
	
}



void * assign_the_final_address(free_list *previous, free_list *present, int size)
{

	short int x = size-2;
	void *address = ((short*)present->free_start_address) + 1;//int* takes 4 bytes
	*((short *)present->free_start_address) = x;
	if (present->size > size)
	{
		free_list *new_node = (free_list *)malloc(sizeof(free_list));
		new_node->size = (present->size) - size;;
		new_node->link = NULL;
		new_node->free_start_address = (void*)(((char*)present->free_start_address) + size);
		if (previous != present)
		{
			previous->link = new_node;
		}
		new_node->link = present->link;
		if (present == free_head)
		{
			free_head = new_node;
		}
		if (present == free_last)
		{
			free_last = new_node;
		}
	}
	else
	{
		if (present == previous)
		{
			free_last = present->link;
			free_head = present->link;
		}
		else
		{
			if (present == free_last)
			{
				free_last = previous;
			}
			else
			{
				previous->link = present->link;
			}
		}
	}
	return address;
}





void *calculate_address(int size)
{
	free_list *present,*previous=free_head;
	present = free_head;
	while (present != NULL)
	{
		if (present->size >= size+2)
		{
			return(assign_the_final_address(previous, present, size + 2));
		}
		previous = present;
		present = present->link;
	}
	return NULL;
}





void *ajay_alloc(int size)
{
	if (size > BLOCK_SIZE  && total_blocks>12)
	{
		if (total_blocks > 12)
		{
			printf("limit exceed");
			return NULL;
		}
		printf("not given more than 1024 so given 1022\n");
		size = 1022;
	}
	if (free_head == NULL)
	{
		allocate_respected_memory();
	}
	void *allocated_address=calculate_address(size);
	if (allocated_address == NULL)
	{
		allocate_respected_memory();
		allocated_address = calculate_address(size);
	}
	return (void *)allocated_address;
}





void assign_memory_to_free_list(void *allocated_address)
{
	void *final_address = (void*)(((short*)allocated_address)-1);
	int size = *((short*)final_address);
	free_list *new_node = (free_list *)malloc(sizeof(free_list));
	new_node->free_start_address = (char *)final_address;
	new_node->size = size+2;
	new_node->link = NULL;
	free_list *temp=free_head,*temp1 = free_head;
	while (temp != NULL)
	{
		if (temp->free_start_address > new_node->free_start_address)
		{
			void *address = (void *)((short *)temp1->free_start_address + (temp1->size)/2);
			if (address == new_node->free_start_address)
			{
				temp1->size = (temp1->size) + new_node->size;
				if ((void *)((short*)temp1->free_start_address + (temp1->size)/2) == temp->free_start_address)
				{
					temp1->size = temp1->size + temp->size;
					temp1->link = temp->link;
				}
			}
			else if ((void *)((short *)new_node->free_start_address + (new_node->size/2)) == temp->free_start_address)
			{
				temp->size = temp->size + new_node->size;
				temp->free_start_address = new_node->free_start_address;
			}
			else
			{
				temp1->link = new_node;
				new_node->link = temp;
			}
			break;
		}
		temp1 = temp;
		temp = temp->link;
	}
	if (temp == NULL)
	{
		free_head = new_node;
	}

}




void ajay_free(void *address)
{
	assign_memory_to_free_list(address);
}


void print()
{


	free_list *temp;
	temp = free_head;
	while (temp != NULL)
	{
		printf("start address: %d\tsize:%d\n", temp->free_start_address, temp->size);
		temp = temp->link;
	}
}