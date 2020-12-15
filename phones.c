/* phones - locate and sort phone numbers in text document
 *
 * usage - phones
 *  (1) prompts user for filename of document
 *  (2) scans file for valid phone numbers
 *  (3) sorts phone numbers using selection sort algorithm
 *  (4) outputs sorted list to console
 *
 * NC State University
 * ECE 209 (001) Spring 2020
 * Program 3
 *
 * Sam Huneycutt, April 2020
 */

#include "phones.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//printPhoneNumbers
//prints list of phone numbers from array
//input:
//  char* const nums[]: ptr to array containing phone numbers
//  int size: size of array
void printPhoneNumbers(char* const nums[], int size) {
    int i;                          //counter
    for (i=0; i<size; i++) {        //print each phone number in array
        printf("%13s\n", nums[i]);
    }
}


//isPhoneNumber
//checks if input string is a correctly formatted phone number
//input:
//  const char* str: ptr to input string
//return:
//  1 if string is correctly formatted phone number
//  0 else
int isPhoneNumber(const char* str) {
    int i;          //counter

    //(xxx)xxx-xxxx
    //this block checks for 10 digit phone numbers with the area code in parentheses
    if(str[0] == '(') {                                 //check if first char '('
        for(i = 1; i <= 3; i++) {                       //check if next 3 chars are digits
            if(str[i] < '0' || str[i] > '9')
                return 0;                               //if non-digit char, string is invalid
        }

        if(str[4] == ')') {                             //check for ')'
            for (i = 5; i <= 7; i++) {                  //check if next 3 chars are digits
                if (str[i] < '0' || str[i] > '9')
                    return 0;                           //if non-digit char, string is invalid
            }
            if (str[8] == '-') {                        //check for '-' after digits
                for (i = 9; i <= 12; i++) {             //check next if next 4 chars are digits
                    if (str[i] < '0' || str[i] > '9')
                        return 0;                       //if non-digit char, string is invalid
                }
                if(str[13] == '\0')                     //check if string is finished (null terminator)
                    return 1;                           //if all conditions passed, string is valid (xxx)xxx-xxxx
            }
        }
    }

    //x-xxxx and xxx-xxxx and xxx-xxx-xxxx
    //this block checks for 5, 7, and 10 digit phone numbers without parentheses
    if(str[0] >= '0' && str[0] <= '9') {                //check if first char is digit

        //x-xxxx
        if(str[1] == '-') {                             //check for '-' after digit
            for (i = 2; i <= 5; i++) {                  //check if next 4 chars are digits
                if (str[i] < '0' || str[i] > '9')
                    return 0;                           //if non-digit char, string is invalid
            }
            if(str[6] == '\0')                          //check if string is finished (null terminator)
                return 1;                               //if all conditions passed, string is valid x-xxxx
        }

        //xxx-xxxx and xxx-xxx-xxxx
        else {
            for (i = 0; i <= 2; i++) {                  //check if first 3 chars are digits
                if (str[i] < '0' || str[i] > '9')
                    return 0;                           //if non-digit char, string is invalid
            }

            if(str[3] == '-') {                         //check for '-' after 3 digits
                for (i = 4; i <= 6; i++) {              //check if next 3 chars are digits
                    if (str[i] < '0' || str[i] > '9')
                        return 0;                       //if non-digit char, string is invalid
                }

                //str[7] == '-' -> xxx-xxx-xxxx
                if (str[7] == '-') {                    //check for '-'
                    for (i = 8; i <= 11; i++) {         //check if next 4 chars are digits
                        if (str[i] < '0' || str[i] > '9')
                            return 0;                   //if non-digit char, string is invalid
                    }
                    if (str[12] == '\0')                //check if string is finished (null terminator)
                        return 1;                       //if all conditions passed, string is valid xxx-xxx-xxxx
                }
                //str[7] == digit -> xxx-xxxx
                else {
                    if (str[7] >= '0' && str[7] <= '9')      //check if last char is a digit
                        if (str[8] == '\0')                 //check if string is finished (null terminator)
                            return 1;                       //if all conditions passed, string is valid xxx-xxxx
                }
            }
        }
    }
    return 0;                                           //all conditions failed, string is invalid
}


