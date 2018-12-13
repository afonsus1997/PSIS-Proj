#include "structs.h"

struct tm timespecToTm(struct timespec t){
/*
 * Function:  timespecToTm 
 * --------------------
 *  Converts timespec to tm.
 * 
 *  Returns:
 *      (tm) converted timespec
 */
    struct tm tm;
    localtime_r(&t.tv_sec, &tm);
    return tm;
}

struct timespec tmToTimespec(struct tm tm){
/*
 * Function:  tmToTimespec 
 * --------------------
 *  Converts tm to timespec.
 * 
 *  Returns:
 *      (timespec) converted tm
 */    
    struct timespec t;
    t.tv_sec = mktime(&tm);
    return t;
}

struct timespec stringToTimespec(char string[26]){
/*
 * Function:  stringToTimespec 
 * --------------------
 *  Parses string to timespec.
 * 
 *  Returns:
 *      (timespec) parsed string
 */   
    struct tm tm;
    strptime(string, "%d/%m/%Y%H:%M:%S\n", &tm);
    return tmToTimespec(tm); 
}

void printTimespecString(struct timespec t){
/*
 * Function:  printTimespecString 
 * --------------------
 *  Converts timespec to string and prints it.
 * 
 *  Returns:
 *      (void) 
 */ 
    char str[26];
    struct tm tm;
    tm = timespecToTm(t);
    strftime(&str[0], sizeof(str), "%d/%m/%Y %H:%M:%S\n", &tm); // specify format of str
    printf("%s", str); // e.g. “15/11/2011 15:45:25” 

}

