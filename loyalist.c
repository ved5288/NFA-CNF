#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Linked-List part of the code */
//*****************************************************************************************//

struct production
{
	char* left;
	char* right1;
	char* right2;
	struct production* next;
} production;

struct list
{
	char* nt;
	struct list* next;
} list;

void small_printlist(struct list* head)
{
	struct list* current;
	current=head;
	if(head==NULL)
		printf("Empty List\n");
	while(current!=NULL)
	{
		printf("%s ",current->nt);
		current=current->next;
	}
	printf("\n");
}

void printlist(struct production* head)
{
	struct production* current;
	current=head;
	if(head==NULL)
		printf("Empty List\n");
	while(current!=NULL)
	{
		printf("%s -- > %s %s\n",current->left,current->right1,current->right2);
		current=current->next;
	}
return;	
}

void insert(struct production ** head,char* val1, char* val2, char* val3)
{
	struct production * new_production=(struct production*) malloc(sizeof(struct production));
	new_production->left=val1;
	new_production->right1=val2;
	new_production->right2=val3;
	new_production->next=*head;
	*head=new_production;
return;
}

void small_insert(struct list ** head,char* val)
{
	struct list* new_entry=(struct list*)malloc(sizeof(struct list));
	new_entry->nt=val;
	new_entry->next=*head;
	*head=new_entry;
}

struct list* small_search(struct list* head,char* val)
{
	struct list* current;
	if(head==NULL)
	{
		//printf("NoEntry\n");
		return NULL;
	}
	current=head;
	while(current!=NULL)
	{
		if(strcmp(current->nt,val)==0)
			return current;
		current=current->next;
	}
	return NULL;
}

struct production* search(struct production* head,char* val1,char* val2,char* val3)
{
	struct production* current;
	if(head==NULL)
	{
		printf("Empty List\n");
		return NULL;
	}
	current=head;
	while(current!=NULL)
		if(strcmp(val1,"x")==0)
			if(strcmp(val2,"x")==0)
				if(strcmp(val3,"x")==0)
					{
						printf("Nothing to Search\n");
						return NULL;
					}
				else
					{
						if(current->right2==val3)
							return current;
						current=current->next;
					}
					//search for only 3
			else 
				if(strcmp(val3,"x")==0)
					{
						if(current->right1==val2)
							return current;
						current=current->next;
					}
					//search for only 2
				else
					{
						if(current->right2==val3&&current->right1==val2)
							return current;
						current=current->next;
					}
					// search for 2 and 3
		else
			if(strcmp(val2,"x")==0)
				if(strcmp(val3,"x")==0)
					{
						if(current->left==val1)
							return current;
						current=current->next;
					}
					//search for only 1
				else
					{
						if(current->right2==val3&&current->left==val1)
							return current;
						current=current->next;
					}
					//search for 1 and 3
			else
				if(strcmp(val3,"x")==0)
					{
						if(strcmp(current->right1,val2)==0&&strcmp(current->left,val1)==0)
							return current;
						current=current->next;
					}
					//search for only 1 and 2
				else
					{
						if(current->right2==val3&&current->right1==val2&&current->left==val1)
							return current;
						current=current->next;
					}
					//search for 1,2 and 3
	return NULL;
}

void delete(struct production ** head,char* val1,char* val2,char* val3)
{
	if(*head==NULL)
	{
		printf("Empty List\n");
		return;
	}
	struct production* to_delete=search(*head,val1,val2,val3);
	struct production* reg2_node;
	struct production* current=*head;
	struct production* parent=NULL;
	
	while(current!=to_delete&&current!=NULL)
	{
		parent=current;
		current=current->next;
	}
	if(current==NULL)
	{
		printf("Element not found\n");
		return;
	}
	reg2_node=current;
	current=*head;
	if(parent!=NULL)
	{
		while(current!=parent)
			current=current->next;
		parent->next=reg2_node->next;
		free(reg2_node);
		return;	
	}
	current=(*head)->next;
	free(*head);
	*head=current;
return;	
}
/* End of linked list part of code */
//********************************************************************************************************//

/* The following part of the code prints all the productions */

