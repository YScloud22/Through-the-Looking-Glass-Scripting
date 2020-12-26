#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "ll.h"
//#include "parser.h"
//#include "speck.h"

int HSstr(void) {
  FILE *in_file;
  char word[50000];

  in_file = fopen("userinputs.txt", "r");

  while (fscanf(in_file, "%s", word) != EOF) {
    ////// checking for old speak words
    FILE *HS_file;
    char HSword[50000];
    HS_file = fopen("hatterspeak.txt", "r");
    int b = 0;
    int temp = -1;
    while (fscanf(HS_file, "%s", HSword) != EOF) {

      if (strncmp(HSword, word, 50) == 0) {
          int f = (b + 2)/2;
        printf("%s -> Line %d\n", word, f);
        temp = b + 1;
        //           val(temp);
      }
      b = b + 1;
    }
    fclose(HS_file);
  }
  fclose(in_file);

  return 0;
}

int OSstr(void) { // printing os words
  FILE *in_file;
  char word[50000];

  in_file = fopen("userinputs.txt", "r");

  bool OS = false; // check if file contains old speak, hatterspeak, or both

  while (fscanf(in_file, "%s", word) != EOF) {
    ////// checking for old speak words
    FILE *OS_file;
    char OSword[50000];
    OS_file = fopen("oldspeak.txt", "r");
    int b = 0;

    while (fscanf(OS_file, "%s", OSword) != EOF) {

      if (strncmp(OSword, word, 50) == 0) {
        OS = true;
        printf("%s\n", word);

        //        break;
      }
      b = b + 1;
    }
    fclose(OS_file);
  }
  fclose(in_file);

  return 1;
}

int hatk(void) {
  FILE *my_stream;
  char my_filename[] = "hatterkeys.txt";
  my_stream = fopen(my_filename, "w");
  FILE *in_file;
  char word[100000];
  in_file = fopen("hatterspeak.txt", "r");
  int c = 0;
  while (fscanf(in_file, "%s", word) != EOF) {

    if ((c % 2) == 0) {
      fprintf(my_stream, "%s\n", word);
    }
    c = c + 1;
  }
  fclose(in_file);
  fclose(my_stream);

  return 0;
}

int main(int argc, char **argv) {
  //    printf("argc = %d\n", argc);
  //    printf("****/n");
  //    bin(8);
  //    printf("****/n");

  int option;
  int count = 1;
  int hashtable = 10000; // hashtable size
  int bloom = 1048576;
  int z; // checks if user gave a number
  int sflag = 0;
  int mflag = 0; // move to front
  int bflag = 0;
  while ((option = getopt(argc, argv, "sh:f:mb")) != -1) {
    switch (option) {
    case 's': // supress letter from the censor
      count++;
      sflag++;
      break;
    case 'm': // use move to front rule
      count++;
      mflag++;
      break;
    case 'b': // not use move to front rule
      count++;
      bflag++;
      break;
    case 'h': // specify size of hashtable
      count++;
      z = atoi(argv[count]);
      if (z != 0) {
        hashtable = z;
        count++;
      }
      break;
    case 'f':
      // bloom filter size
      count++;
      z = atoi(argv[count]);
      if (z != 0) {
        bloom = z;
        count++;
      }
      break;
    default:
      printf("error");
      break;
    }
  }
  // end of getopt
  if (sflag > 0) {
    printf("Seeks:\n");
    printf("Average seek length:\n");
    printf("Average Linked List Length:\n");
    printf("Hash table load:\n");
    printf("Bloom filter load:\n");
  }
  hatk(); // create hatterspeak keys file

  char str[50000]; // storing user inout
  // citing
  // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
  scanf("%[^EOF]%*c", str); // taking user input until end of file
  // int input_character;
  FILE *my_stream;
  char my_filename[] = "userinputs.txt";
  my_stream = fopen(my_filename, "w");
  fprintf(my_stream, "%s", str); // input into text file
  fclose(my_stream);             // close stream

  //////////////////////////////////////

  FILE *in_file;
  char word[50000];

  in_file = fopen("userinputs.txt", "r");

  bool OS = false; // check if file contains old speak, hatterspeak, or both
  bool HS = false;

  while (fscanf(in_file, "%s", word) != EOF) {
    ////// checking for old speak words
    FILE *OS_file;
    char OSword[50000];
    OS_file = fopen("oldspeak.txt", "r");
    int b = 0;

    while (fscanf(OS_file, "%s", OSword) != EOF) {

      if (strncmp(OSword, word, 50) == 0) {
        OS = true;

        //        break;
      }
      b = b + 1;
    }
    fclose(OS_file);
  }
  fclose(in_file);

  FILE *HS_file;
  char HSword[100000];
  HS_file = fopen("hatterkeys.txt", "r");
  int c = 0;

  while (fscanf(HS_file, "%s", HSword) != EOF) {

    if (strncmp(HSword, word, 50) == 0) {
      HS = true;
      break;
    }
    c = c + 1;
  }
  fclose(HS_file);

  //      if (OS == true) {
  //        printf("there is old speak\n");
  //      }
  //      if (HS == true) {
  //        printf("there is hatter speak\n");
  //      }

  //  if (sflag > 0) {
  //    printf("Seeks:\n");
  //    printf("Average seek length:\n");
  //    printf("Average Linked List Length:\n");
  //    printf("Hash table load:\n");
  //    printf("Bloom filter load:\n");
  //  }

  if ((OS == true) && (HS == true)) {
    printf("Dear Comrade ,\n");
    printf(
        "You have chosen to use words that the queen has decreed oldspeak.\n");
    printf("Due to your infraction you will be sent to the dungeon where you "
           "will be taught hatterspeak.\n");
    printf("\nYour errors:\n\n");
    /// print out OS words
    OSstr();
    printf("\nAppropriate hatterspeak translations.\n\n");
    // print out HS words
    HSstr();
  }

  else if (OS == true) {
    printf("Dear Wonderlander ,\n\n");
    printf(
        "You have chosen to use words that the queen has decreed oldspeak.\n");
    printf("Due to your infraction you will be sent to the dungeon where you "
           "will be taught hatterspeak.\n\n");
    printf("Your errors:\n\n");
    /// print out OS words
    OSstr();

  }

  else if (HS == true) {
    printf("Dear Wonderlander ,\n\n");
    printf("The decree for hatterspeak finds your message lacking. Some of the "
           "words that you used are not hatterspeak.\n");
    printf(
        "The list shows how to turn the oldspeak words into hatterspeak.\n\n");
    // print out HS words
    HSstr();
  }

  return 0;
}
