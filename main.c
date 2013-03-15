#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define all_string_maxsize 30
#define child_num 5

struct st1 {
    char surname_distr_doc[all_string_maxsize];
};
struct st2 {
    char hosp_num[all_string_maxsize];
    char hosp_address[all_string_maxsize];
    char surname_hosp_doc[all_string_maxsize];
};
struct info {
    char child_surname[all_string_maxsize];  // variables names later
    int hospital_cure;
	char last_illness[all_string_maxsize];
    union {
        struct st1 was_not;
        struct st2 was;
    } x;
};
void print_alphabet(struct info *child)
{
	puts("***");
	int i,j;
	char hz[20]="ospa"; // temporarily
	for (i='A'; i<='Z'; i++)
		for (j=0; j < child_num; j++)
			if (!strcmp(hz, child[j].last_illness) && child[j].child_surname[0]==i) 
			{
				if (child[i].hospital_cure) printf("%d: %s hospital #%s address: %s doc: %s, illness:%s\n", j, child[j].child_surname, child[j].x.was.hosp_num, child[j].x.was.hosp_address, child[j].x.was.surname_hosp_doc, child[j].last_illness);
				else printf("%d: %s , Doc:%s illness:%s\n", j, child[j].child_surname, child[j].x.was_not.surname_distr_doc, child[j].last_illness);
			 }
}
void database_print(struct info *child)
{
	int i;
	for (i = 0; i < child_num; i++)
		if (child[i].hospital_cure) printf("%d: %s was in hospital #%s with address %s, Doctor:%s, illness:%s\n", i, child[i].child_surname, child[i].x.was.hosp_num, child[i].x.was.hosp_address, child[i].x.was.surname_hosp_doc, child[i].last_illness);
		else printf("%d: %s was not in hospital, Doc:%s illness:%s\n", i, child[i].child_surname, child[i].x.was_not.surname_distr_doc, child[i].last_illness);
}

void init_database(struct info *child)
{
	child[0] = (struct info) {.last_illness = "fg",.child_surname="Alehin",.hospital_cure=1};
    child[0].x.was = (struct st2) {.hosp_num = "hg",.hosp_address ="hg",.surname_hosp_doc = "hg"};

	child[1] = (struct info) {.last_illness = "ospa",.child_surname="Ivanov",.hospital_cure=0};
    child[1].x.was_not = (struct st1) {.surname_distr_doc = "hg"};

	child[2] = (struct info) {.last_illness = "fg",.child_surname="Smith",.hospital_cure=1};
    child[2].x.was = (struct st2) {.hosp_num = "hg",.hosp_address ="hg",.surname_hosp_doc = "hg"};

	child[3] = (struct info) {.last_illness = "fg",.child_surname="Petrov",.hospital_cure=0};
    child[3].x.was_not = (struct st1) {.surname_distr_doc = "hg"};

	child[4] = (struct info) {.last_illness = "ospa",.child_surname="Arib",.hospital_cure=1};
    child[4].x.was = (struct st2) {.hosp_num = "hg",.hosp_address ="hg",.surname_hosp_doc = "hg"};
}


int main()
{
    struct info child[child_num];
	init_database(child);
	database_print(child);
	print_alphabet(child);
    return 0;
}
