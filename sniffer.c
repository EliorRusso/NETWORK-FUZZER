

#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<string.h>	//memset
#include<netinet/ip_icmp.h>	//Provides declarations for icmp header
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/tcp.h>	//Provides declarations for tcp header
#include<sys/socket.h>
#include<arpa/inet.h>
#include<linux/types.h>
#include<net/ethernet.h>
#include <features.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "fuzz.h"
#define ETH_ALEN 6

int sock_raw;
struct sockaddr_in source,dest;
void SocketConnect(unsigned char *buffer){
	int sock_raw;
	struct sockaddr_in source, dest;
	sock_raw=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	if(sock_raw<0)
	{
		printf("Error connecting to the raw socket.");
		return -1;
	}
	memset(buffer,0,65536);
	struct sockaddr saddr;
	int saddr_len = sizeof (saddr);
		int buflen=recvfrom(sock_raw,buffer,65536,0,&saddr,(socklen_t *)&saddr_len); //recieving a buffer through the raw socket and putting it in buflen
		if(buflen<0)
		{
			printf("Error recieving the packet");
			return -1;
		}
}
void PrintingPackets(unsigned char *buffer){
		struct ethdr *eth = (struct ethhdr *) (buffer);
	if(ntohs(eth->h_proto) == 2048){
		printf("Ethernet Header \n"); //printing mac addresses in hexa
		printf("Source As : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
		printf("Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
		printf("Protocol : %x \n",htons(eth->h_proto));//converting byte order to match protocol 0x0800
		printf("\n");
		unsigned short iphdrlen;
		struct iphr *iph = (struct iphr*)(buffer + sizeof(struct ethhdr));
		printf("IP header\n");
    	printf("\t\t\t |- Version : %d\n", iph->version); 
    	printf("\t\t\t |- Inter Header Length : %d DWORDS or %d BYTES\n", (unsigned int)iph->ihl, (unsigned int)iph->ihl * 4);
		printf("\t\t\t |- Type Of Service : %d\n", (unsigned char)iph->TypeOfService); //Also can be called Qos(Quality Of Service)
    	printf("\t\t\t |- Total Length : %d Bytes\n", (unsigned short)ntohs(iph->TotalLength)); //Length of the datagram
    	printf("\t\t\t |- Identification : %d\n", (unsigned short)iph->Identification); //Identification of the packet
    	printf("\t\t\t |- Time To Live : %d\n", (unsigned char)iph->Ttl); //Indicated the maximum time a data is allowed to be on the network.
    	printf("\t\t\t |- Protocol : %d\n", (unsigned char)iph->Protocol); //Protocol of the packet
    	printf("\t\t\t |- Header Checksum : %d\n", (unsigned short)ntohs(iph->HeaderChecksum));
		source.sin_addr.s_addr = iph->SourceAddr;
    	dest.sin_addr.s_addr = iph->DestAddr;
    	printf("\t\t\t |- Source IP : %s\n", inet_ntoa(source.sin_addr)); //Converting addresses into a string so it could be printed
    	printf("\t\t\t |- Destination IP : %s\n", inet_ntoa(dest.sin_addr));
		if(iph->Protocol == 6){
			struct tcpheader *tcph = (struct tcpheader *)buffer;
    		printf("\nTcp Header\n");
    		printf("\t\t\t |- Source Port\t : %d\n", (unsigned short)ntohs(tcph->SourcePort));
    		printf("\t\t\t |- Destination Port\t : %d\n", (unsigned short)ntohs(tcph->DestinationPort));
    		printf("\t\t\t |- Sequence Number\t : %d\n", (unsigned int)ntohs(tcph->SequenceNumber));
    		printf("\t\t\t |- Acknowledge Number\t : %d\n", (unsigned int)ntohs(tcph->AckNumber));
    		printf("\t\t\t |-Header Length : %d DWORDS or %d BYTES\n", (unsigned int)tcph->DataOffset, (unsigned int)tcph->DataOffset * 4);
    		printf("\n------------------------------------------------------flags------------------------------------------------------\n");
    		printf("\t\t\t\t |-Urgent flag : %d\n", (unsigned int)tcph->Urg); //Printing flags, each flag represent a different purpose and it's 1 bit in size
    		printf("\t\t\t\t |-Acknowledgement flag : %d\n", (unsigned int)tcph->Ack);
    		printf("\t\t\t\t |-push flag : %d\n", (unsigned int)tcph->Psh);
    		printf("\t\t\t\t |-Reset flag : %d\n", (unsigned int)tcph->Rst);
    		printf("\t\t\t\t |-Synchronise flag : %d\n", (unsigned int)tcph->Syn);
    		printf("\t\t\t\t |-Finish flag : %d\n", (unsigned int)tcph->Fin);
    		printf("\t\t\t |-Window size  :%d\n", (unsigned short)ntohs(tcph->Window));
    		printf("\t\t\t |- checksum  :%d\n", (unsigned short)ntohs(tcph->Checksum));
    		printf("\t\t\t |- Urgent pointer  :%d\n", (unsigned short)ntohs(tcph->UrgentPointer));
			char *remain;
			remain = buffer + sizeof(struct ethdr) + iph->ihl * 4 + tcph->DataOffset * 4;
			while (*remain){
				printf("%.2x\t", (unsigned)*remain);
				remain++;
			}
		}
		if(iph->Protocol == 17){
			struct udpheader *udph = (struct udpheader*)buffer;
    		printf("\nUdp Header\n");
    		printf("\t\t\t |- Source Port\t : %d\n", (unsigned short)ntohs(udph->SourcePort));
    		printf("\t\t\t |- Destination Port\t : %d\n", (unsigned short)ntohs(udph->DestinationPort));
			printf("\t\t\t |- Total Length : %d Bytes\n", (unsigned short)ntohs(udph->Length)); //Length of the datagram
			printf("\t\t\t |- Checksum : %d\n", (unsigned short)ntohs(udph->Checksum));
            if((unsigned short)ntohs(udph->DestinationPort) == 55055){
                printf("yes");
            }
			char *remain;
			remain = buffer +sizeof(eth) + iph->ihl * 4 + sizeof(udph);
			while (*remain){
				printf("%.2x\t", (unsigned)*remain);
				remain++;
			}
			
		}
		free(buffer);
		close(SOCK_RAW);
	}
}
int main(){
	while(1){
		unsigned char *buffer = (unsigned char *) malloc(65536);
		SocketConnect(buffer);
		PrintingPackets(buffer);
	}
}