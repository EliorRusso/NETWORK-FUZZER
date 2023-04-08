#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef union protocol {
    struct Nissim {
        uint16_t barak:16;
        uint16_t shmerling:8;
    } nissim;
    uint16_t array[2];
} Protocol;

int main(void) {
    int s[2] = {16,8};
    int num = 2;

    Protocol p;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        // Determine the maximum value based on the bit size
        uint16_t max_value = (1 << s[i]) - 1;

        // Generate a random value between 0 and the maximum value
        uint16_t value = rand() % (max_value + 1);

        // Determine the number of bytes needed to store the field
        int num_bytes = (s[i] + 7) / 8;

        // Assign the value to the appropriate field in the struct
        uint16_t mask = (1 << s[i]) - 1;
        for (int j = 0; j < num_bytes; j++) {
            p.array[i] &= ~(mask << (8 * j));
            p.array[i] |= (value & mask) << (8 * j);
            value >>= 8;
        }
    }

    // Print out the values for verification
    printf("barak: %u\n", p.nissim.barak);
    printf("shmerling: %u\n", p.nissim.shmerling);

    return 0;
}