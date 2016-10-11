//
// Created by jk on 05.10.16.
//

#include <assert.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#define ASCII_LOWERCASE_OFFSET 'a'
#define ASCII_UPPERCASE_OFFSET 'A'


// ############### HELPER ################


size_t random_index() {
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand((unsigned int) ((t1.tv_usec * t1.tv_sec) + getpid()));
    return (size_t) rand();
}

void print_long_array(unsigned char *array, size_t size) {

    for (size_t i = 0; i < size; ++i) {
        printf("%2x ", array[i]);
    }
    printf("\n");
}


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

long gcd_iterative(long rest0, long rest1) {
    if (rest0 < rest1) {
        long temp = rest0;
        rest0 = rest1;
        rest1 = temp;
    }

    long current_rest;

    do {
        current_rest = rest0 % rest1;
        printf("%5ld %% %4ld = %3ld\n", rest0, rest1, current_rest);
        rest0 = rest1;
        rest1 = current_rest;
    } while (current_rest != 0);

    return rest0;
}

// Assumes a is the modulus and b the number
long eea(long a, long b, long *x, long *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }


    long x1, y1;
    long remainder = b % a;
    long gcd = eea(remainder, a, &x1, &y1);
    long quotient = b / a;


    /* Explanation:
     * 1) We want x,y so that a * x + b * y = gcd
     * 2) Then the iteration before is (b % a) * x1 + a * y1 = gcd
     * 3) b / a is the integer quotient q.
     * 4) If we multiply q by a, that is the number of a which fit into b
     * 5) So we can rewrite b % a = b - q * a
     * 6) This lead to (b - q * a) * x1 + a * y1 = gcd
     * 7) Which can be rewritten to b * x1 + a * (y1 - q * x1) = gcd
     * 8) From this equation it follows that:
     *      x = y1 - q * x1
     *      y = x1
     * 9) We see that in each iteration
     *      - the new y is the old x
     *      - the new x is the old y minus q times the old x
     * */
    *x = y1 - quotient * x1;
    *y = x1;
    printf("%4ld \t %4ld \t %4ld / %4ld = %4ld \t %4ld %% %4ld = %4ld \t %4ld \t %4ld\n", a, b, b, a, quotient, b, a, remainder, *x, *y);

    return gcd;
}

long eea_iterative(long a, long b, long *x, long *y) {

    long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    long current_rest, quotient;

    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }

    while (b > 0) {
        current_rest = a % b;
        quotient = a / b;
        *x = x0 - quotient * x1;
        *y = y0 - quotient * y1;
        a = b;
        b = current_rest;
        printf("%4ld \t %4ld \t %4ld / %4ld = %4ld \t %4ld %% %4ld = %4ld \t %4ld \t %4ld\n", a, b, a, b, quotient, a, b, current_rest, *x, *y);
        x0 = x1;
        x1 = *x;
        y0 = y1;
        y1 = *y;
    }

    *x = x0;
    *y = y0;
    return a;
}

long inverse(long number, long modulus) {
    long x, y;
    eea(modulus, number, &x, &y);
    return y;
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

void swap_elements(int *array, size_t first, size_t second) {
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
        swap_elements(result, i, j);
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
        swap_elements(stream, i, j);
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


// ############### HASHES ################


// Shuffles a given array
void shuffle(unsigned char *input, size_t size) {


    size_t j = 0;
    for (size_t i = 0; i < size; ++i) {

        // Not cryptographically secure! But does the job
        j = (j + input[i]) % size;

        //printf("Swapping input[%zu] (%d) with input[%zu] (%d):\t", i, input[i], j, input[j]);
        //print_long_array(input, size);

        // swap
        unsigned char temp = input[i];
        input[i] = input[j];
        input[j] = temp;
    }
}

// Simple (and bad :-) ) hash function which reduces an arbitrarily large array to an 8 byte array
// Each output byte depends on all preceding output bytes.
// 1. Preimage resistance: Check
// 2. Second preimage resistance: Probably not
// 3. Collision resistance: Hell no!
void hash(unsigned char *input, size_t input_size, unsigned char *output, size_t output_size) {

    //if input_size < output_size we need to extend input
    if (input_size < output_size) {
        unsigned char *extended_input = calloc(output_size, sizeof(unsigned char));
        memcpy(extended_input, input, input_size);
        input = extended_input;
        input_size = output_size;
        printf("After extending: ");
        print_long_array(input, input_size);

        shuffle(input, input_size);
        printf("After shuffling: ");
        print_long_array(input, input_size);
    }


    unsigned char last_output = input[input_size - 1];

    //generate output, looping over input
    for (size_t i = 0; i < input_size; ++i) {
        last_output = output[i % output_size] = input[i] ^ last_output;
        //printf("current input: %2x, new output[%zu] (and next rounds last_output): %2x\n", input[i], i % output_size, last_output);
    }
}