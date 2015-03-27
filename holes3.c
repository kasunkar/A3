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
Process * create (char name, int size, int timesSwapped);
void print (char * mem);
void firstFit(char * memory, Process * que);
Process * duplicate (Process * source);
void printQue (Process * que);
int loadProcess (char * mem, Process * toLoad);
Process * deque (Process * que);
Process * clean(Process * que);
Process * lastInQue (Process * que);
void printInfo (Process * que);
Process * removeOne(Process* que, Process * toRemove);
Process * moveToBack(Process * que, Process *  toMove);
void stats(Process * que, char * mem);
int countProcess (Process * que);
int countHoles(char * mem);
double memusagse(Process * running);
double culMemUsage(Process * running);
int bestHole(char * mem, int size);
void bestFit(char * memory, Process * que);
void replaceMemory(char * memory, char rm, char replace);
int worstHole(char * memory, int size);
Process * enque(FILE * fp);
void clearMemory(char * memory);
void worstFit(char * memory,  Process * que);
int nextHole (char * memory, int size,int * lastIndex);
void nextFit(char * memory,Process * que);

int main (int argc, char * argv[])
{


	FILE * fp= NULL;
	fp =  fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("NO FILE\n");
		return 0;
	}
	int choice;
	char * memory = malloc(sizeof(char)*129);
	Process * que = NULL;
	clearMemory(memory);
	que = enque(fp);
	printf("Please select a number\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\n");
	scanf("%d",&choice);
	printf("%d\n",choice );

	if(choice == 1)
	{
		printf("**********FIRST FIT***********\n");
		firstFit(memory,que);
	}
	else if (choice == 2)
	{
		printf("***********BEST FIT************\n");
		bestFit(memory,que);
	}
	else if (choice == 3)
	{
		printf("*********WORST FIT*************\n");
		worstFit(memory,que);
	}else if(choice ==4)
	{
		printf("***********NEXT FIT*************\n");
		nextFit(memory,que);
	}


	free(memory);
	return 0;
}


int nextHole(char * memory, int size, int *lastIndex)/*uses index of last process id on memory NOT the empty one after*/
{
	int i = *lastIndex;
	int space=0;
	int start =-1;
	while(i<129)
	{
		
		if(memory[i]=='0')
		{
			space++;
		}

		if(memory[i]!='0')
		{
			space = 0;
		}


		if(space >= size)
		{
			start = i-space;
			*lastIndex = i+1;
			return start+1;
		}
		i++;
	}

	i=0;
	space =0;
	while(i<129)
	{
		if (memory[i]=='0')
		{ 
			space ++;
		}

		if(memory[i]!='0')
		{
			space = 0;
		}
		if(space>=size)
		{
			start = i-space;
			*lastIndex = i+1;
			return start+1;
		}
		i++;
	}
	return -1;

}




void nextFit(char * memory,Process * que)
{
	int success =-1;
	int lastIndex = -1;
	Process * running=NULL;
	while(que!=NULL)
	{
		success = nextHole(memory,que->size,&lastIndex);

		while(success== -1)
		{
			running->swaps++;
			que = append(que,duplicate(running));
			que = clean(que);
			replaceMemory(memory,running->id,'0');
			running = deque(running);
			success = nextHole(memory,que->size,&lastIndex);
		}

		int j;
		for(j=success;j<success + que->size;j++)
		{
			memory[j]=que->id;
		}
		running = append(running,duplicate(que));
		stats(running,memory);
		que = deque(que);
	}

}









void worstFit(char * memory,  Process * que)
{
	Process * running = NULL;
	int success = 0;
	int i;
	while(que!= NULL)
	{
		
		success = worstHole(memory,que->size);
		while(success < 0)
		{

			running->swaps++;
			que = append(que,duplicate(running));
			que = clean(que);
			replaceMemory(memory,running->id,'0');
			running = deque(running);
			success = worstHole(memory,que->size);
		}

		for(i=success;i<success+que->size;i++)
		{
			memory[i]= que->id;
		}
		running = append(running,duplicate(que));
		stats(running,memory);
		que = deque(que);
	}

}


