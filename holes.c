#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Process Process;

struct Process 
{
	char id;
	int size;
	int swaps;
    Process *next;
};


void append (Process ** que,Process * toAdd);
Process * create (char name, int size, int timesSwapped);
void print (char * mem);
void firstFit(char * memory, Process ** que);
Process * duplicate (Process * source);
void printQue (Process * que);
int loadProcess (char * mem, Process * toLoad);

Process * lastInQue (Process * que);
void printInfo (Process * que);
Process * moveToBack(Process ** que, Process *  toMove);
void stats(Process * que, char * mem);
int countProcess (Process * que);
int countHoles(char * mem);
double memUsagse(char * mem);
double culMemUsagse(Process * running);
void enque(char * infile,Process ** que);
void clearMemory(char * memory);
void checkFile(FILE * fp);
int bestHole(char * memory,int size);
void bestFit (char * memory, Process ** que);
void replaceMemory(char * memory, char rm, char replace);

void  eraseQue(Process ** que);
void  clean(Process ** que);
void deque (Process ** que);



int main (int argc, char * argv[])
{
	char * memory = malloc(sizeof(char)*129);
	Process * que = NULL;
	clearMemory(memory);


/*	printf("****************************FIRST FIT*************************************\n");
	que = enque(argv[1]);
	firstFit(memory,que);
	que= eraseQue(que);
*/
	printf("*****************************BEST FIT*************************************\n");
	enque(argv[1],&que);
	//printQue(que);
	//bestFit(memory,&que);

	//eraseQue(&que);
	

	free(memory);
	return 0;
}

void append (Process ** que, Process * toAdd)
{
	Process * temp=(*que);

	if(temp == NULL)
	{
		//printf("NULL QUE\n");
		*que = toAdd;
		toAdd->next = NULL;
		//printQue(*que);
		return;
	}

	while(quem->next != NULL)
	{
		temp = (*que)->next;
	}	
	printf("ADTER LAST QUE\n");
	printQue(*que);
	temp->next = toAdd;
	toAdd->next = NULL;
}

void enque (char * infile, Process ** que)
{
	FILE * fp;
	fp = fopen(infile,"r");
	checkFile(fp);
	//printf("beforew\n");
	char * line = malloc(sizeof(char)*20);
	while(fgets(line,20,fp)!=NULL)
	{
		//printf("in while\n");
		char tempID;
		int tempSize;

		sscanf(line,"%c %d",&tempID, &tempSize);
		append(que, create(tempID,tempSize,0));
		//printf("AFTER APPENDING\n");
		//printQue(*que);
		printf("\n");
		
	}
	fclose(fp);
	free(line);
}


void bestFit (char * memory, Process ** que)
{
	Process* running=NULL;
	int success=0;
	while((*que)!= NULL)
	{
		success= bestHole(memory,(*que)->size);
		while(success==-1)
		{	
			running->swaps++;
	
		    append(que,duplicate(running));
			printf("AFTER APPENDING DUE TO NO MEM\n");
			printQue(*que);
			clean(que);
			replaceMemory(memory,running->id,'0');
			deque(&running);
			success  = bestHole(memory,(*que)->size);
		}
		if(success!=-1)
		{
			int i;
			for(i=success;i<success+(*que)->size;i++)
			{
				memory[i]=(*que)->id;
			}

			append(&running,duplicate(*que));

			
			
		}
		deque(que);
		stats(running,memory);
		printf("CURRENTLY RUNNING\n");
		printQue(running);
		printf("CURRENT IN QUE\n");
		printQue(*que);
		print(memory);
		
	}
	printf("RUNNING:\n");
	printQue(running);
	printf("QUE\n");
	printQue(*que);	
}
















void deque (Process ** que)
{

	Process * temp=(*que);

	if ((*que) == NULL)
	{
		printf("EMPTY QUE\n");
		return;
	}

	(*que) = (*que)->next;
	free(temp);
}



void clean(Process ** que)
{
	Process* temp = (*que);

	if(temp->swaps>=3)
	{
		deque(que);

	}

	while(temp->next != NULL)
	{
		if(temp->next->swaps >=3)
		{
			Process * rm = temp->next;
			temp->next = temp->next->next;
			free(rm);
		}
		*temp = *temp->next;
		}
	if(temp->next == NULL && temp->swaps>=3)
	{
		Process * rm = temp;
		temp = NULL;
		free(rm);
	}
}


void eraseQue(Process ** que)
{
	while((*que)!= NULL)
	{
		Process * rm = *que;
		(*que) = (*que)->next;
		free(rm);
	}

	(*que)=NULL;
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

/* 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 
    0  0  0  0  0  0  0  0  0  0  a  a  a  a  0  0  0  0  0  0  b
*/


void checkFile(FILE * fp)
{
	if(fp==NULL)
	{
		printf("FILE EMPTY\n");
		exit(0);
	}
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





void printQue (Process * que)
{
	Process * temp  = que;
	if(que == NULL)
	{
		printf("EMPTY QUE\n");
		return;
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
	for(i=0;i<129;i++)
	{
		printf("%c  ", mem[i]);

	}
	printf("\n");
}

Process * duplicate (Process * source)
{
	return create(source->id,source->size,source->swaps);
}

void firstFit (char * memory, Process ** que)
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
		sum = loadProcess(memory,(*que));
	
		while (sum == 0) /*no hole big enough*/
		{
			
			int i=0;
			char oldestID = running->id; /* gets the head of the running que as oldest*/
			running->swaps++;/*update the swap tims right before swapping*/
			append(que,duplicate(running)); /*delets running process from where ever in the que and appends it to the back*/ 
			clean(que);/*remove and processes with threee or more swaps*/
			
			deque(&running);
			
			while(memory[i]!= oldestID)
			{
				i++;
			}

			while(memory[i]==oldestID)
			{
				memory[i]='0';
				i++;
			}
			sum = loadProcess(memory,(*que));
			if(sum == 1)
			{
				append(&running, duplicate(*que));
				stats(running,memory);
			}
		}

		deque(que);
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

double memUsagse(char * mem)
{
	int i=0;
	int freeCount = 0;
	double percent=0;

	while(mem[i]!= '1')
	{
		if(mem[i] == '0' )
		{
			freeCount++;
		}
		i++;
	}

	percent = (128-freeCount);
	percent = percent/128;
	percent = percent*100;
	return percent;

}

double culMemUsagse(Process * running)
{
	Process * temp =running;
	double sum = 0;
	double count =0;
	double percent=0;

	while(temp != NULL)
	{
		count ++;
		sum = sum + memusagse(temp);
		temp = temp->next;
	}
	//percent =  sum/count;
	return percent;

}



void stats(Process * que, char * mem)
{
	char * out = malloc(sizeof(char)*100);
	sprintf(out, "%c loaded, #processes %d, #holes %d, memusagse %.2lf, cumulative mem %.2lf\n", lastInQue(que)->id, countProcess(que), countHoles(mem), memUsagse(mem), culMemUsagse(que));
	printf("%s\n",out);
	free(out);
}

