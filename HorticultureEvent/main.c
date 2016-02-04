/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Shankly Richard Cragg (shc27)
 *
 * /aber/dap/HORT_237/hort_2013.txt
 * 
 * Created on 04 December 2015, 21:28
 */

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

/*
 * 
 */
int main(int argc, char** argv) {

    char file_name[50];
    getFileName(file_name);
    readFromFile(file_name);
    Competitor * temp = root;
    search_through_BST(temp,print);
    
    /* 
     * A hack solution to print off these details at the
     * top of the competitor contact details section, I am not
     * proud of this, but I wanted it too work on the output.
     */
    printf("Competition: %s Date: %s\n", event_name, event_date);
    printf("Competitor Contact Details.\n\n");
    search_through_BST(temp,print_competitor_info_to_output);    

    return (EXIT_SUCCESS);

}

/**
 * The user enters the file name to be used
 * @param file_name The file name to be used
 */
void getFileName(char * file_name) {

    printf("Please enter a file name: \n");

    /* Read file name */
    if (scanf("%s", file_name) == 1) {
    } else {
        printf("failed to read file name.\n");
    }
}

/**
 * Reads in information from a file specified by the user. This information
 * is placed into structs which are placed into a BST
 * @param file_name The name of the file to be used
 * @return If the file was not found, returns EXIT_FAILURE.
 */
int readFromFile(char* file_name) {

    /* temporary int variables for converting to total inches */
    int temp_feet;
    float temp_inches;

    /* Points to the file and opens it */
    FILE * file_pointer = fopen(file_name, "r");

    /* If the file is not found, exit */
    if (file_pointer == NULL) {
        printf("No file found");
        return (EXIT_FAILURE);
    }

    /* Increments to automatically get competitors number */
    int comp_numm = 1;

    /* Read name of event */
    if (fscanf(file_pointer, "%[a-zA-Z. ]\n", event_name) == 1) {
        //printf("%s\n", event_name);
    } else {
        printf("failed to read event name.\n");
    }

    /* Read date of event */
    if (fscanf(file_pointer, "%[a-zA-Z0-9,. ]\n", event_date) == 1) {
        //printf("%s\n", event_date);
    } else {
        printf("failed to read event date.\n");
    }

    /* Loop through while we are not at the end of the file */
    while (!feof(file_pointer)) {

        /* Malloc the size of a competitor */
        Competitor *competitors = malloc(sizeof (Competitor));

        /* Read name of entrant */
        if (fscanf(file_pointer, " %[a-zA-Z,. ]\n", competitors->name) == 1) {
            //printf("%s\n", competitors->name);
        } else {
            printf("failed to read name.\n");
        }

        /* Read address of entrant */
        if (fscanf(file_pointer, " %[a-zA-Z0-9.,/- ]\n", competitors->address) == 1) {
            //printf("%s\n", competitors->address);
        } else {
            printf("failed to read address.\n");
        }

        /* Read Contact information of entrant */
        if (fscanf(file_pointer, " %[a-zA-Z0-9 ]\n", competitors->phonen_num) == 1) {
            //printf("%s\n", competitors->phonen_num);
        } else {
            printf("failed to read phone number.\n");
        }

        /* Read length of cucumber and change in into inches */
        if (fscanf(file_pointer, "%d %f", &temp_feet, &temp_inches) == 2) {
            //printf("%d %.1f\n", temp_feet, temp_inches);
            competitors->cucum_len = convert_size_to_inches(temp_feet, temp_inches);
            //printf("%.1f\n", competitors->cucum_len);
        } else {
            printf("failed to read cucumber length.\n");
        }

        /* Read length of carrot and change in into inches */
        if (fscanf(file_pointer, "%d %f", &temp_feet, &temp_inches) == 2) {
            //printf("%d %.1f\n", temp_feet, temp_inches);

            competitors->carrot_len = convert_size_to_inches(temp_feet, temp_inches);
            //printf("%.1f\n", competitors->carrot_len);
        } else {
            printf("failed to read carrot length.\n");
        }

        /* Read length of runner bean and change in into inches */
        if (fscanf(file_pointer, "%d %f\n", &temp_feet, &temp_inches) == 2) {
            //printf("%d %.1f\n", temp_feet, temp_inches);

            competitors->run_bean_len = convert_size_to_inches(temp_feet, temp_inches);
            //printf("%.1f\n", competitors->run_bean_len);
        } else {
            printf("failed to read runner bean length.\n");
        }

        /* Store the competitors number*/
        competitors->comp_num = comp_numm;

        /* Increment the competitor number count ready for next competitor*/
        comp_numm++;

        /* Send the root and the current struct into insert*/
        insert(&root, competitors);

    }

    fclose(file_pointer);
    
    printf("Competition: %s Date: %s\n", event_name, event_date);
    /* The table format that is printed */
    printf("%-20s%-20s%-15s%-15s%-15s%-15s\n", "NAME", "competitor number", "Cucumber", "Carrot", "Runner Bean", "Total Length");
    printf("=================================================================================================\n");

}

