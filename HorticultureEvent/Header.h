#ifndef HEADER_H /* Added as recommended by Indian Hill Style Guide */
#define HEADER_H

#define MAX_LINE_LEN 80
#define MAX_FILE_LEN 50
#define MAX_NAME_LEN 80
#define MAX_DATE_LEN 80
#define MAX_ADDRESS_LEN 80
#define MAX_PHONENUM_LEN 80
#define INCHES_IN_FEET 12

typedef struct competitor_t {
    char name[MAX_NAME_LEN];
    char address[MAX_ADDRESS_LEN];
    char phonen_num[MAX_PHONENUM_LEN]; //Spec says assume as text
    int comp_num; //Allocated automatically as read in
    float cucum_len; //Inches
    float carrot_len; //Inches
    float run_bean_len; //Inches
    struct competitor_t *left;
    struct competitor_t *right;
}Competitor;

/* This hold the root location */
Competitor * root;  

/* 
 * Shameful global variables so I can access the name and date of event
 * in the 2 seperate printing sections.
 */
char event_name[MAX_NAME_LEN];
char event_date[MAX_DATE_LEN];

void getFileName(char * file_name);
int readFromFile(char* file_name);
float convert_size_to_inches(int feet, float inches);
float get_total_size(Competitor* new_node);
char * inches_to_feet_and_inches(float fruit_len);
void insert(Competitor** root, Competitor* new_node);
void search_through_BST(Competitor* new_node, void (*name_of_function_i_am_pointing_to)(Competitor* new_node));
void print(Competitor* new_node);
void print_competitor_info_to_output(Competitor* new_node);



#endif /* HEADER_H */