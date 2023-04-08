typedef union protocol{
struct Nissim{
uint8_t SRC:3;
uint8_t DST:3;
uint8_t LEN:3;
uint8_t CHECK:3;
uint8_t FLAG:3;
}; uint8_t array[5];
};
int s[5] = {3,3,3,3,3};
int num = 5;
