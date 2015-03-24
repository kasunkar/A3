#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Process Process;

struct Process 
{
	char id;
	int size;
	int swaps;
    Process *next;
};


Process * append (Process * que,Process * toAdd);
Process * create (char name, int size);
void print (Process * que);





int main (int argc, char * argv[])
{


	FILE * fp =  fopen(argv[1],"r");
	char * memory = malloc(sizeof(char)*128);
	char * line = malloc(sizeof(char)*20);
	Process * que = NULL;
	int i;

	
	{
		char tempID;
		int tempSize;

		sscanf(line,"%c %d",&tempID, &tempSize);

		if (que == NULL)
		{
			que = create(tempID, tempSize);
		}
		else
		{
			que = append(que, create(tempID,tempSize));
		}
		
	}




	print(que);
	free(line);
	free(memory);	
	return 0;
}
Process * create (char name, int newSize)
{
	Process * newProcess;
	newProcess = malloc(sizeof(Process));
	newProcess->id = name;
	newProcess->size = newSize;
	newProcess->swaps = 0;
	newProcess->next=NULL;
	return newProcess;

}
Process * append (Process * que, Process * toAdd)
{
	Process * temp=que;

	if(que == NULL)
	{
		que = toAdd;
		toAdd->next = NULL;
		return que;
	}

	while(temp->next != NULL)
	{
		temp = temp->next;
	}

	temp->next = toAdd;
	toAdd->next = NULL;
	return que;
}

void print (Process * que)
{
	Process * temp = que;
	if(que == NULL)
	{
		printf("EMPTY\n");
	}
	while(temp!=NULL)
	{
		printf("%c %d\n", temp->id, temp->size);
		temp = temp->next;
	}
}