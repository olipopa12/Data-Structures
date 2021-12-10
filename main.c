#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

int initialize() {
	Species_head = NULL;
	Species_tail = NULL;
	for (int i = 0; i < 5; i++) {
		continents[i] = NULL;
	}
	hs_L = NULL;
	return 1;
}
int printpop();
int insert_species(int sid) {
	struct Species* S = (struct Species*)malloc(sizeof(struct Species));
	struct Species* head = Species_head;
	S->Population_head = NULL;
	S->Population_tail = NULL;
	S->sid = sid;
	if (head == NULL) {
		S->next = NULL;
		S->prev = NULL;
		Species_head = Species_tail = S;
		print_populations();
		return 1;
	}
	if (head->sid > S->sid) { //prepei na mpei se sxolia
		Species_head = S;
		Species_head->next = head;
		Species_head->prev = NULL;
		if (head->next == NULL) {
			Species_tail = head;
			Species_tail->prev = S;
		}
		print_populations();
		return 1;
	}
	while (head->next != NULL) {


		if (head->next->sid > S->sid) {
			S->next = head->next;
			S->prev = head;
			head->next->prev = S;
			head->next = S;
			print_populations();
			return 1;
		}
		head = head->next;
	}
	if (head->next == NULL) {
		if ((head->sid) < S->sid) {
			head->next = S;
			S->next = NULL;
			S->prev = head;
			Species_tail = S;
		}
		else {
			head = S;
			head->next = head;
			head->prev = NULL;
		}
	}
	print_populations();
	return 1;
}

