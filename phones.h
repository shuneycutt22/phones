#ifndef PHONES_H
#define PHONES_H
/*
 * This function prints phone numbers
 *
 * Parameters:
 *  nums - an array to store the phone numbers (an array of pointers)
 *  size - length of that array.
 *
 */
void printPhoneNumbers(char * const nums[], int size);


/*
 * This function finds phone numbers within a file.
 *
 *
 * Parameters:
 *  filename -file name (a string)
 *  nums - an array to store the phone numbers (an array of pointers)
 *  limit - max size of that array.
 *
 * The return value:
 *  - The number of strings that were extracted from the file.
 *  - If the file cannot be opened, the function returns zero.
 *  (The caller will not be able to distinguish a file error
 *  from a file with no phone numbers.)
 */
int findPhoneNumbers(const char * filename, char * nums[], int limit);

/*
 * This function sorts the phone numbers in ascending order
 *
 * Parameters:
 *  nums - an array to store the phone numbers (an array of pointers)
 *  size - length of that array.
 */
void sortPhoneNumbers(char * nums[], int size);



/*
 *This function checks if a string is a phone number
 *
 * Parameter:
 *  str - string pointer
 *
 * return value:
 *  1 - if the string is a phone number
 *  0 - otherwise
 *
 */
int isPhoneNumber(const char * str);

#endif //PHONES_H
