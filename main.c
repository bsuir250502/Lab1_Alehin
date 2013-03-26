#include <stdio.h>
#include <getopt.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define all_string_maxsize 30
#define child_num 5

struct home_cure {
    char surname_distr_doc[all_string_maxsize];
};
struct hosp_cure {
    char hosp_num[all_string_maxsize];
    char hosp_address[all_string_maxsize];
    char surname_hosp_doc[all_string_maxsize];
};
struct info {
    char child_surname[all_string_maxsize];
    int hospital_cure;
    char last_illness[all_string_maxsize];
    union patient_or_no {
        struct home_cure home;
        struct hosp_cure hospital;
    } ch_union;
};

int name_cmp(const void *a, const void *b)
{
    return strcmp((*(struct info *) a).child_surname,
                  (*(struct info *) b).child_surname);
}

void readme(void)
{
    puts("Usage: ./main [mode]");
    puts("  -p                print data from database");
    puts("  -l <illness>      alphabetically sort list of patients with");
    puts("                    this illness");
    puts("  -h                help");
}

void print_alphabet(struct info *child, char *illness, int child_num_typed)
{
    int i;
    printf("Patients with %s:\n", illness);
    for (i = 0; i < child_num_typed; i++)
        if (!strcmp(illness, child[i].last_illness)) {
            if (child[i].hospital_cure)
                printf
                    ("%s, hospital #%s, address: %s, doctor: %s, illness: %s\n",
                     child[i].child_surname,
                     child[i].ch_union.hospital.hosp_num,
                     child[i].ch_union.hospital.hosp_address,
                     child[i].ch_union.hospital.surname_hosp_doc,
                     child[i].last_illness);
            else
                printf("%s, doctor: %s, illness: %s\n",
                       child[i].child_surname,
                       child[i].ch_union.home.surname_distr_doc,
                       child[i].last_illness);
        }
}

void print_database(struct info *child, int child_num_typed)
{
    int i;
    puts("Database:");
    for (i = 0; i < child_num_typed; i++)
        if (child[i].hospital_cure)
            printf
                ("%d: %s, hospital #%s, address: %s, doctor: %s, illness: %s\n",
                 i, child[i].child_surname,
                 child[i].ch_union.hospital.hosp_num,
                 child[i].ch_union.hospital.hosp_address,
                 child[i].ch_union.hospital.surname_hosp_doc,
                 child[i].last_illness);
        else
            printf("%d: %s, district doctor: %s, illness: %s\n", i,
                   child[i].child_surname,
                   child[i].ch_union.home.surname_distr_doc,
                   child[i].last_illness);
}

int init_database(struct info *child)
{
    int child_num_typed = 5;
    child[0] = (struct info) {
    .last_illness = "anemia",.child_surname = "Alehin",.hospital_cure =
            1};
    child[0].ch_union.hospital = (struct hosp_cure) {
    .hosp_num = "12",.hosp_address =
            "Kalinowski street",.surname_hosp_doc = "Bobr"};

    child[1] = (struct info) {
    .last_illness = "pneumonia",.child_surname =
            "Ivanov",.hospital_cure = 0};
    child[1].ch_union.home = (struct home_cure) {
    .surname_distr_doc = "Kashliak"};

    child[2] = (struct info) {
    .last_illness = "tetanus",.child_surname =
            "Sidorov",.hospital_cure = 1};
    child[2].ch_union.hospital = (struct hosp_cure) {
    .hosp_num = "5",.hosp_address =
            "Zapadnaya street",.surname_hosp_doc = "Maksimov"};

    child[3] = (struct info) {
    .last_illness = "anemia",.child_surname = "Petrov",.hospital_cure =
            0};
    child[3].ch_union.home = (struct home_cure) {
    .surname_distr_doc = "Maksimova"};

    child[4] = (struct info) {
    .last_illness = "anemia",.child_surname = "Aleain",.hospital_cure =
            1};
    child[4].ch_union.hospital = (struct hosp_cure) {
    .hosp_num = "4",.hosp_address = "West street",.surname_hosp_doc =
            "Melnova"};
    return child_num_typed;
}

int main(int argc, char *argv[])
{

    const char *options = "pl:h";
    int opt = 0, child_num_typed;
    struct info child[child_num];
    child_num_typed = init_database(child);
    qsort(child, child_num_typed, sizeof(struct info), name_cmp);
    opt = getopt(argc, argv, options);
    if (opt == -1)
        readme();
    while (opt != -1) {
        switch (opt) {
        case 'p':
            print_database(child, child_num_typed);
            break;

        case 'l':
            print_alphabet(child, optarg, child_num_typed);
            break;

        case 'h':
            readme();
            break;

        default:
            break;
        }
        opt = getopt(argc, argv, options);
    }
    return 0;
}