//********************************************************************************************************//
void add_production(char* S,char* R,char* P,struct production** head)
{
	insert(head,S,R,P);
return;
}

char* change_to_string(char a)
{
	char* unit=(char*)malloc(sizeof(char)*2);
	unit[0]=a;
	unit[1]='\0';
	return (char*)unit;
}

int production_number=0;

char* current_production()
{
	char *s = (char*)malloc(sizeof(char)*3);
	s[0]='R';
	s[1]=production_number+'0';
	s[2]='\0';
	production_number++;
	return (char*)s;
}

void make_productions(int start,int end,char* entry, char* exp,struct production** head)
{
	char *reg1,*reg2;
	int i,count1=0,k;

	if(end-start==2)
	{
		char* unit=change_to_string(exp[start+1]);
		add_production(entry,(char*)unit,"00",head);
		return;
	}
	if(end-start==0)
	{
		char* unit=change_to_string(exp[start]);
		add_production(entry,(char*)unit,"00",head);
		return;
	}

	for(i=start;i<=end;i++)
	{
		if(exp[i]=='(')
			count1++;
		else if (exp[i]==')')
			count1--;
		if((count1==1)&&(exp[i]=='+'||exp[i]=='.'||exp[i]=='*'))
		{
			k=i;
			break;
		}
	}
	reg1=current_production();

	if(exp[k]!='*')
		reg2=current_production();

	if(exp[k]=='+')
	{
		add_production(entry,reg1,"0",head);
		add_production(entry,reg2,"0",head);
	}
	else if(exp[k]=='.')
		add_production(entry,reg1,reg2,head);
	else if(exp[k]=='*')
	{
		add_production(entry,entry,reg1,head);
		add_production(entry,"#","0",head);
	}
	make_productions(start+1,k-1,reg1,exp,head);
	if(exp[k]!='*')
		make_productions(k+1,end-1,reg2,exp,head);
return;
}

//***************************************************************************************************//

/* Remove Ephsilon Productions */
//***************************************************************************************************//

void remove_ephsilon_productions(struct production** head)
{
	struct production* ephsilon=*head;
	struct production* temp;
	while(ephsilon!=NULL)
	{
		ephsilon=search(ephsilon,"x","#","x");
		if(ephsilon!=NULL)
		{
			int flag=0;
			temp=*head;
			while(temp!=NULL)
			{
				temp=search(temp,"x","x",ephsilon->left);
				if(temp!=NULL)
				{
					add_production(temp->left,temp->right1,"0",head);
					temp=temp->next;				
				}
			}
			temp=*head;
			while(temp!=NULL)
			{
				temp=search(temp,"x",ephsilon->left,"x");
				if(temp!=NULL)
				{	
					if(temp->right2=="0")
					{
						add_production(temp->left,"#","0",head);
						flag=1; 		// restart from *head					
					}	
					else
					{
						add_production(temp->left,temp->right2,"0",head);
					}	
					temp=temp->next;		
				}
			}		
			temp=ephsilon->next;
			delete(head,ephsilon->left,ephsilon->right1,ephsilon->right2);	
			if (flag==0) ephsilon=temp;
			else ephsilon=*head;
		}
	}
}

//***************************************************************************************************//


/* Remove Unit Productions */
//***************************************************************************************************//

void remove_unit_productions(struct production** head)
{
	struct production* unit=*head;
	struct production* temp;
	while(unit!=NULL)
	{
		unit=search(unit,"x","x","0");
		if(unit!=NULL)
		{
			int flag=0;	
			temp=*head;
			while(temp!=NULL)
			{
				temp=search(temp,unit->right1,"x","x");
				if(temp!=NULL)
				{
					add_production(unit->left,temp->right1,temp->right2,head);
					if(temp->right2=="0")
						flag=1;
					temp=temp->next;
				}
			}
			while(temp!=NULL)
			{
				temp=search(temp,unit->right1,"x","00");
				if(temp!=NULL)
				{
					add_production(unit->left,temp->right1,"00",head);
					temp=temp->next;
				}
			}	
			
			temp=unit->next;
			delete(head,unit->left,unit->right1,unit->right2);	
			if (flag==0) unit=temp;
			else unit=*head;
		}
	}
	
}