int insert_population(int gid, int sid, int cid) {
	struct Population* P = (struct Population*)malloc(sizeof(struct Population));
	struct Population* prev;
	struct Population* Phead;
	//Phead = Species_head->Population_head;
	P->gid = gid;
	P->cid = cid;
	P->sid = sid;
	struct Species* Shead = Species_head;
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		prev = Phead;
		if (Shead->sid == P->sid) {
			if (Phead == NULL) {
				Shead->Population_head = Shead->Population_tail = P;
				Shead->Population_head->next = NULL;
				printpop();
				return 1;
			}
			if (Phead->gid > P->gid) {
				P->next = Phead;
				Phead = P;
				Shead->Population_head = P;
				printpop();
				return 1;

			}
			while (Phead->next != NULL) {
				if (Phead->next->gid > P->gid) {
					P->next = Phead->next;
					Phead->next = P;
					printpop();
					return 1;
				}
				//prev = Phead;
				Phead = Phead->next;
			}
			if (Phead->next == NULL) {
				//prev = P;
				Phead->next = P;
				Shead->Population_tail = P;
				P->next = NULL;
				printpop();
				return 1;
			}

		}
		Shead = Shead->next;
	}

	return 0;
}
int printpop() {
	struct Species*Shead = Species_head;
	struct Population*Phead=NULL;
	
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		printf(" <%d>\n", Shead->sid);
		if (Phead != NULL){
			while (Phead->next != NULL) {
				printf("  <%d,%d>,", Phead->gid, Phead->cid);
				Phead = Phead->next;
			}
		if (Phead->next == NULL) {
			printf("  <%d,%d>", Phead->gid, Phead->cid);
		}
	}
			printf("\n");
			Shead = Shead->next;
		}
		return 1;
	
}
int insert_species_no_print(int sid) {
	struct Species* S = (struct Species*)malloc(sizeof(struct Species));
	struct Species* head = Species_head;
	S->Population_head = NULL;
	S->Population_tail = NULL;
	S->sid = sid;
	if (sid == 13)
	{
		printf(" found\n");
	}
	if (head == NULL) {
		S->next = NULL;
		S->prev = NULL;
		Species_head = Species_tail = S;
		//print_populations();
		return 1;
	}
	if (head->sid > S->sid) {
		Species_head = S;
		Species_head->next = head;
		Species_head->prev = NULL;
		Species_tail = head;
		Species_tail->prev = S;
		//print_populations();
		return 1;
	}
	while (head->next != NULL) {


		if (head->next->sid > S->sid) {
			S->next = head->next;
			S->prev = head;
			head->next->prev = S;
			head->next = S;
			//print_populations();
			return 1;
		}
		head = head->next;
	}
	if (head->next == NULL) {
		if ((head->sid) < S->sid) {
			head->next = S;
			S->next = NULL;
			S->prev = head;
			Species_tail = S;
		}
		else {
			head = S;
			head->next = head;
			head->prev = NULL;
		}
	}
	return 1;
}
int merge_species(int sid1, int sid2, int sid3) {
	struct Species* Shead, *Shead2 = NULL;
	struct Population* tmp, *ptr1 = NULL;
	struct Population* ptr2 = NULL;
	struct Population* ptr3 = NULL;

	insert_species_no_print(sid3);
	Shead = Species_head;

	while (Shead != NULL) {
		if (Shead->sid == sid1) {
			ptr1 = Shead->Population_head;
		}
		else if (Shead->sid == sid2) {
			ptr2 = Shead->Population_head;
		}
		else if (Shead->sid == sid3) {
			
			Shead2 = Shead;
		}
		Shead = Shead->next;
	}
	if (ptr1->gid > ptr2->gid) {
		
		Shead2->Population_head = ptr2;
		ptr2 = ptr2->next;
	}
	else if (Shead2!=NULL) {
		
		Shead2->Population_head = ptr1;
		ptr1 = ptr1->next;
	}
	ptr3 = Shead2->Population_head;
	while ((ptr1 != NULL) && (ptr2 != NULL)) {
		if (ptr1->gid > ptr2->gid) {
			ptr3->next = ptr2;
			ptr3->next->sid = sid3;
			ptr2 = ptr2->next;
			
		}
		else {
			ptr3->next = ptr1;
			ptr3->next->sid = sid3;
			ptr1 = ptr1->next;
			
		}
		ptr3 = ptr3->next;
	}
	if (ptr1 == NULL) {
		ptr3->next = ptr2;
		ptr3->next->sid = sid3;
	}
	if (ptr2 == NULL) {
		ptr3->next = ptr1;
		ptr3->next->sid = sid3;
	}

	Shead = Species_head;
	while (Shead != NULL) {
		if ((Shead->sid == sid1) || (Shead->sid == sid2)) {
			if ((Shead->prev != NULL) && (Shead->next != NULL)) {
				Shead->prev->next = Shead->next;
				Shead->next->prev = Shead->prev;
			}
			else {
				if (Shead->prev == NULL) {
					Shead->next->prev = NULL;
					Species_head = Shead->next;
				}
				if (Shead->next == NULL) {
					Shead->prev->next = Shead->next;
					Species_tail = Shead->prev;
				}
			}
		}
		Shead = Shead->next;
	}
	print_populations();
	return 1;
}
int distribute() {
	struct Species* Shead																			 = Species_head;
	struct Population* Phead;	
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		while (Phead != NULL) {
			if (continents[Phead->cid] == NULL) {
				continents[Phead->cid] = (struct ContinentList*)malloc(sizeof(struct ContinentList));
				continents[Phead->cid]->populationList = Phead;
				continents[Phead->cid]->sentinel = (struct ContinentList*)malloc(sizeof(struct ContinentList));
				//continents[Phead->cid]->sentinel = continents[Phead->cid]->populationList;
				continents[Phead->cid]->sentinel->gid = Phead->gid;
				continents[Phead->cid]->populationList = continents[Phead->cid]->sentinel;
			}
			else
			{
				continents[Phead->cid]->sentinel->next = (struct ContinentList*)malloc(sizeof(struct ContinentList));
				continents[Phead->cid]->sentinel->next->gid = Phead->gid;
				continents[Phead->cid]->sentinel = continents[Phead->cid]->sentinel->next;
				//continents[Phead->cid]->sentinel = Phead;

			}
			//Phead->sid = Shead->sid;
			Phead = Phead->next;
		}
		Shead = Shead->next;
	}

	for (int i = 0; i < 5; i++) {
		if (continents[i] != NULL) {
			continents[i]->sentinel->next = (struct ContinentList*)malloc(sizeof(struct ContinentList));
			continents[i]->sentinel = continents[i]->sentinel->next;
			continents[i]->sentinel->gid = -1;
			continents[i]->sentinel->next = NULL;
		}
	}

	
	print_continents();

	return 1;
}
int delete_population(int gid, int sid) {
	struct Species* Shead = Species_head;
	struct Population* Phead, *Prev;
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		Prev = NULL;
		if (Shead->sid == sid) {
			while (Phead != NULL) {
				if (Phead->gid == gid) {
					if ((Prev != NULL) && (Phead->next != NULL)) {
						Prev->next = Phead->next;
						//Shead->next->prev = Shead->prev;
					}
					else {
						if (Prev == NULL) {
							Shead->Population_head = Phead->next;
						}
						else if (Phead->next == NULL) {
							Prev->next = NULL;
							Shead->Population_tail = Prev;
						}
						else if ((Prev == NULL) && (Phead->next == NULL)) {
							Shead->Population_head = NULL;

						}
					}
				}
				Prev = Phead;
				Phead = Phead->next;
			}
		}
		//Prev = Shead;
		Shead = Shead->next;
	}
	struct ContinentPopulation* ptr, *prev;
	for (int i = 0; i < 5; i++) {
		if (continents[i] != NULL) {
			ptr = continents[i]->populationList;
			prev = NULL;
			while (ptr != NULL) {
				if (ptr->gid == gid) {
					if ((prev != NULL) && (ptr->next != NULL)) {
						prev->next = ptr->next;
						//Shead->next->prev = Shead->prev;
					}
					else {
						if (prev == NULL) {
							continents[i]->populationList = ptr->next;
						}
						else if (ptr->next == NULL) {
							prev->next = NULL;
							//Shead->Population_tail = prev;
						}
						else if ((prev == NULL) && (ptr->next == NULL)) {
							continents[i]->populationList = NULL;

						}
					}
				}
				prev = ptr;
				ptr = ptr->next;
			}
		}
	}
	 Shead = Species_head;
	printf("SPECIES\n");
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		printf(" <%d>\n", Shead->sid);
		while (Phead != NULL) {
			printf("  <%d> ", Phead->gid);
			Phead = Phead->next;
		}
		Shead = Shead->next;
		printf("\n");
	}
	struct ContinentPopulation* contptr;

	printf("CONTINENTS\n");
	for (int i = 0; i < 5; i++) {
		if (continents[i] != NULL)
		{

			contptr = continents[i]->populationList;
			printf(" Continent %d :", i);
			if (contptr == NULL) return 0;
			while ((contptr->next != continents[i]->sentinel) && (contptr != NULL))
			{
				printf("<%d>,", contptr->gid);
				contptr = contptr->next;
			}
			if (contptr->next == continents[i]->sentinel) {
				printf("<%d>", contptr->gid);

			}
			printf("\n");
		}
	}
	return 1;
}
int delete_species(int sid) {
	struct Species* Stail = Species_tail;
	struct Population* Phead = NULL;
	struct ContinentPopulation *contptr = NULL, *prev = NULL;
	while (Stail != NULL) {
		if (Stail->sid == sid) {
			Phead = Stail->Population_head;
			while (Phead != NULL) {
				contptr = continents[Phead->cid]->populationList;
				prev = NULL;
				if (contptr != NULL) {
					while (contptr != continents[Phead->cid]->sentinel) {
						if (contptr->gid == Phead->gid) {
							if (prev == NULL) {
								continents[Phead->cid]->populationList = contptr->next;
							}
							else {
								prev->next = contptr->next;
							}
							if ((prev == NULL) && (contptr->next == NULL)) {
								continents[Phead->cid]->populationList = NULL;

							}
						}
						prev = contptr;
						contptr = contptr->next;
					}
				}
				Phead = Phead->next;
			}
			Stail->Population_head = NULL;
			if ((Stail->prev == NULL) && (Stail->next == NULL)) {
				Species_head = Species_tail = NULL;
				//return 1;
			}
			else if (Stail->prev == NULL) {
				Species_head = Stail->next;
				//return 1;
			}
			else if (Stail->next == NULL) {
				Species_tail = Stail->prev;
				//return 1;
			}
			else {
				Stail->prev->next = Stail->next;
				Stail->next->prev = Stail->prev;
			}

		}
		Stail = Stail->prev;
	}
	struct Species* Shead = Species_head;
	//printf("F <%d>\n", sid);
	printf("SPECIES\n");
	while (Shead != NULL) {
		Phead = Shead->Population_head;
		printf(" <%d>\n", Shead->sid);
		while (Phead != NULL) {
			printf("  <%d> ", Phead->gid);
			Phead = Phead->next;
		}
		Shead = Shead->next;
		printf("\n");
	}
	printf("CONTINENTS\n");
	for (int i = 0; i < 5; i++) {
		if (continents[i] != NULL)
		{

			contptr = continents[i]->populationList;
			printf(" Continent %d :", i);
			if (contptr == NULL) return 0;
			while ((contptr->next != continents[i]->sentinel) && (contptr != NULL))
			{
				printf("<%d>,", contptr->gid);
				contptr = contptr->next;
			}
			if (contptr->next == continents[i]->sentinel) {
				printf("<%d>", contptr->gid);

			}
			printf("\n");
		}
	}
	
	return 1;
}

