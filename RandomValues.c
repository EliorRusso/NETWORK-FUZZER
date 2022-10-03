#include <stdio.h>
#include <stdlib.h>
#include <time.h>
unsigned int printRandoms(int lower, int upper,int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
    }
}
unsigned int randomSourcePort(uint16_t src_port){
   int lower = 20, upper = 1000, count = 1;
    srand(time(0));
    src_port = printRandoms(lower, upper, count);
    return src_port; 
}
unsigned int randomDestPort(uint16_t dst_port){
   int lower = 20, upper = 1000, count = 1;
    srand(time(0));
    dst_port = printRandoms(lower, upper, count);
    return dst_port;
}
unsigned int randomQOS(uint8_t qos){
    int lower = 20, upper = 1000, count = 1;
    srand(time(0));
    qos = printRandoms(lower, upper, count);
    return qos;
}
unsigned int randomIdentification(uint8_t identification){
    int lower = 5, upper = 100, count = 1;
    srand(time(0));
    identification = printRandoms(lower, upper, count);
    return identification;
}
unsigned int randomTtl(uint8_t Ttl){
    int lower = 5, upper = 100, count = 1;
    srand(time(0));
    Ttl = printRandoms(lower, upper, count);
}
void randomProtocol(uint8_t proto){
    int lower = 5, upper = 100, count = 1;
    srand(time(0));
    printRandoms(lower, upper, count);
}
unsigned int randomChecksum(uint16_t checksum){
    int lower = 5, upper = 100, count = 1;
    srand(time(0));
    checksum = printRandoms(lower, upper, count);
    return checksum;
}