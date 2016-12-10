#include <stdio.h>
#include "crypto.h"
#include <gmp.h>


int main() {

    mpz_t p, q, n, m, e, d, cipher, plain;
    mpz_init_set_str(p, "9648423029010515676590551740010426534945737639235739800643989352039852507298491399561035009163427050370107570733633350911691280297777160200625281665378483", 10);
    mpz_init_set_str(q, "11874843837980297032092405848653656852760910154543380907650040190704283358909208578251063047732443992230647903887510065547947313543299303261986053486569407", 10);
    mpz_init_set_str(e, "65537", 10);
    mpz_init_set_str(cipher, "83208298995174604174773590298203639360540024871256126892889661345742403314929861939100492666605647316646576486526217457006376842280869728581726746401583705899941768214138742259689334840735633553053887641847651173776251820293087212885670180367406807406765923638973161375817392737747832762751690104423869019034", 10);
    mpz_init(n);
    mpz_init(d);
    mpz_init(m);
    mpz_init(plain);

    mpz_mul(n, q, p);

    mpz_out_str(stdout, 16, n);
    printf("\n");
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(m, p, q);

    mpz_out_str(stdout, 16, m);
    printf("\n");

    mpz_invert(d, e, m);

    mpz_out_str(stdout, 16, d);
    printf("\n");

    mpz_powm(plain, cipher, d, n);

    mpz_out_str(stdout, 10, plain);
    printf("\n");





//    int key[] = {1,0,1,0,1,0};
//    size_t sbox_size = 256;
//    int *sbox = ksa(key, 6, sbox_size);
//    print_int_array(sbox, sbox_size);
//
//    size_t keystream_size = 16;
//    int *keystream = prga(sbox, sbox_size, keystream_size);
//    print_int_array(keystream, keystream_size);
//
//    int *result = concatenate_bytes(keystream, keystream_size, keystream, keystream_size);
//    print_int_array(result, keystream_size * 2);
}




















