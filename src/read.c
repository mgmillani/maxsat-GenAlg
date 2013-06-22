#include <stdio.h>
#include <stdlib.h>

#include "read.h"

#include "definitions.h"
#include "debug.h"

#define SIZE 128
#define CLAUSESIZE 20

/**
  * carrega um instancia do SAT a partir de um arquivo CNF
  * se a instancia passada for NULL, aloca uma nova
  */
t_instance *satLoadInstance(t_instance *inst,const char *fname)
{
	FILE *fl = fopen(fname,"rb");

	if( inst == NULL)
		inst = malloc(sizeof(*inst));

	char word[SIZE];
	int w = 0;
	unsigned int clauseIndex = 0;
	unsigned int numVars = 0;
	typedef enum {State_Ini, State_ReadSpace, State_Comment, State_ReadType, State_Vars, State_ReadWord,  State_ReadWordII, State_Problem, State_Clauses, State_ReadClause, State_AddVar} e_state;

	e_state state = State_Ini;
	e_state nextState = State_Ini;
	char read = 1;
	while(!feof(fl))
	{
		char c;
		if(read)
			c = fgetc(fl);

		switch(state)
		{
			case State_Ini:
				//se for um comentario, pula toda a linha
				if(c=='c')
					state = State_Comment;
				else if(c=='p')
					state = State_Problem;
				break;
			case State_Comment:
				if(ISEOL(c))
					state = State_Ini;
				break;

			//cnf <vars> <clauses>
			case State_Problem:
				state = State_ReadType;
				break;

			case State_ReadType:
				if(c==' ' || c=='\t')
				{
					w = 0;
					read = 1;
					state = State_ReadWord;
					nextState = State_Vars;
				}
				break;

			//le o numero de variavies, que esta em word
			case State_Vars:
				sscanf(word,"%u",&inst->numVars);
				inst->var = malloc(sizeof(*inst->var)*inst->numVars);
				read = 1;
				state = State_ReadWord;
				nextState = State_Clauses;
				break;

			//le o numero de clausas, que esta em word
			case State_Clauses:
				sscanf(word,"%u",&inst->numClauses);
				inst->clause = malloc(sizeof(*inst->clause)*inst->numClauses);
				read = 1;
				state = State_ReadSpace;
				nextState = State_ReadClause;

				break;

			case State_ReadClause:
				state = State_ReadWord;
				//inicializa a clausula atual
				clauseInit(inst->clause+clauseIndex,CLAUSESIZE);
				numVars = 0;
				nextState = State_AddVar;
				break;

			//adiciona um variavel a clausula atual
			//a variavel esta em word
			case State_AddVar:
				{
					int var;
					sscanf(word,"%d",&var);
					//getchar();
					unsigned char signal;
					//se a variavel for negativa, ela aparece negada na clausula
					if(var < 0)
					{
						signal = 1;
						var = -var;
					}
					//se for 0, terminou a clausula
					else if(var == 0)
					{
						//faz com que a clausula use o numero correto de variaveis
						if(numVars <= inst->clause[clauseIndex].size)
						{
							inst->clause[clauseIndex].size = numVars;
							inst->clause[clauseIndex].var = realloc(inst->clause[clauseIndex].var,sizeof(*inst->clause[clauseIndex].var)*numVars);
							inst->clause[clauseIndex].signal = realloc(inst->clause[clauseIndex].signal,sizeof(*inst->clause[clauseIndex].signal)*numVars);
						}
						clauseIndex++;
						numVars = 0;
						state = State_ReadSpace;
						nextState = State_ReadClause;
						break;
					}
					else
						signal = 0;
					//adiciona a variavel
					//verifica se eh necessario aumentar os arrays
					if(inst->clause[clauseIndex].size <= numVars)
					{
						inst->clause[clauseIndex].var = realloc(inst->clause[clauseIndex].var,sizeof(*inst->clause[clauseIndex].var)*numVars*2);
						inst->clause[clauseIndex].signal = realloc(inst->clause[clauseIndex].signal,sizeof(*inst->clause[clauseIndex].signal)*numVars*2);
						inst->clause[clauseIndex].size = numVars*2;
					}

					inst->clause[clauseIndex].var[numVars] = var;
					inst->clause[clauseIndex].signal[numVars] = signal;

					//aumenta o numero de variaveis lidas
					numVars++;
					read = 1;
					state = State_ReadWord;
					nextState = State_AddVar;
				}
				break;

			//le os espacos em branco
			case State_ReadSpace:
				if(!ISEOL(c) && !ISWHITESPACE(c))
				{
					read = 0;
					state = nextState;
				}
				else
					read = 1;
				break;

			//le os espacos em branco antes de uma palavra
			case State_ReadWord:
				if(!ISWHITESPACE(c) && !ISEOL(c))
				{
					w = 0;
					state = State_ReadWordII;
					read = 0;
				}
				else
					read = 1;
				break;

			case State_ReadWordII:
			if(ISWHITESPACE(c) || ISEOL(c))
			{
				word[w] = '\0';
				state = nextState;
				read = 0;
			}
			else
			{
				word[w++] = c;
				read = 1;
			}

			break;
		}
	}

	return inst;

}

/**
  * aloca uma clausula com o numero dado de literais
  */
t_clause *clauseInit(t_clause *clause,unsigned int literals)
{
	if(clause == NULL)
		clause = malloc(sizeof(*clause));

	clause->size = literals;

	clause->var = malloc(sizeof(*clause->var)*clause->size);
	clause->signal = malloc(sizeof(*clause->signal)*clause->size);

	return clause;
}


/**
  * printa todas as clausulas da instancia
  */
void showInstance(t_instance *inst)
{
	unsigned int i;
	for(i=0 ; i<inst->numClauses ; i++)
	{
		showClause(inst->clause+i);
	}
}

/**
  * printa as variaveis da clausula
  */
void showClause(t_clause *clause)
{
	unsigned int i;
	for(i=0 ; i<clause->size ;  i++)
	{
		if(clause->signal[i] == 1)
			printf("-%u ",clause->var[i]);
		else
			printf(" %u ",clause->var[i]);
	}
	printf("\n");
}