int worstHole(char * memory,int size)
{

	int i=0;
	int space = 0;
	int worst=0;
	int start=-1;
	while(i<129)
	{
		
		if(memory[i]=='0') 
		{	
			space++;
		}
		
		if(memory[i]!= '0')
		{
			
			if(space>=worst && space>=size)
			{

				worst = space;
				start = i-space;
			}
			space=0;
		}
		i++;
	}

	return start;

}

void clearMemory(char * memory)
{ 
	int i;
	for(i=0;i<129;i++)
	{
		memory[i]='0';
	}
	memory[128]='1';
}

Process * enque(FILE * fp)
{
	Process * que;
	char * line = malloc(sizeof(char)*20);
	while(fgets(line,20,fp)!=NULL)
	{
		char tempID;
		int tempSize;

		sscanf(line,"%c %d",&tempID, &tempSize);

		if (que == NULL)
		{
			que = create(tempID, tempSize,0);
		}
		else
		{
			que = append(que, create(tempID,tempSize,0));
		}
		
	}

	free(line);
	return que;
}

void bestFit (char * memory, Process * que)
{
	Process* running=NULL;
	int success=0;
	int i=0;
	while(que!= NULL)
	{
		
		success= bestHole(memory,que->size);
		while(success==-1)
		{	
			running->swaps++;
			que = append(que,duplicate(running));
			que = clean(que);
			replaceMemory(memory,running->id,'0');
			running = deque(running);
			success  = bestHole(memory,que->size);
		}
		if(success!=-1)
		{
			int i;
			for(i=success;i<success+que->size;i++)
			{
				memory[i]=que->id;
			}

			running = append(running,duplicate(que));
			stats(running,memory);
		}
		i++;
		que=deque(que);
	}
	
}

void replaceMemory(char * memory, char rm, char replace)
{
	int i=0;


	while(memory[i]!=rm)
	{
		i++;
	}

	while(memory[i]==rm)
	{
		memory[i] = replace;
		i++;
	}
}


int bestHole(char * memory,int size)
{
	int i=0;
	int space = 0;
	int best=128;
	int start=-1;
	while(i<129)
	{
		
		if(memory[i]=='0') 
		{	
			space++;
		}
		
		if(memory[i]!= '0')
		{
			
			if(space<=best && space>=size)
			{

				best = space;
				start = i-space;
			}
			space=0;
		}
		i++;
	}

	return start;
}

