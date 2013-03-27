#include <stdio.h>
#include <getopt.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
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
    strncpy(child[0].child_surname, "Alehin", all_string_maxsize);
    strncpy(child[0].last_illness, "anemia", all_string_maxsize);
    child[0].hospital_cure = 1;
    strncpy(child[0].ch_union.hospital.hosp_num, "12", all_string_maxsize);
    strncpy(child[0].ch_union.hospital.hosp_address, "Kalinowski street",
            all_string_maxsize);
    strncpy(child[0].ch_union.hospital.surname_hosp_doc, "Bobr",
            all_string_maxsize);

    strncpy(child[1].child_surname, "Ivanov", all_string_maxsize);
    strncpy(child[1].last_illness, "pneumonia", all_string_maxsize);
    child[1].hospital_cure = 0;
    strncpy(child[1].ch_union.home.surname_distr_doc, "Kashliak",
            all_string_maxsize);

    strncpy(child[2].child_surname, "Sidorov", all_string_maxsize);
    strncpy(child[2].last_illness, "tetanus", all_string_maxsize);
    child[2].hospital_cure = 1;
    strncpy(child[2].ch_union.hospital.hosp_num, "5", all_string_maxsize);
    strncpy(child[2].ch_union.hospital.hosp_address, "Zapadnaya street",
            all_string_maxsize);
    strncpy(child[2].ch_union.hospital.surname_hosp_doc, "Maksimov",
            all_string_maxsize);

    strncpy(child[3].child_surname, "Petrov", all_string_maxsize);
    strncpy(child[3].last_illness, "anemia", all_string_maxsize);
    child[3].hospital_cure = 0;
    strncpy(child[3].ch_union.home.surname_distr_doc, "Maksimova",
            all_string_maxsize);

    strncpy(child[4].child_surname, "Aleain", all_string_maxsize);
    strncpy(child[4].last_illness, "tetanus", all_string_maxsize);
    child[4].hospital_cure = 1;
    strncpy(child[4].ch_union.hospital.hosp_num, "4", all_string_maxsize);
    strncpy(child[4].ch_union.hospital.hosp_address, "West street",
            all_string_maxsize);
    strncpy(child[4].ch_union.hospital.surname_hosp_doc, "Melnova",
            all_string_maxsize);
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
