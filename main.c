#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "crypto.h"

#define LOWER 0
#define UPPER 300
#define STEP 20

#define TRUE 1
#define FALSE 0

#define ZERO 0
#define ONE 1
#define TEN 10
#define TWENTYSIX 26

#define ASCII_ZERO 0x30
#define ASCII_NINE 0x39
#define ASCII_SPACE 0x20
#define ASCII_NEWLINE 0xA
#define ASCII_TAB 0x9
#define ASCII_a 0x61
#define ASCII_z 0x7A

#define MAXLINE 1000


//copy_single_blank() {
//    int character;
//    int inspace = FALSE;
//
//    while ((character = getchar()) != EOF)
//    {
//        inspace = character == ' ' && inspace == FALSE ? TRUE : FALSE;
//        putchar(character);
//    }
//}


// 1-10
//void copy_replace_whitespace() {
//    int character;
//
//    while ((character = getchar()) != EOF)
//    {
//        if (character == '\\')
//        {
//            putchar('\\');
//            putchar('\\');
//        }
//        if (character == '\t')
//        {
//            putchar('\\');
//            putchar('t');
//        }
//        if (character == '\b')
//        {
//            putchar('\\');
//            putchar('b');
//        }
//        else {
//            putchar(character);
//        }
//    }
//}

//main()
//{
//    int character, count;
//
//    count = 0;
//    while ((character = getchar()) != EOF) {
//        if (character == '\n' || character == '\t' || character == ' ') {
//            ++count;
//        }
//    }
//
//    printf("%d\n", count);
//}

//main() {
//    double new_character = 0;
//
//    while (getchar() != EOF) {
//        ++new_character;
//    }
//
//    printf("%f\n", new_character);
//}

//int main() {
//    int fahrenheit;
//
//    for (fahrenheit = LOWER; fahrenheit <= UPPER; fahrenheit = fahrenheit + STEP) {
//        printf("%d\t%6.1f\n", fahrenheit, 5 * (fahrenheit - 32) / 9.0);
//    }
//}



//void word_counting()
//{
//    int character, new_line, new_word, new_character, state;
//
//    state = OUT;
//    new_line = new_word = new_character = 0;
//
//    while ((character == getchar()) != EOF)
//    {
//        ++new_character;
//        if (character == '\n')
//        {
//            ++new_line;
//        }
//        if (character == ' ' || character == '\n' || character == '\t')
//        {
//            state = OUT;
//        }
//        else if (state == OUT)
//        {
//            state = IN;
//            ++new_word;
//        }
//
//        printf("%d %d %d\n", new_line, new_word, new_character);
//    }
//
//    printf("%d %d %d\n", new_line, new_word, new_character);
//}

//void count() {
//    int character, whitespace, other;
//    int digits[TEN];
//
//    whitespace = other = ZERO;
//    for (int i = ZERO; i < TEN; ++i) {
//        digits[i] = ZERO;
//    }
//
//    while ((character = getchar()) != EOF) {
//        if (character >= ASCII_ZERO && character <= ASCII_NINE) {
//            ++digits[character - ASCII_ZERO];
//        }
//        else if (character == ASCII_SPACE || character == ASCII_NEWLINE || character == ASCII_TAB) {
//            ++whitespace;
//        }
//        else {
//            ++other;
//        }
//    }
//
//    printf("digits = ");
//    for (int i = ZERO; i < TEN; ++i) {
//        printf("%d:%d ", i, digits[i]);
//    }
//    printf(", white space = %d, other = %d\n", whitespace, other);
//
//}

//void frequency() {
//    int characters[TWENTYSIX];
//    int character;
//
//    for (int i = ZERO; i < TWENTYSIX; ++i) {
//        characters[i] = ZERO;
//    }
//
//    while ((character = getchar()) != EOF) {
//        if (character >= ASCII_a && character <= ASCII_z) {
//            ++characters[character - ASCII_a];
//        }
//    }
//
//    printf("\nCharacters = ");
//    for (int i = ZERO; i < TWENTYSIX; ++i) {
//        printf("%c:%d ", i + ASCII_a, characters[i]);
//    }
//}

//int power(int base, int exponent) {
//    return exponent > ONE ? base * power(base, exponent - ONE) : base;
//}

//int getline(char string[], int limit) {
//    int character, i;
//
//    for (i = ZERO; i < limit - ONE && (character = getchar()) != EOF && character != ASCII_NEWLINE; ++i) {
//        string[i] = (char) character;
//    }
//
//    if (character == ASCII_NEWLINE) {
//        string[i] = (char) character;
//        ++i;
//    }
//
//    string[i] = '\0';
//    return i;
//
//}


int main() {

//    int key[] = {1,2,5,4,5,6,7,1};
//    size_t key_length = 8;
//    size_t stream_size = 8;
//    int *ksa_stream = ksa(key, key_length, stream_size);
//
//    printf("KSA stream: ");
//    for (int i = 0; i < stream_size; ++i) {
//        printf("%d ", ksa_stream[i]);
//    }
//
//    size_t key_stream_size = 20;
//    int *key_stream = prga(ksa_stream, stream_size, key_stream_size);
//    free(ksa_stream);
//
//    printf("\nPRGA output: ");
//    for (int i = 0; i < key_stream_size; ++i) {
//        printf("%d ", key_stream[i]);
//    }
//    free(key_stream);

    // This is the variable input
    //char input[] = {0,1,2,3,4,5,6,7,8,9,10};
    unsigned char input[] = "Hello World how are you today?";
    size_t input_size = 30;

    // This is the fixed hash size
    const size_t HASH_SIZE = 8;

    // Allocate memory for the hash value. Could this be a literal value?
    // Char is probably 8 bit anyways and HASH_SIZE is fixed.
    unsigned char *hash_value = calloc(HASH_SIZE, sizeof(unsigned char));


    printf("Message: ");
    print_long_array(input, input_size);

    // Now hash the input
    hash(input, input_size, hash_value, HASH_SIZE);

    printf("Hash: ");
    print_long_array(hash_value, HASH_SIZE);

    // And finally free the hash value
    free(hash_value);

    prime_factors(25);
}




