//***************************************************************************************************//

// CYK Algorithm ------------------------------------------------------------------------------------//
int check_if_present(char* string,struct production** head,char* start_state)
{
	int n=strlen(string),i,j,m;
	struct production* temp;
	struct list* T[n+1][n+1];

	for(i=0;i<=n;i++)
	for(j=0;j<=n;j++)
		T[i][j]=NULL;

	temp=*head;
	while(temp!=NULL)
	{
		temp=search(temp,"x","x","00");
		if(temp!=NULL)
		{
			for(i=0;i<n;i++)
			if(string[i]==temp->right1[0])
				small_insert(&T[i][i+1],temp->left);
			temp=temp->next;			
		}
	}

	for(m=2;m<=n;m++)
	for(i=0;i<=n-m;i++)
	for(j=i+1;j<n;j++)
	{
		struct list* temp1;
		struct list* temp2;
		temp1=T[i][j];
		while(temp1!=NULL)
		{
			char* P1=temp1->nt;
			temp2=T[j][i+m];
			while(temp2!=NULL)
			{
				char* P2=temp2->nt;
				struct production* temp;
				temp=*head;
				while(temp!=NULL)
				{
					temp=search(temp,"x",P1,P2);
					if(temp!=NULL)
					{
						if(small_search(T[i][i+m],temp->left)==NULL)
							small_insert(&T[i][i+m],temp->left);
						temp=temp->next;
					}
				}
				temp2=temp2->next;
			}
			temp1=temp1->next;
		}
	}
	if(small_search(T[0][n],start_state)!=NULL)
		return 1;
	return 0;
}
//--------------------------------------------------------------------------------------------------//

struct NFA
{
	char* start_state;
	char* final_state;
	struct production* transition_func;
	struct list* states;
};

// Make NFA ****************************************************************************************//
void make_NFA(int start,int end,char* entry, char* exit, char* exp,struct NFA* regex)
{
	char *reg1,*reg2,*reg3,*reg4;
	int i,count1=0,k;

	if(end-start==2)
	{
		char* unit=change_to_string(exp[start+1]);
		add_production(entry,(char*)unit,exit,&regex->transition_func);
		regex->start_state=entry;
		regex->final_state=exit;
		if(small_search(regex->states,entry)==NULL)
			small_insert(&regex->states,entry);
		if(small_search(regex->states,exit)==NULL)
			small_insert(&regex->states,exit);
		return;
	}
	if(end-start==0)
	{
		char* unit=change_to_string(exp[start]);
		add_production(entry,(char*)unit,exit,&regex->transition_func);
		regex->start_state=entry;
		regex->final_state=exit;
		if(small_search(regex->states,entry)==NULL)
			small_insert(&regex->states,entry);
		if(small_search(regex->states,exit)==NULL)
			small_insert(&regex->states,exit);
		return;
	}

	for(i=start;i<=end;i++)
	{
		if(exp[i]=='(')
			count1++;
		else if (exp[i]==')')
			count1--;
		if((count1==1)&&(exp[i]=='+'||exp[i]=='.'||exp[i]=='*'))
		{
			k=i;
			break;
		}
	}
	reg1=current_production();
	reg2=current_production();

	if(exp[k]=='+')
	{
		reg3=current_production();
		reg4=current_production();
		make_NFA(start+1,k-1,reg1,reg3,exp,regex);
		make_NFA(k+1,end-1,reg2,reg4,exp,regex);
		add_production(entry,"#",reg1,&regex->transition_func);
		add_production(entry,"#",reg2,&regex->transition_func);
		add_production(reg3,"#",exit,&regex->transition_func);
		add_production(reg4,"#",exit,&regex->transition_func);
		if(small_search(regex->states,reg1)==NULL)
			small_insert(&regex->states,reg1);
		if(small_search(regex->states,reg2)==NULL)
			small_insert(&regex->states,reg2);
		if(small_search(regex->states,reg3)==NULL)
			small_insert(&regex->states,reg3);
		if(small_search(regex->states,reg4)==NULL)
			small_insert(&regex->states,reg4);
	}
	else if(exp[k]=='.')
	{
		reg3=current_production();
		reg4=current_production();
		make_NFA(start+1,k-1,reg1,reg3,exp,regex);
		make_NFA(k+1,end-1,reg2,reg4,exp,regex);
		add_production(entry,"#",reg1,&regex->transition_func);
		add_production(reg3,"#",reg2,&regex->transition_func);
		add_production(reg4,"#",exit,&regex->transition_func);
		if(small_search(regex->states,reg1)==NULL)
			small_insert(&regex->states,reg1);
		if(small_search(regex->states,reg2)==NULL)
			small_insert(&regex->states,reg2);
		if(small_search(regex->states,reg3)==NULL)
			small_insert(&regex->states,reg3);
		if(small_search(regex->states,reg4)==NULL)
			small_insert(&regex->states,reg4);
	}
	else if(exp[k]=='*')
	{
		make_NFA(start+1,k-1,reg1,reg2,exp,regex);
		add_production(entry,"#",reg1,&regex->transition_func);
		add_production(entry,"#",exit,&regex->transition_func);
		add_production(reg2,"#",exit,&regex->transition_func);
		add_production(reg2,"#",reg1,&regex->transition_func);
		if(small_search(regex->states,reg1)==NULL)
			small_insert(&regex->states,reg1);
		if(small_search(regex->states,reg2)==NULL)
			small_insert(&regex->states,reg2);
	}
return;
}