Process * create (char name, int newSize, int timesSwapped)
{
	Process * newProcess;
	newProcess = malloc(sizeof(Process));
	newProcess->id = name;
	newProcess->size = newSize;
	newProcess->swaps = timesSwapped;
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

Process * deque (Process * que)
{

	Process * temp=que;

	if (que == NULL)
	{
		printf("EMPTY QUE\n");
		return NULL;
	}

	que = que->next;
	free(temp);
	return que;
}

void printQue (Process * que)
{
	Process * temp  = que;
	if(que == NULL)
	{
		printf("EMPTY QUE\n");
	}
	while(temp!=NULL)
	{
		printf("%c   %2d   %d\n", temp->id, temp->size,temp->swaps);
		temp = temp->next;
	}
}

void printInfo(Process * que)
{
	if(que == NULL)
	{
		printf("EMPTY QUE\n");
		return;
	}
	printf("%c   %d   %d\n", que->id,que->size,que->swaps);
}

void print (char * mem)
{
	int i;
	for(i=0;i<128;i++)
	{
		printf("%c  ", mem[i]);

	}
	printf("\n");
}

Process * duplicate (Process * source)
{
	return create(source->id,source->size,source->swaps);
}

void firstFit (char * memory, Process * que)
{
	int sum=0;
	Process * running=NULL;
	while(que!= NULL)
	{
		/*
		printf("***********************************************\nQUE\n");
		printQue(que);
		printf("***********************************************\nRUNNING\n");
		printQue(running);
		printf("***********************************************\n\n");
		*/	
		sum = loadProcess(memory,que);
		if(sum == 1)
		{
			
			running = append(running, duplicate(que));
			stats(running,memory);
			
		}

		while (sum == 0) /*no hole big enough*/
		{
			int i=0;
			char oldestID = running->id; /* gets the head of the running que as oldest*/
			running->swaps++;/*update the swap tims right before swapping*/
			que = append(que,duplicate(running)); /*delets running process from where ever in the que and appends it to the back*/ 
			que = clean(que);/*remove and processes with threee or more swaps*/
			
			running = deque(running);
			
			while(memory[i]!= oldestID)
			{
				i++;
			}

			while(memory[i]==oldestID)
			{
				memory[i]='0';
				i++;
			}
			sum = loadProcess(memory,que);
			if(sum == 1)
			{
				running = append(running, duplicate(que));
				stats(running,memory);
			}
		}

		que = deque(que);
	}

}

int loadProcess (char * mem, Process * toLoad)
{

	int i=0;
	int j=0;
	int count=0;
	while(mem[i]!='1')
	{
		if(mem[i]=='0')
		{
			
			count++;
		}
		
		if(mem[i+1] != '0' && i-count != i)
		{
			if(count>=toLoad->size)
			{
				for(j=i-count+1;j<i-count+1+toLoad->size;j++)
				{
					mem[j]=toLoad->id;
				}
				return 1;
			}
			count=0;
		}
		i++;
	}
		
	
	return 0;
}

Process * clean(Process * que)
{
	Process* temp = que;

	if(temp->swaps>=3)
	{
		
		que=deque(que);
		return que;
	}

	while(temp->next != NULL)
	{
		if(temp->next->swaps >=3)
		{
			Process * rm = temp->next;
			temp->next = temp->next->next;
			free(rm);
			return que;
		}
		temp = temp->next;
	}

	if(temp->next == NULL && temp->swaps>=3)
	{
		Process * rm = temp;
		temp = NULL;
		free(rm);
		return que;
	}
	return que;
}

Process * lastInQue (Process * que)
{
	Process * temp = que;

	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}

int countProcess (Process * que)
{
	int i=0;
	Process * temp = que;

	while(temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return i;
}

int countHoles(char * mem)
{
	int i=0;
	int count = 0;

	while(mem[i]!= '1')
	{
		if(mem[i] == '0' && mem[i+1]!='0')
		{
			count++;
		}
		i++;
	}

	return count;
}



Process * removeOne(Process* que, Process * toRemove)
{
	Process* temp = que;

	if(temp->id == toRemove->id)
	{
		que=deque(que);
		return que;
	}

	while(temp->next != NULL)
	{
		if(temp->next->id == toRemove->id )
		{
			Process * rm = temp->next;
			temp->next = temp->next->next;
			free(rm);
			return que;
		}
		temp = temp->next;
	}

	if(temp->next == NULL)
	{
		Process * rm = temp;
		temp = NULL;
		free(rm);
		return que;
	}
	return que;

}

Process * moveToBack(Process * que, Process *  toMove)
{
	Process * afterRemoval = removeOne(que,toMove);
	afterRemoval = append(que,toMove);
	return afterRemoval;
}

void stats(Process * que, char * mem)
{
	char * out = malloc(sizeof(char)*100);
	sprintf(out, "%c loaded, #processes %d, #holes %d, memusagse %.2lf, culmemusage %.2lf \n", lastInQue(que)->id, countProcess(que), countHoles(mem), memusagse(que), culMemUsage(que));
	printf("%s\n",out);
	free(out);
}

double memusagse(Process * running)
{

	Process * temp = running;
	double usage =0;
	double percent=0;

	while(temp!= NULL)
	{

		usage = usage + temp->size;
		temp =temp->next;
	}
	percent = (usage/128)*100;
	return percent;

}


double culMemUsage(Process * running)
{
	double sum =0;

	return sum;

}

/* 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 
    0  0  0  0  0  0  0  0  0  0  a  a  a  a  0  0  0  0  0  0  b
*/