/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution() {
	struct Population* HS = hs_L;
	struct Species* Shead = Species_head, *Prev = Species_head;
	struct Population* Phead, *Ptail;
	while (Shead != NULL) {
		Phead = Prev->Population_head;
		Ptail = Prev->Population_tail;
		if (Shead->Population_head != NULL) {
			Shead->Population_head->next_species = NULL;
		}
		if (HS == NULL) {
			hs_L = Shead->Population_head;
			HS = hs_L;
		}
		
			if ((Shead->Population_head == NULL)) {
				while ((Shead != NULL)&&(Shead->Population_head == NULL)) {
					Shead = Shead->next;
				}
				continue;
			}

			else if ((Prev != Shead) && (Phead != NULL) && (Ptail != NULL))
			{

				Phead->next_species = Shead->Population_head;
				Ptail->next = Shead->Population_head;
				Prev = Shead;


			}
			else if (Phead == NULL)
			{
				Prev = Shead;
			}

			Shead = Shead->next;

		

	}

	HS = hs_L;
	printf("E\n Homo Sapiens:");
	while (HS->next != NULL) {
		printf("<%d,%d>,", HS->gid, HS->sid);
		HS = HS->next;
	}
	if (HS->next == NULL) {
		printf("<%d,%d>\n", HS->gid, HS->sid);
	}
	return 1;
}

