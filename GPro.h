/* Author:    William Ellett
Organisation: Melbourne University Racing
Position:     Dynamics Engineer
Student ID:   586703

Written:      18/02/2018
Last modified:18/02/2018

Description: Header File for GPro.h

*/
/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Struct to contain each data point */
typedef struct {
  double time;    /*Sample time*/
  double GLat;    /*Longitudinal Acceleration*/
  double GLong;   /*Latteral Acceleration*/
  double GVert;   /*Vertical Acceleration*/
} GData_t;


/*function prototypes*/
FILE* safe_fopen(const char*, const char*);
void* safe_malloc(size_t);
GData_t* read_data_point(FILE*);
void print_data(GData_t*);
void fprint_data_line(FILE* file_p, GData_t* data_p);
GData_t* rotate_sample(GData_t* sample_p);
