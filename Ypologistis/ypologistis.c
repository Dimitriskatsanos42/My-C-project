
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define WORDS 10
# define SIZE   4

/** Mnimi kai registers **/
int memory[WORDS][SIZE];
int R1[SIZE];
int R2[SIZE];

 
   
/** i sunartisi epistrefei piso to plithos ton orismaton tis entolis **/ 
int splitCommand(char x[],char command[],char first[],char second[],char third[])
{
	int i,icount=0;
	char entoli[100];
	char orisma[100];
	int argumentCount=0;
	/* stin metabliti command mpainei i pragmatiki entoli pou einai na ektelestei **/
	/** stis metablites first, second,third mpenoun ta tria orismata tis entolis **/
	
	strcpy(command,"");
	strcpy(first,"");
	strcpy(second,"");
	strcpy(third,"");
	
	int flag=0; /** an to flag=0 diabazo entoli, allios diabazo orisma **/
	for(i=0;i<strlen(x);i++)
	{
		if(x[i]!=' ') 
		{
			if(flag==0)
			entoli[icount++]=x[i];
			else orisma[icount++]=x[i];
		}
		else
		{
			 if(flag==0)
			 {
			 entoli[icount]='\0';
			 flag=1;
			 strcpy(command,entoli);
			}
			else 
			{
				orisma[icount]='\0';
				++argumentCount;
				if(argumentCount==1) strcpy(first,orisma);
				else
				if(argumentCount==2) strcpy(second,orisma);
				else strcpy(third,orisma);
				
				
			}
			icount =0;
			
		 }
	}
	/** an to teleutaio gramma den itan keno **/
	if(x[strlen(x)-1]!=' ')
	{
		if(flag==0) 
		{
			entoli[icount]='\0';
						 strcpy(command,entoli);

		}
		else 
		{
			orisma[icount]='\0';
							++argumentCount;
				if(argumentCount==1) strcpy(first,orisma);
				else
				if(argumentCount==2) strcpy(second,orisma);
				else strcpy(third,orisma);
		}
	}
	return argumentCount;
}


/** ayti i sunartisi metrepei ena dyadiko arithmo (pinakas x) se dekadiko 
 * px. 1110 =>14 **/
int bin2dec(int x[])
{
	int total = 0;
	int i;
	for(i=0;i<SIZE;i++)
	  total = 2 * total + x[i];
	return total;
}
/** px 1234 **/
/* 4231*/
/* 4321*/
/* 4231*/
/* 1234*/
/** antistrefo ton pinaka x, giati kata tin metatropi apo dekadiko se 
 * dyadiko ta bits exoun mpei anapoda **/
void reverse(int x[])
{
	int i;
	for(i=0;i<SIZE/2;i++)
	{
		int t=x[i];
		x[i]=x[SIZE-i-1];
		x[SIZE-i-1]=t;
	}
}

/** i synartisi auti metatrpei to k se dyadiko arithmo **/
void dec2bin(int k,int x[])
{
	int b;
	int index=0;
	while(k!=0)
	{
		b= k % 2;
		x[index]=b;
		k=k/2;
	}
	reverse(x);
}

/** Epistrefei ena tyxaio bit **/
int randomBit()
{
	int x=rand() %2;
	if(x<0) x=-x;
	return x;
}

void boot()
{
	int i,j;
	for(i=0;i<WORDS;i++)
	{
		for(j=0;j<SIZE;j++)
		  memory[i][j]=randomBit();
	}
	for(i=0;i<SIZE;i++)
	{
		R1[i]=0;
		R2[i]=0;
	}
}

int loadR1(int address)
{
	int i;
	if(address<0 || address>=WORDS) return 0;
	for(i=0;i<SIZE;i++) R1[i]=memory[address][i];
	return 1;
}


int loadR2(int address)
{
	int i;
	if(address<0 || address>=WORDS) return 0;
	for(i=0;i<SIZE;i++) R2[i]=memory[address][i];
	return 1;
}

int storeR1(int address)
{
	int i;
	if(address<0 || address>=WORDS) return 0;
	for(i=0;i<SIZE;i++) memory[address][i]=R1[i];
	return 1;
}

int storeR2(int address)
{
	int i;
	if(address<0 || address>=WORDS) return 0;
	for(i=0;i<SIZE;i++) memory[address][i]=R2[i];
	return 1;
}