// Check if accepted -------------------------------------------------------------------------------//
int check_if_accepted(char* string,struct NFA* head,char* start_state,char* final_state)
{
	int n=strlen(string),i;
	struct list* Reachable[n+1];
	struct production* random;
	struct list* temp,*temp1;
	for(i=0;i<=n;i++)
		Reachable[i]=NULL;
	
	small_insert(&Reachable[0],start_state);

	for(i=0;i<=n;i++)
	{
		char s[2];;
		s[0]=string[i-1];
		s[1]='\0';
	
		if(i>0)
		{
			temp=Reachable[i-1];
			while(temp!=NULL)
			{
				random=head->transition_func;
				while(random!=NULL)
				{			
					random=search(random,temp->nt,(char*)s,"x");
					if(random!=NULL)
					{
						if(small_search(Reachable[i],random->right2)==NULL)
							small_insert(&Reachable[i],random->right2);
						random=random->next;
					}
				}
				temp=temp->next;
			}

			
			//use, transition from Reachable[i-1] to Reachable[i]
		}
		// do "#" transitions from itself
		temp=Reachable[i];
		while(temp!=NULL)
		{
			int flag=0;
			random=head->transition_func;
			while(random!=NULL)
			{
				random=search(random,temp->nt,"#","x");
				if(random!=NULL)
				if(small_search(Reachable[i],random->right2)==NULL)
				{

					small_insert(&Reachable[i],random->right2);
					flag=1;					
					random=random->next;
					
				}
				else random=random->next;
			}
			if(flag==1)
				temp=Reachable[i];
			else temp=temp->next;
		}
		
	}
	
	if(small_search(Reachable[n],final_state)!=NULL)
		return 1;
	return 0;
}


//--------------------------------------------------------------------------------------------------//

// *************************************************************************************************//