/**
 * Converts size of fruit in feet and inches into only inches
 * @param feet Number of feet of fruit
 * @param inches Number of inches of fruit
 * @return total_inches Total number of inches of fruit
 */
float convert_size_to_inches(int feet, float inches) {
    float total_inches = 0;
    total_inches += feet * INCHES_IN_FEET;
    total_inches += inches;
    return total_inches;
}

/**
 * Inserts a competitor into the binary search tree.
 * This insert function and the knowledge I have on their
 * implementation in C comes from this website:
 * http://www.thegeekstuff.com/2013/02/c-binary-tree/
 * The code used below is adapted from their example
 * @param root The root node of the tree
 * @param new_node The current competitor we are inserting
 */
void insert(Competitor** root, Competitor* new_node) {

    /* If there is no root node to BST */
    if (!(*root)) {

        /* Set the root to be the new node */
        *root = new_node;
        return;
    }

    /* Inserts the node into the correct child position */
    if ((get_total_size(new_node)) < get_total_size(*root)) {

        /* Recursively call insert until it is a leaf */
        insert(&(*root)->left, new_node);

        /* If the nodes are even, insert into right tree as mentioned in spec */
    } else if ((get_total_size(new_node)) >= get_total_size(*root)) {

        /* Recursively call insert until it is a leaf */
        insert(&(*root)->right, new_node);
    }
}

/**
 * Adds up  the sizes of all fruit for a competitor
 * @param new_node The competitor whose total size we want
 * @return total_len The total length of all fruit
 */
float get_total_size(Competitor* new_node) {
    float total_len = new_node->cucum_len + new_node->carrot_len
            + new_node->run_bean_len;
    return total_len;
}

/**
 * Recursively prints results from the tree in-order.
 * This print function and the knowledge I have on their
 * implementation in C from a BST comes from this website:
 * http://www.thegeekstuff.com/2013/02/c-binary-tree/
 * The code used below is adapted from my code in part 1,
 * and that code is adapted from their example
 * @param new_node The node currently being used in the BST
 * @param name_of_function_i_am_pointing_to the function I am pointing to that
 * I wish to call
 */
void search_through_BST(Competitor* new_node, void (*name_of_function_i_am_pointing_to)(Competitor* new_node)) {
    if (new_node) {
        search_through_BST(new_node->left, name_of_function_i_am_pointing_to);
        name_of_function_i_am_pointing_to(new_node);
        search_through_BST(new_node->right, name_of_function_i_am_pointing_to);
    }
}

/**
 * Gets the information to print about each competitor in the
 * correct format and prints to the output
 * @param new_node The competitor whose information we want to print
 */
void print(Competitor* new_node) {
    char * cucum_string = inches_to_feet_and_inches(new_node->cucum_len);
    char * carrot_string = inches_to_feet_and_inches(new_node->carrot_len);
    char * run_bean_string = inches_to_feet_and_inches(new_node->run_bean_len);
    float total_len = get_total_size(new_node);
    char * total_len_string = inches_to_feet_and_inches(total_len);
    printf("%-20s%-20d%-15s%-15s%-15s%-15s\n", new_node->name, new_node->comp_num, cucum_string, carrot_string, run_bean_string, total_len_string);

}

/**
 * Print out the contact info for competitors
 * @param new_node The Competitor whose information is to be printed
 */
void print_competitor_info_to_output(Competitor* new_node) {
    printf("Competitor Name: ");
    printf("%s\n", new_node->name);
    printf("Postal Address: ");
    printf("%s\n", new_node->address);
    printf("Telephone: ");
    printf("%s\n\n", new_node->phonen_num);
}

/**
 * Converts the total length in inches in a string containing the feet
 * and inches
 * @param fruit_len The length of the fruit in inches
 * @return temp The string containing the number of feet and inches
 */
char * inches_to_feet_and_inches(float fruit_len) {

    /* Give memory to the string we are returning*/
    char * temp = malloc(sizeof (char) * 15);

    /* Work out the individual feet and inches */
    int feet = fruit_len / INCHES_IN_FEET;
    float inches = (fruit_len - (feet * INCHES_IN_FEET));

    /* Make the string to be returned */
    sprintf(temp, "%dft %.1fin", feet, inches);

    return temp;

}