//relatePhoneNumber
//relates two phone numbers precedence for sorting
//input:
//  char num1[]: first phone number string
//  char num2[]: second phone number string
//return:
//  1 if num1 has greater precedence
//  0 if equal precedence
//  -1 if num1 has less precedence
int relatePhoneNumber(char num1[], char num2[]) {
    int i;                  //counter
    int format1;            //format code for num1
    int format2;            //format code for num2
    int length1;            //length of num1 string
    int length2;            //length of num2 string

    if (!strcmp(num1, num2))                            //if num1 and num2 are the same
        return 0;                                       //return 0 (equal precedence)

    length1 = (int)strlen(num1);                        //compute length of num1 string
    length2 = (int)strlen(num2);                        //compute length of num2 string

    /* Format codes for phone numbers
     *  (1) - x-xxxx
     *  (2) - xxx-xxxx
     *  (3) - xxx-xxx-xxxx
     *  (4) - (xxx)xxx-xxxx
     *  (-1)- invalid
     */

    //assign format code for num1 based on length
    switch (length1) {
        case 6:
            format1 = 1;
            break;
        case 8:
            format1 = 2;
            break;
        case 12:
            format1 = 3;
            break;
        case 13:
            format1 = 4;
            break;
        default:
            format1 = -1;
            break;
    }

    //assign format code for num2 based on length
    switch (length2) {
        case 6:
            format2 = 1;
            break;
        case 8:
            format2 = 2;
            break;
        case 12:
            format2 = 3;
            break;
        case 13:
            format2 = 4;
            break;
        default:
            format2 = -1;
            break;
    }

    /* greater format codes generally have greater sort precedence
     * code 3 and 4 have equal precedence
     * code 4 numbers contain parentheses which offset phone number digits
     * therefore, comparisons between code 3 and 4 numbers require special case logic
     */

    //special case: 4,3
    //num1: (xxx)xxx-xxxx   num2: xxx-xxx-xxxx
    if (format1 == 4 && format2 == 3) {                     //check format codes (format1 == 4 and format2 == 3)
        for (i = 0; i < 3; i++) {                           //check first 3 digits of each number
            if (num1[i + 1] > num2[i])                      //if digit in num1 > digit in num2
                return 1;                                   //return 1 (num1 has greater precedence)
            if (num1[i + 1] < num2[i])                      //if digit in num1 < digit in num2
                return -1;                                  //return -1 (num1 has less precedence)
            else continue;                                  //if digit in num1 == digit in num2, check next digit
        }

        //skip i == 3 to avoid comparing ')' to '-'

        for (i = 4; i < length2; i++) {                     //check remaining digits of each number
            if (num1[i + 1] > num2[i])                      //if digit in num1 > digit in num2
                return 1;                                   //return 1 (num1 has greater precedence)
            if (num1[i + 1] < num2[i])                      //if digit in num1 < digit in num2
                return -1;                                  //return -1 (num1 has less precedence)
            else continue;                                  //if digit in num1 == digit in num2, check next digit
        }
    }

    //special case: 3,4
    //num1: xxx-xxx-xxxx    num2: (xxx)xxx-xxxx
    if (format1 == 3 && format2 == 4) {                     //check format codes (format1 == 4 and format2 == 3)
        for (i = 0; i < 3; i++) {                           //check first 3 digits of each number
            if (num1[i] > num2[i + 1])                      //if digit in num1 > digit in num2
                return 1;                                   //return 1 (num1 has greater precedence)
            if (num1[i] < num2[i + 1])                      //if digit in num1 < digit in num2
                return -1;                                  //return -1 (num1 has less precedence)
            else continue;                                  //if digit in num1 == digit in num2, check next digit
        }

        //skip i == 3 to avoid comparing '-' to ')'

        for (i = 4; i < length1; i++) {                     //check remaining digits of each number
            if (num1[i] > num2[i + 1])                      //if digit in num1 > digit in num2
                return 1;                                   //return 1 (num1 has greater precedence)
            if (num1[i] < num2[i + 1])                      //if digit in num1 < digit in num2
                return -1;                                  //return -1 (num1 has less precedence)
            else continue;                                  //if digit in num1 == digit in num2, check next digit
        }
    }

    /* special cases for format code 3 and 4 have been taken care of */

    //greater format codes have greater precedence
    if (format1 > format2)                                  //if num1 format > format2
        return 1;                                           //return 1 (num1 has greater precedence)

    //lower format codes have less precedence
    if (format1 < format2)                                  //if num1 format < format2
        return -1;                                          //return -1 (num1 has less precedence)


    //if format is the same
    // precedence is assigned based on digits from left to right
    // greater digits have greater precedence
    if (format1 == format2) {
        for (i = 0; i < length1; i++) {                     //check digits of each number
            if (num1[i] > num2[i])                          //if digit in num1 > digit in num2
                return 1;                                   //return 1 (num1 has greater precedence)
            else if (num1[i] < num2[i])                     //if digit in num1 < digit in num2
                return -1;                                  //return -1 (num1 has less precedence)
            else continue;                                  //if digit in num1 == digit in num2, check next digit
        }
    }
    return 0;       //if all digits equal, num1 and num2 have equal precedence
}


