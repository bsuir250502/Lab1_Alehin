#include <stdio.h>
#include <getopt.h>
#include <malloc.h>
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
void print_alphabet(struct info *child, char *illness)
{
    int i, j;
    printf("\nPatients with %s:\n", illness);
    for (i = 'A'; i <= 'Z'; i++)
        for (j = 0; j < child_num; j++)
            if (!strcmp(illness, child[j].last_illness)
                && child[j].child_surname[0] == i) {
                if (child[j].hospital_cure)
                    printf
                        ("%s, hospital #%s, address: %s, doctor: %s, illness: %s\n",
                         child[j].child_surname,
                         child[j].ch_union.hospital.hosp_num,
                         child[j].ch_union.hospital.hosp_address,
                         child[j].ch_union.hospital.surname_hosp_doc,
                         child[j].last_illness);
                else
                    printf("%s, doctor: %s, illness: %s\n",
                           child[j].child_surname,
                           child[j].ch_union.home.surname_distr_doc,
                           child[j].last_illness);
            }
}

void database_print(struct info *child)
{
    int i;
    puts("Database:");
    for (i = 0; i < child_num; i++)
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

void init_database(struct info *child)
{
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
    .last_illness = "mumps",.child_surname = "Petrov",.hospital_cure =
            0};
    child[3].ch_union.home = (struct home_cure) {
    .surname_distr_doc = "Maksimova"};

    child[4] = (struct info) {
    .last_illness = "anemia",.child_surname = "Frynse",.hospital_cure =
            1};
    child[4].ch_union.hospital = (struct hosp_cure) {
    .hosp_num = "4",.hosp_address = "West street",.surname_hosp_doc =
            "Melnova"};
}

int main(int argc, char *argv[])
{
    struct info child[child_num];
    int opt = 0;
    init_database(child);
    opt = getopt(argc, argv, "pl:h");
    while (opt != -1) {
        switch (opt) {
        case 'p':
            database_print(child);
            break;

        case 'l':
            print_alphabet(child, optarg);
            break;

        case 'h':              /* later */

            break;

        default:
            break;
        }
        opt = getopt(argc, argv, "pl:h");
    }
    return 0;
}
