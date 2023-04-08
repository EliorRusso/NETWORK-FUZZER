#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/udp.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
void print_ip_header(unsigned char* Buffer, int Size, FILE *logfile)
{
	unsigned short iphdrlen;
		
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen =iph->ihl*4;
	
	fprintf(logfile,"\n");
	fprintf(logfile,"IP Header\n");
	fprintf(logfile,"   |-IP Version        : %d\n",(unsigned int)iph->version);
	fprintf(logfile,"   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
	fprintf(logfile,"   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
	fprintf(logfile,"   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
	fprintf(logfile,"   |-Identification    : %d\n",ntohs(iph->id));
	//fprintf(logfile,"   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
	//fprintf(logfile,"   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
	//fprintf(logfile,"   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
	fprintf(logfile,"   |-TTL      : %d\n",(unsigned int)iph->ttl);
	fprintf(logfile,"   |-Protocol : %d\n",(unsigned int)iph->protocol);
	fprintf(logfile,"   |-Checksum : %d\n",ntohs(iph->check));
}


void print_udp_packet(unsigned char *Buffer , int Size,FILE *logfile)
{
	
	unsigned short iphdrlen;
	
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen = iph->ihl*4;
	
	struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen);
	
	fprintf(logfile,"\n\n***********************UDP Packet*************************\n");
	
	print_ip_header(Buffer,Size, logfile);			
	
	fprintf(logfile,"\nUDP Header\n");
	fprintf(logfile,"   |-Source Port      : %d\n" , ntohs(udph->source));
	fprintf(logfile,"   |-Destination Port : %d\n" , ntohs(udph->dest));
	fprintf(logfile,"   |-UDP Length       : %d\n" , ntohs(udph->len));
	fprintf(logfile,"   |-UDP Checksum     : %d\n" , ntohs(udph->check));
	
	fprintf(logfile,"\n");
	fprintf(logfile,"IP Header\n");
}