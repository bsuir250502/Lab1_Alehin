#include <stdio.h>
#include <malloc.h>
const int all_string_maxsize = 30;
const int child_num = 5;
struct info {
    char *child_surname;
    int hospital_cure;
    union {
        struct {
            char *last_illness;
            char *surname_distr_doc;
        } was;
        struct {
            char *last_illness;
            char *hosp_num;
            char *hosp_address;
            char *surname_hosp_doc;
        } was_not;
    };
} *child;

void database()
{
    child = (struct info *) malloc(sizeof(struct info) * child_num);
    child[0].child_surname = (char *) malloc(all_string_maxsize);
    child[0].child_surname = "ehin";
    child[0].hospital_cure = 0;
    child[0].was_not.last_illness = (char *) malloc(all_string_maxsize);
    child[0].was_not.hosp_address = (char *) malloc(all_string_maxsize);
    child[0].was_not.hosp_num = (char *) malloc(all_string_maxsize);
    child[0].was_not.surname_hosp_doc =
        (char *) malloc(all_string_maxsize);
    child[0].was_not.last_illness = "ORVI";
    child[0].was_not.hosp_address = "ERGFFDG";
    child[0].was_not.hosp_num = "17";
    child[0].was_not.surname_hosp_doc = "Melnova";
    /* ....... */
}

int main()
{
    database();
    return 0;
}
