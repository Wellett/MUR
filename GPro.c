/* Author:    William Ellett
Organisation: Melbourne University Racing
Position:     Dynamics Engineer
Student ID:   586703

Written:      18/02/2018
Last modified:18/02/2018

Description: Processor for racecar accelerometer data.
Takes data input as csv and processes to adjust for accelerometer inclination
and gravity offset.

*/
#define OUTPUT_FILE "GPro_output.csv"
#define OUTPUT_HEAD "Time,G Force Lat,G Force Long,G Force Vert\ns,G,G,G\n"
#define INPUT_FILE "Enduro_G_Data.csv"


#include "GPro.h"
#include <stdio.h>
#include <stdlib.h>



int
main(int argc, char *argv[]){

  /*Open input file*/
  FILE* inputFile = safe_fopen(INPUT_FILE, "r");
  fscanf(inputFile, "%*[^\n]\n"); /*Skip line*/
  fscanf(inputFile, "%*[^\n]\n"); /*Skip line*/

  /*Initialize output*/
  FILE* outputFile = safe_fopen(OUTPUT_FILE, "w");
  fprintf(outputFile, OUTPUT_HEAD);

  GData_t* newSample;
  while ((newSample = read_data_point(inputFile)) != NULL){
    fprint_data_line(outputFile, newSample);
    free(newSample);
  }




  fclose(inputFile);
  fclose(outputFile);

return 0;
}




/* Reads a single data  point from csv
Returns a pointer to a new GData_t object*/
GData_t* read_data_point(FILE* input){
  double s_time, latitude, longitude, vert;
  if (fscanf(input, "%lf,%lf,%lf,%lf\n", &s_time, &latitude, &longitude, &vert) == 4) {
    GData_t* newData = (GData_t*)safe_malloc(sizeof(GData_t));
    newData->time = s_time;
    newData->GLat = latitude;
    newData->GLong = longitude;
    newData->GVert = vert;
    return newData;
  }
  return NULL;
}



/* Prints a data point to the terminal */
void print_data(GData_t* data_p){
  printf("Sample time: %.2f\n", data_p->time);
  printf("Longitudinal Acceleration: %.2fG\n", data_p->GLong);
  printf("Latteral Acceleration: %.2fG\n", data_p->GLat);
  printf("Vertical Acceleration: %.2fG\n", data_p->GVert);
}

/* outputs a line of data to file in csv format */
void fprint_data_line(FILE* file_p, GData_t* data_p){
  fprintf(file_p, "%.2f,", data_p->time);
  fprintf(file_p, "%.2f,", data_p->GLat);
  fprintf(file_p, "%.2f,", data_p->GLong);
  fprintf(file_p, "%.2f\n", data_p->GVert);
}

/* UTILITIES */

/* wrapper function arround fopen()*/
FILE* safe_fopen(const char* file_name, const char* mode){
  FILE* file_p = NULL;
  file_p = fopen(file_name, mode);
  if (file_p == NULL){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  return file_p;
}

/* a wrapper function around malloc which checks return values and exits on error */
void* safe_malloc(size_t bytes){
    void* ptr = NULL;
    ptr = malloc(bytes);
    if (ptr == NULL){
    	perror("ERROR: malloc failure");
    	exit(EXIT_FAILURE);
    }
    return ptr;
}
