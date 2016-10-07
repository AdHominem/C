//
// Created by jk on 05.10.16.
//

#include <assert.h>
#define ASCII_LOWERCASE_OFFSET 'a'
#define ASCII_UPPERCASE_OFFSET 'A'


// ############### MATH ################


long gcd(long first, long second) {
    if (first < second) {
        long temp = first;
        first = second;
        second = temp;
    }

    long remainder = first % second;
    //printf("%ld %% %ld = %ld\n", first, second, remainder);
    return (remainder) == 0 ? second : gcd(second, remainder);
}

//buggy
void eea(long first, long second) {
    assert(first > second && first > 0 && second > 0);
    long remainder, quotient, old_x = 1, old_y = 0, x = 0, y = 1, temp;

    do {
        remainder = first % second;
        quotient = first / second;

        // Temp is necessary to move values of x and y to old_x and old_y and still use them
        temp = x;
        x = old_x - quotient * x;
        old_x = temp;
        temp = y;
        y = old_y - quotient * y;
        old_y = temp;

        printf("%ld \t %ld \t %ld \t %ld \t %ld \t %ld \t\n", first, second, quotient, remainder, x, y);
        first = second;
        second = remainder;
    } while (remainder != 0);
}

// No Erastothenes ;-)
int isPrime(int number) {
    int i;
    for (i = 2; i * i <= number; ++i) {
        if (number % i == 0) return 0;
    }
    return 1;
}

// This could be faster by checking if number is a multiple of a prime
int euler_phi(int number) {
    if (isPrime(number)) return number - 1;

    int result = 0;

    for (int i = 1; i < number; ++i) {
        if (gcd(i, number) == 1) {
            result++;
        }
    }

    return result;
}

void swap(int *array, size_t first, size_t second) {
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}


// ############### CIPHERS ################


// Generates an identity permutation of array of size n, using a specified key
int *ksa(int *key, size_t key_length, size_t stream_size) {
    int *result = malloc(sizeof(int) * stream_size);

    for (int i = 0; i < stream_size; ++i) {
        result[i] = i;
    }

    size_t j = 0;
    for (size_t i = 0; i < stream_size; ++i) {
        j = (j + result[i] + key[i % key_length]) % stream_size;
        swap(result, i, j);
    }

    return result;
}

// Creates a key stream array of specified size
int *prga(int *stream, size_t stream_length, size_t size) {
    size_t j = 0, i = 0;
    int *result = malloc(sizeof(int) * size);

    for (int k = 0; k < size; ++k) {
        assert(j < stream_length);
        assert(i < stream_length);
        assert((stream[i] + stream[j]) % stream_length < stream_length);

        i = ++i % stream_length;
        j = (j + stream[i]) % stream_length;
        swap(stream, i, j);
        result[k] = stream[(stream[i] + stream[j]) % stream_length];
    }

    return result;
}

char shift_letter(char letter, int key) {
    assert(key >= 0 && key <= 25);

    int isLowerCase = letter >= 'a' && letter <= 'z';
    int isUpperCase = letter >= 'A' && letter <= 'Z';
    char offset = (char) (isLowerCase ? ASCII_LOWERCASE_OFFSET : ASCII_UPPERCASE_OFFSET);

    return (isLowerCase || isUpperCase) ? (char) ((letter + key - offset) % 26 + offset) : letter;
}

char *shift_cipher(char *text, size_t length, int key) {
    assert(key >= 0 && key <= 25);

    char *result = malloc(sizeof(char) * length);

    for (int i = 0; i < length; ++i) {
        result[i] = shift_letter(text[i], key);
    }

    return result;
}

char affine_shift_letter(char letter, int a, int b) {
    assert(gcd(26, a) == 1 && b < 26 && b >= 0);

    int isLowerCase = letter >= 'a' && letter <= 'z';
    int isUpperCase = letter >= 'A' && letter <= 'Z';
    char offset = (char) (isLowerCase ? ASCII_LOWERCASE_OFFSET : ASCII_UPPERCASE_OFFSET);

    return (isLowerCase || isUpperCase) ? (char) ((a * (letter - offset) + b) % 26 + offset) : letter;
}

char *affine_shift_cipher(char *text, size_t length, int a, int b) {
    assert(gcd(26, a) == 1 && b < 26 && b >= 0);

    char *result = malloc(sizeof(char) * length);

    for (int i = 0; i < length; ++i) {
        result[i] = affine_shift_letter(text[i], a, b);
    }

    return result;
}