/**
 * @brief Gather statistics on species from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics() {
	struct Population* HS = hs_L;
	int counter = 0;
	while (HS != NULL) {
		counter++;
		HS = HS->next_species;
	}
	printf(" Homo Sapiens Species:<%d>\n", counter);
	return 1;
}

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid) {
	struct Population* HS = hs_L;
	int counter = 0;
	//printf("J \n",sid);
	while (HS != NULL) {
		if (HS->sid == sid) {
			while ((HS != NULL) && (HS->sid == sid)) {
				counter++;
				HS = HS->next;
			}
			printf(" Homo Sapiens Populations:<%d>\n", counter);
			return 1;
		}
		HS = HS->next_species;
	}
	return 1;
}

/**
 * @brief Print species' list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species() {
	struct Species* Shead = Species_head;
	printf(" ");
	if (Shead == NULL) return 0;
	while (Shead->next != NULL) {
		printf("<%d>,", Shead->sid);
		Shead = Shead->next;
	}
	if (Shead->next == NULL) {
		printf("<%d>\n", Shead->sid);
	}
	return 1;
}

/**
 * @brief Print species' list with population lists
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations() {
	struct Species* Shead = Species_head;
	struct Population* Phead;
	while (Shead != NULL) {
		printf("\n <%d>\n", Shead->sid);
		Phead = Shead->Population_head;
		while ((Phead!=NULL)&&(Phead != Shead->Population_tail)) {
			printf("  <%d,%d>,", Phead->gid, Phead->cid);
			Phead = Phead->next;
		}
		if (Phead == Shead->Population_tail) {
			printf("  ");
		}
		if (Shead->Population_tail != NULL) {
			printf("<%d,%d>", Shead->Population_tail->gid, Shead->Population_tail->cid);
		}
		Shead = Shead->next;

	}
	printf("\n");
	return 1;
}

/**
 * @brief Print continents array with each continent's population list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents() {
	struct ContinentPopulation* ptr;
	for (int i = 0; i < 5; i++) {
		if (continents[i] != NULL)
		{

			ptr = continents[i]->populationList;
			printf("Continent %d:", i);
			while ((ptr->next != continents[i]->sentinel) && (ptr->next != NULL)) {
				printf("<%d>,", ptr->gid);
				ptr = ptr->next;
			}
			if (ptr->next == continents[i]->sentinel) {
				printf("<%d>\n", ptr->gid);
			}
		}
	}
	
	return 1;
}

/**
 * @brief Print homo_sapiens list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens() {
	struct Population* HS = hs_L;
	printf(" Homo Sapiens:");
	while (HS->next != NULL) {
		printf("<%d,%d>,", HS->gid, HS->sid);
		HS = HS->next;
	}
	if (HS->next == NULL) {
		printf("<%d,%d>\n", HS->gid, HS->sid);
	}
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
	return 1;
}


int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0]) {

			/* Comment */
		case '#':
			break;

			/* Insert Species
			 * S <sid> */
		case 'S':
		{
			int sid;

			sscanf(buff, "%c %d", &event, &sid);
			DPRINT("%c %d\n", event, sid);

			if (insert_species(sid)) {
				DPRINT("%c %d succeeded\n", event, sid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Insert population
		 * G <gid> <sid> <cid> */
		case 'G':
		{
			int gid, sid, cid;

			sscanf(buff, "%c %d %d %d", &event, &gid, &sid, &cid);
			DPRINT("%c %d %d %d\n", event, gid, sid, cid);

			if (insert_population(gid, sid, cid)) {
				DPRINT("%c %d %d %d succeeded\n", event, gid, sid, cid);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, gid, sid, cid);
			}

			break;
		}

		/* Merge species
		 * M <sid1> <sid2> <sid3> */
		case 'M':
		{
			int sid1, sid2, sid3;

			sscanf(buff, "%c %d %d %d", &event, &sid1, &sid2, &sid3);
			DPRINT("%c %d %d %d\n", event, sid1, sid2, sid3);

			if (merge_species(sid1, sid2, sid3)) {
				DPRINT("%c %d %d %d succeeded\n", event, sid1, sid2, sid3);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, sid1, sid2, sid3);
			}

			break;
		}

		/* Distribute species
		 * D */
		case 'D':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (distribute()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Delete population
		 * K <gid> <sid> */
		case 'K':
		{
			int gid, sid;

			sscanf(buff, "%c %d %d", &event, &gid, &sid);
			DPRINT("%c %d %d\n", event, gid, sid);

			if (delete_population(gid, sid)) {
				DPRINT("%c %d %d succeeded\n", event, gid, sid);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, gid, sid);
			}

			break;
		}

		/* Delete species
		 * F <sid> */
		case 'F':
		{
			int sid;

			sscanf(buff, "%c %d", &event, &sid);
			DPRINT("%c %d\n", event, sid);

			if (delete_species(sid)) {
				DPRINT("%c %d succeeded\n", event, sid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Evolution to homo sapiens
		 * E */
		case 'E':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (evolution()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Species' statistics
		 * N */
		case 'N':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (species_statistics()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Population statistics
		 * J <sid> */
		case 'J':
		{
			int sid;

			sscanf(buff, "%c %d", &event, &sid);
			DPRINT("%c %d\n", event, sid);

			if (population_statistics(sid)) {
				DPRINT("%c %d succeeded\n", event, sid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Print species
		 * P */
		case 'P':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_species()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print populations
			 * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_populations()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print continents
			 * C */
		case 'C':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_continents()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print homo sapiens
			 * W */
		case 'W':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_homo_sapiens()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

			/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);













	/*	insert_species(3);
		insert_species(5);
		insert_species(7);
		insert_species(4);
		insert_species(1);
		insert_species(2);
		insert_species(9);
		Shead = Species_head;
		while (Shead!=NULL)
		{
			Shead->Population_head = Shead->Population_tail = NULL;
			Shead = Shead->next;
		}
		//Species_head->Population_head = Species_head->Population_tail = NULL;
		//insert_species(12);
		//insert_species(10);
		//insert_species(0);
		//insert_species(20);
		insert_population(5, 4, 1);
		insert_population(3, 9, 3);
		insert_population(8, 4, 2);
		insert_population(16, 4, 1);
		insert_population(4, 1, 3);
		insert_population(10, 4, 3);
		insert_population(2, 1, 3);
		insert_population(0, 4, 2);
		insert_population(21, 9, 0);
		insert_population(34, 3, 4);

		Shead = Species_head;
		while (Shead != NULL) {
			printf("%d\n", Shead->sid);
			while (Shead->Population_head != NULL) {
				printf("%d ", Shead->Population_head->gid);
				Shead->Population_head = Shead->Population_head->next;
			}
			printf("\n");
			Shead = Shead->next;
		}*/
		//merge_species(4, 9, 6);
		/*distribute();
		delete_population(34, 3);
		Shead = Species_head;
		for (int i = 0; i < 5; i++) {
				printf("Continent %d:", i);
			while (continents[i]->populationList != continents[i]->sentinel) {
				printf("%d ",continents[i]->populationList->gid);
				continents[i]->populationList = continents[i]->populationList->next;
			}
			printf("\n");
		}
		Shead = Species_head;

		while (Shead != NULL) {
			printf("%d\n", Shead->sid);
			while (Shead->Population_head != NULL) {
				printf("%d ", Shead->Population_head->gid);
				Shead->Population_head = Shead->Population_head->next;
			}
			printf("\n");
			Shead = Shead->next;
		}*/
	getch();
	return 1;

}