//sortPhoneNumbers
//sort phone numbers in ascending order
//use selection sort algorithm
//input:
//  char* nums[]: ptr to array to be sorted
//  int size: size of array to be sorted
void sortPhoneNumbers(char* nums[], int size) {
    int i, j;                   //counters
    int indexSmallest;          //index of smallest value
    char tempVal[15];           //temporary char array to facilitate swap

    /* Selection sort:
     * set index i to beginning of array
     * find smallest value in array after index i, swap with value at index i
     * repeat for each value of i (all valid indexes)
     */

    //sort list with selection sort
    for(i = 0; i < size - 1; i++) {

        //find index of smallest value
        indexSmallest = i;                                  //start at i
        for(j = i + 1; j < size; j++) {                     //check all values right of i
            //if value less than smallest value
            //  rules for determining precedence are defined in relatePhoneNumber
            //  list will be sorted from lowest precedence to highest precedence
            if(relatePhoneNumber(nums[j], nums[indexSmallest]) == -1)
                indexSmallest = j;                          //store index of smallest value
        }
        if(indexSmallest == i) {                            //if value at i is the smallest, can't swap i with i
            continue;                                       //continue to next i
        }
        else {                                              //otherwise, swap value at i with smallest value
            strcpy(tempVal, nums[i]);                       //save value at i
            strcpy(nums[i], nums[indexSmallest]);           //value at i = smallest value
            strcpy(nums[indexSmallest], tempVal);           //value at index of smallest value = saved value at i
        }
    }
}


//findPhoneNumbers
//find all occurrences of phone numbers in a text file
//store all phone numbers into allocated memory
//input:
//  const char* filename: filename for text document
//  char* nums[]: array of pointers (starts empty, populated by function)
//  int limit: max number of phone numbers to store
//return:
//  number of phone numbers stored (int)
int findPhoneNumbers(const char* filename, char* nums[], int limit) {
    char readString[15];        //array for input string
    int i;                  //counter
    bool fileDone = false;      //boolean, true if finished reading file
    FILE* in;                   //FILE* ptr for opening text file

    in = fopen(filename, "r");                          //open text file

    if(!in)                                                 //if file open failed
        return 0;                                           //return 0 (file error)

    //read strings from the file until all strings have been read or limit reached
    //  strings larger than 14 characters will be truncated -- phone number can only be 13 or fewer characters
    for(i = 0; i < limit && !fileDone; ) {
        if (fscanf(in, "%14s", readString) == EOF)          //if fscanf reports end of file (EOF)
            fileDone = true;                                //all strings have been read

        else if (isPhoneNumber(readString)) {               //check if string is a phone number
            nums[i] = (char *) malloc(14 * sizeof(char));   //allocate memory for phone number
            strcpy(nums[i], readString);                    //copy string into allocated memory
            i++;                                            //increment counter
        }
    }
    fclose(in);             //close file
    return i;               //return number of phone numbers stored
}
