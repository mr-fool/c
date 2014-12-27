#include <stdio.h>

#define LOWER_BOUND 33 //since 1-33 is considered nonprintable prof said consider space and tab as nonprintable
#define UPPER_BOUND 127                                

int main() {
    char row[9]; //8 characters a row
    int  c, d; //d is used to control the bounds of the row buffer
    for (d = 0, c = 0; c <= UPPER_BOUND; c++) { // c is the used as the ascii
        if (c < LOWER_BOUND || c >= UPPER_BOUND)  //1-33 or 127 print .
            row[d++] = '.';
        else                        
            row[d++] = c;   
        if (d == 8) { // when d = 8, we have an entire row 
            row[d] = '\0';
            printf("%s\n", row);
            d = 0;
        }
    }
    return 0;
}