void addRegistersR1()
{
	int a,b,c,i;
	a=bin2dec(R1);
	b=bin2dec(R2);
	c=a+b;
	if(c>15) 
	{
		for(i=0;i<SIZE;i++) R1[i]=0;
	}
	else
	dec2bin(c,R1);
}

void addRegistersR2()
{
	int a,b,c,i;
	a=bin2dec(R1);
	b=bin2dec(R2);
	c=a+b;
	if(c>15) 
	{
		for(i=0;i<SIZE;i++) R2[i]=0;
	}
	else
	dec2bin(c,R2);
}

void subRegistersR1()
{
	int a,b,c,i;
	a=bin2dec(R1);
	b=bin2dec(R2);
	c=a-b;
	if(c<0) 
	{
		for(i=0;i<SIZE;i++) R1[i]=1;
	}
	else
	dec2bin(c,R1);
}


void subRegistersR2()
{
	int a,b,c,i;
	a=bin2dec(R1);
	b=bin2dec(R2);
	c=b-a;
	if(c<0) 
	{
		for(i=0;i<SIZE;i++) R2[i]=1;
	}
	else
	dec2bin(c,R2);
}

void displayR1()
{
	int i;
	printf("R1=[ ");
	for(i=0;i<SIZE;i++)
	 printf("%d",R1[i]);
    printf("]\n");
}


void displayR2()
{
	int i;
	printf("R2=[ ");
	for(i=0;i<SIZE;i++)
	 printf("%d",R2[i]);
    printf("]\n");
}

void displayMemory()
{
	int i,j;
	for(i=0;i<WORDS;i++)
	{
		for(j=0;j<SIZE;j++)
		  printf("%d",memory[i][j]);
		printf("\n");  
	}
}

/** pairnei san orisma dyo strings a,b kai epistrefei 1 an einai idia
 * kai 0 an den einai **/
int equals(char *a,char *b)
{
	int i;
	if(strlen(a)!=strlen(b)) return 0;
	for(i=0;i<strlen(a);i++)
	{
		if(a[i]!=b[i]) return 0;
	}
	return 1;
}


void saveInDisk()
{
	FILE *fp=fopen("computer.txt","w");
	int i,j;
	for(i=0;i<WORDS;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			fprintf(fp,"%d ",memory[i][j]);
		}
		fprintf(fp,"\n");
	}
	for(i=0;i<SIZE;i++)
	{
		fprintf(fp,"%d ",R1[i]);
	}
	fprintf(fp,"\n");
	
	for(i=0;i<SIZE;i++)
	{
		fprintf(fp,"%d ",R2[i]);
	}
	fprintf(fp,"\n");
	
	fclose(fp);
}

int main()
{
	char protasi[100];
	int args;
	char command[100],first[100],second[100],third[100];
	boot();
	do
	{
		gets(protasi);
		args=splitCommand(protasi,command,first,second,third);
		if(equals(command,"BOOT")) boot();
		else
		if(equals(command,"LOAD"))
		{
			if(equals(first,"R1"))
			{
				int address=atoi(second);
				loadR1(address);
			}
			else
			if(equals(first,"R2"))
			{
				int address=atoi(second);
				loadR2(address);
			}
			else
			printf("Wrong register !\n");
		}
		else
		if(equals(command,"STORE"))
		{
			if(equals(first,"R1"))
			{
				int address=atoi(second);
				storeR1(address);
			}
			else
			if(equals(first,"R2"))
			{
				int address=atoi(second);
				storeR2(address);
			}
			else
			printf("Wrong register !\n");
		} 
		else
		if(equals(command,"ADD"))
		{
			if(equals(first,"R1"))
			{
				addRegistersR1();
			}
			else
			if(equals(first,"R2"))
			{
				addRegistersR2();
			}
			else
			{
			printf("Wrong register !\n");
			}
		}
		else
		if(equals(command,"SUB"))
		{
			if(equals(first,"R1"))
			{
				subRegistersR1();
			}
			else
			if(equals(first,"R2"))
			{
				subRegistersR2();
			}
			else
			{
			printf("Wrong register !\n");
			}
		}
		else
		if(equals(command,"SHOW"))
		{
			if(equals(first,"R1"))
			{
				displayR1();
			}
			else
			if(equals(first,"R2"))
			{
				displayR2();
			}
			else
			{
			printf("Wrong register !\n");
			}
		}
		else
		if(equals(command,"MEM")) displayMemory();
		else
		if(equals(command,"SAVE"))
		{
			saveInDisk();
		}
	}while(1);
  return 0;
}
