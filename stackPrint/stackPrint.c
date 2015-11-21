/*
 * stackPrint.c
 * Prints out the stack of this process.
 * by Julian Borrey, 2014
 */

#include <stdlib.h>
#include <stdio.h>

#define LIM 128
#define ASCII_SPACE 32
#define ASCII_TILDA 126
#define BYTES_BEYOND_TOP 100

void foo0(int n, int wordSize);
void foo1(int n, int wordSize);
void foo2(int n, int wordSize);
void foo3(int n, int wordSize);
void printDown(char* ptr, int n, int wordSize);
void printLine(int index, char* ptr, int wordSize);
void printColTitles(int wordSize);
char niceChar(char c);

int main(int argc, char* argv[]){
   
   if(argc != 3){
      printf("This program will print out its own stack in a data "
             "table displaying the bytes in hexidecimal, decimal and "
             "ASCII format along side its address. Per row, wordSize "
             "bytes will be displayed.\n"
             "Please give the number of bytes you want to print "
             "and the wordSize (4 or 8 bytes) to be displayed for "
             "each line of the data table.\n");
      return EXIT_FAILURE;
   }

   printf("&foo0  = %p\n", &foo0);
   printf("&foo1  = %p\n", &foo1);
   printf("&foo2  = %p\n", &foo2);  
   printf("&foo3  = %p\n", &foo3);
   printf("&printDown = %p\n", &printDown);
   printf("&main = %p\n", &main);

   foo0(atoi(argv[1]), atoi(argv[2])); 
   
   return EXIT_SUCCESS;
}

//each foo is just a dummy function to show a stack
void foo0(int n, int wordSize){
   char buffer[8] = "aaaaaaa"; // useful string to find this frame
   foo1(n, wordSize);
   return;
}

void foo1(int n, int wordSize){
   char buffer[8] = "bbbbbbb";
   foo2(n, wordSize);
   return;
}

void foo2(int n, int wordSize){
   char buffer[8] = "ccccccc";
   foo3(n, wordSize);
   return;
}

void foo3(int n, int wordSize){
   char buffer[8] = "ddddddd";
   printDown(buffer-BYTES_BEYOND_TOP, n, wordSize);
   return;
}

//prints the data table
void printDown(char* ptr, int n, int wordSize){
   printColTitles(wordSize);
   for(int i = 0; i < n; i += wordSize){
      printLine(i, &ptr[i], wordSize);
   }
   return;
}

//prints the data of the current word for each line
//in each way spcified by the columns
void printLine(int index, char* ptr, int wordSize){

   int i = 0;
   printf("[%04d] ", index);
   if(wordSize == 4){
      printf("%4p: ", ptr);
   } else if(wordSize == 8){
      printf("%8p: ", ptr);
   }
   
   for(i = 0; i < wordSize; i++){
      printf("%02x ", (unsigned char) ptr[i]);
   }
   printf("| ");
   
   for(i = 0; i < (wordSize / 4); i++){
      printf("%11d ", ((int*) ptr)[i]);
   }
   printf("| ");
   
   for(i = 0; i < wordSize; i++){
      printf("%c ", niceChar(ptr[i]));
   }
   printf("\n");

   return;
}

//printf out the col titles for the data table
void printColTitles(int wordSize){
   printf("[byte] ====address===: ");
   int numDashes = 23;

   int i = 0;
   for(i = 0; i < wordSize; i++){
      printf("hx ");
      numDashes += 3;
   }
   printf("| ");
   numDashes += 2;
   
   for(i = 0; i < (wordSize / 4); i++){
      printf("    deci    ");
      numDashes += 12;
   }
   printf("| ");
   numDashes += 2;
   
   for(i = 0; i < wordSize; i++){
      printf("c ");
      numDashes += 2;
   }
   numDashes--;
   printf("\n");
   
   for(i = 0; i < numDashes; i++){
      printf("-");
   }
   printf("\n");
   return;
}

//removes anything not an ASCII you can see
//also removes things like new line and tab
char niceChar(char c){
   char newChar;
   if(( ((int)c) >= ASCII_SPACE) && ( ((int)c) <= ASCII_TILDA)){
      newChar = c;
   } else {
      newChar = ' ';
   }
   return newChar;
}