int main()
{
struct production* PROD=NULL;
struct production* reg_exp=NULL;
struct NFA* automaton=(struct NFA*)malloc(sizeof(struct NFA));

add_production("R0","a","00",&reg_exp);
add_production("R0","b","00",&reg_exp);
add_production("R0","c","00",&reg_exp);
add_production("R0","d","00",&reg_exp);
add_production("R0","e","00",&reg_exp);
add_production("R0","f","00",&reg_exp);
add_production("R0","g","00",&reg_exp);
add_production("R0","h","00",&reg_exp);
add_production("R0","i","00",&reg_exp);
add_production("R0","j","00",&reg_exp);
add_production("R0","k","00",&reg_exp);
add_production("R0","l","00",&reg_exp);
add_production("R0","m","00",&reg_exp);
add_production("R0","n","00",&reg_exp);
add_production("R0","o","00",&reg_exp);
add_production("R0","p","00",&reg_exp);
add_production("R0","q","00",&reg_exp);
add_production("R0","r","00",&reg_exp);
add_production("R0","s","00",&reg_exp);
add_production("R0","t","00",&reg_exp);
add_production("R0","u","00",&reg_exp);
add_production("R0","v","00",&reg_exp);
add_production("R0","w","00",&reg_exp);
add_production("R0","x","00",&reg_exp);
add_production("R0","y","00",&reg_exp);
add_production("R0","z","00",&reg_exp);
add_production("R0","A","00",&reg_exp);
add_production("R0","B","00",&reg_exp);
add_production("R0","C","00",&reg_exp);
add_production("R0","D","00",&reg_exp);
add_production("R0","E","00",&reg_exp);
add_production("R0","F","00",&reg_exp);
add_production("R0","G","00",&reg_exp);
add_production("R0","H","00",&reg_exp);
add_production("R0","I","00",&reg_exp);
add_production("R0","J","00",&reg_exp);
add_production("R0","K","00",&reg_exp);
add_production("R0","L","00",&reg_exp);
add_production("R0","M","00",&reg_exp);
add_production("R0","N","00",&reg_exp);
add_production("R0","O","00",&reg_exp);
add_production("R0","P","00",&reg_exp);
add_production("R0","Q","00",&reg_exp);
add_production("R0","R","00",&reg_exp);
add_production("R0","S","00",&reg_exp);
add_production("R0","T","00",&reg_exp);
add_production("R0","U","00",&reg_exp);
add_production("R0","V","00",&reg_exp);
add_production("R0","W","00",&reg_exp);
add_production("R0","X","00",&reg_exp);
add_production("R0","Y","00",&reg_exp);
add_production("R0","Z","00",&reg_exp);
add_production("R1","R2","R0",&reg_exp);
add_production("R2","(","00",&reg_exp);
add_production("R3","R0","R4",&reg_exp);
add_production("R4",")","00",&reg_exp);
add_production("R0","R1","R5",&reg_exp);
add_production("R5","R6","R3",&reg_exp);
add_production("R6","+","00",&reg_exp);
add_production("R0","R1","R7",&reg_exp);
add_production("R7","R8","R3",&reg_exp);
add_production("R8",".","00",&reg_exp);
add_production("R0","R1","R9",&reg_exp);
add_production("R9","R10","R4",&reg_exp);
add_production("R10","*","00",&reg_exp);

	automaton->start_state=current_production();
	automaton->final_state=current_production();
	automaton->transition_func=NULL;
	automaton->states=NULL;
	if(small_search(automaton->states,automaton->start_state)==NULL)
		small_insert(&automaton->states,automaton->start_state);
	if(small_search(automaton->states,automaton->final_state)==NULL)
		small_insert(&automaton->states,automaton->final_state);
		
	
	int i,j;
	char reg_string[100];
	scanf("%s",reg_string);
	if(check_if_present((char*)reg_string,&reg_exp,"R0")==0)
		{
			printf("Wrong Expression\n");
			return 0;
		}
	char* reg2,start_state[2],*reg1;
	printf("\nType 1 to check via NFA\nType 2 to check by constructing a CNF\n");
	int l;
	scanf("%d",&l);

	reg2=current_production();
	start_state[0]=reg2[0];
	start_state[1]=reg2[1];
	start_state[2]='\0';
	i=strlen(reg_string);
	make_productions(0,i-1,start_state,reg_string,&PROD);
	reg1=automaton->start_state;
	reg2=automaton->final_state;
	make_NFA(0,i-1,automaton->start_state,automaton->final_state,reg_string,automaton);
	remove_ephsilon_productions(&PROD);
	remove_unit_productions(&PROD);
		
	int n;
	printf("Number of test cases : ");
	scanf("%d",&n);
	for(j=0;j<n;j++)
	{
		char exp[100000];
		scanf("%s",exp);
		if(l==2)
		if(check_if_present((char*)exp,&PROD,start_state)==1)
			printf("Yes\n");
		else printf("No\n");
		if(l==1)
		if(check_if_accepted((char*)exp,automaton,reg1,reg2)==1)	
			printf("Yes\n");
		else printf("No\n");
	}

return 0;
}
