#include<stdio.h>
#include<string.h>
#include "itoa.c"
#include<malloc.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<netinet/udp.h>
#include<linux/if_packet.h>
#include<arpa/inet.h>
#include "fuzz.h"
#include "RandomValues.c"
#include "AddProtocol.h"
 #define DESTMAC0	0x08
 #define DESTMAC1	0x00
 #define DESTMAC2	0x27
 #define DESTMAC3	0x01
 #define DESTMAC4	0x0b
 #define DESTMAC5	0x6d
 #define destination_ip 127.0.0.1 
 uint16_t srcportseed = 23;
 unsigned int randomcounter = 20;
 uint16_t dstportseed = 23;
 unsigned int randomcounter2 = 20;
 uint16_t checksumseed = 23;
 unsigned int randomcounter3 = 20;
void build(){
    struct ifreq ifreq_c,ifreq_i,ifreq_ip; /// for each ioctl keep diffrent ifreq structure otherwise error may come in sending(sendto )
	InstanceProtocol* pInstance;
    pInstance = malloc(sizeof(InstanceProtocol));
    int sock_raw;
    unsigned char *sendbuff;
    int total_len=0,send_len;
    sock_raw=socket(AF_PACKET,SOCK_RAW,IPPROTO_RAW);
	if(sock_raw == -1)
		printf("error in socket");
	sendbuff=(unsigned char*)malloc(64); // increase in case of large data.Here data is --> AA  BB  CC  DD  EE
	memset(sendbuff,0,64);
    memset(&ifreq_i,0,sizeof(ifreq_i));
	strncpy(ifreq_i.ifr_name,"wlo1",IFNAMSIZ-1);
	if((ioctl(sock_raw,SIOCGIFINDEX,&ifreq_i))<0)
		printf("error in index ioctl reading");
    memset(&ifreq_c,0,sizeof(ifreq_c));
	strncpy(ifreq_c.ifr_name,"wlo1",IFNAMSIZ-1);

	if((ioctl(sock_raw,SIOCGIFHWADDR,&ifreq_c))<0)
		printf("error in SIOCGIFHWADDR ioctl reading");
	struct ethdr *eth = (struct ethdr *)(sendbuff);
  	eth->h_source[0] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[0]);
  	eth->h_source[1] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[1]);
   	eth->h_source[2] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[2]);
   	eth->h_source[3] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[3]);
   	eth->h_source[4] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[4]);
   	eth->h_source[5] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[5]);
   	eth->h_dest[0]    =  DESTMAC0;
   	eth->h_dest[1]    =  DESTMAC1;
   	eth->h_dest[2]    =  DESTMAC2;
  	eth->h_dest[3]    =  DESTMAC3;
   	eth->h_dest[4]    =  DESTMAC4;
   	eth->h_dest[5]    =  DESTMAC5;
   	eth->h_proto = htons(ETH_P_IP);   //0x800
	total_len+=sizeof(struct ethhdr);
    memset(&ifreq_ip,0,sizeof(ifreq_ip));
	strncpy(ifreq_ip.ifr_name,"wlo1",IFNAMSIZ-1);
  	 if(ioctl(sock_raw,SIOCGIFADDR,&ifreq_ip)<0)
 	 {
		printf("error in SIOCGIFADDR \n");
	 }
	printf("%s\n",inet_ntoa((((struct sockaddr_in*)&(ifreq_ip.ifr_addr))->sin_addr)));
	struct iphr *iph = (struct iphr*)(sendbuff + sizeof(struct ethhdr));
	iph->ihl	= 5;
	iph->version	= 4;
	iph->TypeOfService	= randomQOS(iph->TypeOfService);
	iph->Identification		= htons(randomIdentification(iph->Identification));
	iph->Ttl= randomTtl(iph->Ttl);
	iph->Protocol	= 17;
	iph->SourceAddr	= inet_addr(inet_ntoa((((struct sockaddr_in *)&(ifreq_ip.ifr_addr))->sin_addr)));
	iph->DestAddr	= inet_addr("destination_ip"); // put destination IP address
	total_len += sizeof(struct iphdr); 
    
    struct udpheader *uh = (struct udpheader *)(sendbuff + sizeof(struct iphr) + sizeof(struct ethdr));
	uh->SourcePort	= htons(23451);
	uh->DestinationPort	= htons(55055);
	uh->Checksum	= 0;
	total_len+= sizeof(struct udpheader);
	total_len++;
	
	char* readline(){
    FILE *file;
    file = fopen("AddProtocol.h","r");
    char tmp[256]={0x0};
    char *tmpline;
    int numline = 1;
    while(file != NULL && fgets(tmp, sizeof(tmp),file) !=NULL)
    	{
        	tmpline = strstr(tmp,"_f");
        	if(tmpline) {
            	printf("%d - %s", numline, tmp);
    		}
			unsigned int temp = 0;
			unsigned int temp2 = 0;
			char buffer1[10];
			int count = 0;
			temp = printRandoms(1,100,1);
			pInstance->tmp = temp;
			sendbuff[total_len] = ((int)temp);
			printf("\n%d", temp);
			total_len+=2;
    	numline++;
    	}
    if (file != NULL) fclose(file);
	/*
	for(int i=0; i<=(sizeof(pInstance->array)/4); i++){
		unsigned int temp = 0;
		unsigned int temp2 = 0;
		char buffer1[10];
		int count = 0;
		temp = printRandoms(1,100,1);
		pInstance->array[i] = temp;
		sendbuff[total_len] = ((int)temp);
		printf("\n%d", temp);
		total_len+=2;
	}
	*/
	uh->Length = htons(21);
    struct sockaddr_ll sadr_ll;
	sadr_ll.sll_ifindex = ifreq_i.ifr_ifindex;
	sadr_ll.sll_halen   = ETH_ALEN;
	sadr_ll.sll_addr[0]  = DESTMAC0;
	sadr_ll.sll_addr[1]  = DESTMAC1;
	sadr_ll.sll_addr[2]  = DESTMAC2;
	sadr_ll.sll_addr[3]  = DESTMAC3;
	sadr_ll.sll_addr[4]  = DESTMAC4;
	sadr_ll.sll_addr[5]  = DESTMAC5;
	
	send_len = sendto(sock_raw,sendbuff,64,0,(const struct sockaddr*)&sadr_ll,sizeof(struct sockaddr_ll));
		if(send_len<0)
		{
			printf("error in sending....sendlen=%d....errno=%d\n",send_len,errno);
			return -1;
		}
	}
}
int main(){
    while(1){
        build();
        sleep(1);
		randomcounter = randomSourcePort(srcportseed);
		randomcounter2 = randomDestPort(dstportseed);
		randomcounter3 = randomChecksum(checksumseed);
    }
}