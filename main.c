#include<stdio.h>
#include <string.h>


#include <unistd.h>
#include <stdlib.h>
// #include "libtuntap.h"
// #include "libtuntap_linux.h"

#include "uip.h"
#include "uipopt.h"
#include "uip_arp.h"

#include "timer.h"
#include "rv_mtvec_map.h"
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

void
uip_log(char *m)
{
//   printf("uIP log message: %s\n", m);
}
/*uIP call back func*/
void uip_appcall(void)
{
	// printf("uip_appcall\n");fflush(stdout);
	// dhcpc_appcall();
	// switch(uip_conn->rport) {
	// 	case HTONS(SERVER_PORT):
	// 		if(uip_timedout()||uip_aborted()||uip_closed()){

	// 		}else if(uip_connected()){

	// 		}else if(uip_rexmit()){

	// 		}else if(uip_poll()){
	// 			/*poll connecte is idle*/

	// 		}else if(uip_acked()){
	// 			/*get a ack for send packet ok*/
	// 			if(uip_newdata()){

	// 			}
	// 		}else if(uip_newdata()){

	// 		}else{
	// 			/*error*/
	// 		}
	// 		break;
	// 	default:
	// 		/*discard packet*/
	// 		break;
	// }
}

void _putchar(char character){
    *(char *)(pdev_uart0_write_addr) = character;
}

static void hexdump(void *data, size_t size) {
	unsigned char *p = (unsigned char *)data;
	unsigned int c;
	size_t n;
	char bytestr[4] = {0};
	char addrstr[10] = {0};
	char hexstr[16 * 3 + 5] = {0};
	char charstr[16 * 1 + 5] = {0};
	char buf[1024];

	for (n = 1; n <= size; n++) {
		if (n % 16 == 1) {
			/* store address for this line */
			snprintf(addrstr, sizeof(addrstr), "%.4zx",
			    (p - (unsigned char *)data) );
		}

		c = *p;
		if (isalnum(c) == 0) {
			c = '.';
		}

		/* store hex str (for left side) */
		snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
		strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);

		/* store char str (for right side) */
		snprintf(bytestr, sizeof(bytestr), "%c", c);
		strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);

		if (n % 16 == 0) { 
			/* line completed */
			(void)memset(buf, 0, sizeof buf);
			(void)snprintf(buf, sizeof buf,
			    "[%4.4s]   %-50.50s  %s", addrstr, hexstr, charstr);
			printf("%s\r\n",buf);
			hexstr[0] = 0;
			charstr[0] = 0;
		} else if (n % 8 == 0) {
			/* half line: add whitespaces */
			strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
			strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
		}
		p++; /* next byte */
	}

	/* print the rest of the buffer if not empty */
	if (strlen(hexstr) > 0) {
		(void)memset(buf, 0, sizeof buf);
		(void)snprintf(buf, sizeof buf, "[%4.4s]   %-50.50s  %s",
				addrstr, hexstr, charstr);
		printf("%s\r\n",buf);
	}
}

void juice_netcrard_send(uint8_t *buf,int size){
	int tmp_i = 0;
	int tmp_cnt = 0;
	// size--;
	// while(size - tmp_cnt > 0){
		// if(size - tmp_cnt >= (pdev_netcard0_write_end_addr - pdev_netcard0_write_addr)){
		// 	for(tmp_i = 0;tmp_i < (pdev_netcard0_write_end_addr - pdev_netcard0_write_addr);tmp_i++){
				
		// 		*((unsigned char *)(pdev_netcard0_write_addr)+tmp_i) = buf[tmp_cnt];
		// 		tmp_cnt++;
		// 	}
		// 	*((unsigned char *)(pdev_netcard0_write_cnt_H_addr)) = (pdev_netcard0_write_end_addr - pdev_netcard0_write_addr) >> 8;
		// 	*((unsigned char *)(pdev_netcard0_write_cnt_L_addr)) = (pdev_netcard0_write_end_addr - pdev_netcard0_write_addr) & 0xff;
		// 	*((unsigned char *)(pdev_netcard0_write_start_addr)) = 1;
		// }else{
		// 	for(tmp_i = 0;tmp_i < (size - tmp_cnt);tmp_i++){
				
		// 		*((unsigned char *)(pdev_netcard0_write_addr)+tmp_i) = buf[tmp_cnt+tmp_i];
		// 	}
		// 	*((unsigned char *)(pdev_netcard0_write_cnt_H_addr)) = (size - tmp_cnt) >> 8;
		// 	*((unsigned char *)(pdev_netcard0_write_cnt_L_addr)) = (size - tmp_cnt) & 0xff;
		// 	*((unsigned char *)(pdev_netcard0_write_start_addr)) = 1;
			
		// 	return;
		// }
		// if(size == 291){
				
		// 	printf("juice_netcrard_send %x size %d\r\n",buf[0],size);
		// 	hexdump(buf,size);
		// }
		for(tmp_i = 0;tmp_i < size;tmp_i++){
			
			*((unsigned char *)(pdev_netcard0_write_addr)+tmp_i) = buf[tmp_i];
		}
		*((unsigned char *)(pdev_netcard0_write_cnt_H_addr)) = size >> 8;
		*((unsigned char *)(pdev_netcard0_write_cnt_L_addr)) = size & 0xff;
		*((unsigned char *)(pdev_netcard0_write_start_addr)) = 1;

	// }
}
void hexdump(void *data, size_t size);
// struct libtuntap_device_t *tun_dev;
int main(int argc, char **argv){
    int port;
	struct timer periodic_timer, arp_timer;


	uint8_t i;
    // if ( argc != 2){
    //     fprintf(stderr,"usage:%s<port>\n", argv[0]);
    //     exit(0);
    // }
    // port = atoi(argv[1]);  // get port
    printf("uip tun/tap test\r\n");
	// extern void juicevm_mem_init(void);
	// juicevm_mem_init();
    int ret;
	

	ret = 1;
	// tun_dev = libtuntap_init();
	// printf("libtuntap_init\r\n");fflush(stdout);
	// libtuntap_promisc_start(tun_dev);
	// printf("libtuntap_promisc_start\r\n");fflush(stdout);

	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);
    /* Initialize the ARP */
	uip_arp_init();

	/* Initialize the uIP TCP/IP stack. */
	uip_init();
	printf("uip_init\r\n");fflush(stdout);
	/*set host MAC addr*/
	uip_ethaddr.addr[0] = 0x12;
	uip_ethaddr.addr[1] = 0x34;
	uip_ethaddr.addr[2] = 0x56;
	uip_ethaddr.addr[3] = 0x78;
	uip_ethaddr.addr[4] = 0x90;
	uip_ethaddr.addr[5] = 0xAC;
	dhcpc_init( uip_ethaddr.addr, 6);
	printf("dhcpc_init\r\n");fflush(stdout);
	dhcpc_request();
	printf("dhcpc_request\r\n");fflush(stdout);
// #if UIP_FIXEDADDR == 0
// 	/*host ip addr*/
// 	uip_ipaddr(ipaddr, 192,168,0,201);
// 	uip_sethostaddr(ipaddr);

// 	/*netmask addr*/
// 	uip_ipaddr(ipaddr, 255,255,255,0);
// 	uip_setnetmask(ipaddr);

// 	/*router ip addr*/
// 	uip_ipaddr(ipaddr, 192,168,0,1);
// 	uip_setdraddr(ipaddr);
// #endif

	// dhcpc_init(const void *mac_addr, int mac_len)
	// /*connect to server*/
	// uip_ipaddr(ipaddr, 192,168,0,15);
	// uip_connect(ipaddr, HTONS(SERVER_PORT));

	while(1) {
		// uip_len = tapdev_read();
		// printf("libtuntap_rxdata %p %d\r\n",uip_buf,UIP_BUFSIZE);
		// int tmp_recv_len = libtuntap_rxdata(tun_dev, uip_buf, UIP_BUFSIZE);
		// printf("libtuntap_rxdata %p %d tmp_recv_len %d\r\n",uip_buf,UIP_BUFSIZE,tmp_recv_len);
		if(*((unsigned char *)(pdev_netcard0_state_addr)) == pdev_netcard0_readbusy_state){
			// printf("pdev_netcard0_readbusy_state\r\n");
			uint16_t tmp_recv_cnt = *((unsigned char *)(pdev_netcard0_readbuf_cnt_H_addr)) << 8;
			tmp_recv_cnt = tmp_recv_cnt + *((unsigned char *)(pdev_netcard0_readbuf_cnt_L_addr));
			uint16_t tmp_cpy_cnt = 0;
			while(tmp_cpy_cnt < tmp_recv_cnt){
				uip_buf[tmp_cpy_cnt] = *((unsigned char *)(pdev_netcard0_read_addr) + tmp_cpy_cnt);
				tmp_cpy_cnt++;
			}
			// uip_buf[0] = *((unsigned char *)(pdev_netcard0_read_addr));
			// printf("libtuntap_rxdata %x %d tmp_recv_cnt %d\r\n",uip_buf[0],UIP_BUFSIZE,tmp_recv_cnt);
			*((unsigned char *)(pdev_netcard0_state_addr)) = pdev_netcard0_free_state;
			uip_len = tmp_recv_cnt;
		}else{
			uip_len = 0;
		}
		if(uip_len > 0) {
			// printf("uip_len %d\r\n",uip_len);
			if(BUF->type == htons(UIP_ETHTYPE_IP)) {
				// printf("BUF->type == htons(UIP_ETHTYPE_IP)\r\n");
				uip_arp_ipin();
				// printf("uip_arp_ipin\r\n");
				uip_input();
				// printf("uip_input\r\n");
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
					// printf("uip_arp_out\r\n");
					uip_arp_out();
					// printf("libtuntap_txdata uip_len %d\r\n",uip_len);
					//   tapdev_send();
					
					juice_netcrard_send( uip_buf, uip_len);
				}
			} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
				// printf("BUF->type == htons(UIP_ETHTYPE_ARP)\r\n");
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
				//   tapdev_send();
					juice_netcrard_send( uip_buf, uip_len);
				}
			}
		} 
		// else {
			// // printf("timer_expired(&periodic_timer) %d\r\n",timer_expired(&periodic_timer));
			// // printf("timer_expired %lld %lld\r\n",(clock_time_t)(clock_time() - periodic_timer.start,(clock_time_t)periodic_timer.interval));fflush(stdout);
			if(timer_expired(&periodic_timer)) {
				// printf("timer_expired(&periodic_timer) %d UIP_CONNS %d\r\n",timer_expired(&periodic_timer),UIP_CONNS);
				timer_reset(&periodic_timer);
				for(i = 0; i < UIP_CONNS; i++) {
					uip_periodic(i);
					/* If the above function invocation resulted in data that
					should be sent out on the network, the global variable
					uip_len is set to a value > 0. */
					if(uip_len > 0) {
						uip_arp_out();
						//   tapdev_send();
						juice_netcrard_send( uip_buf, uip_len);
					}
				}

			// #if UIP_UDP
				// printf("UIP_UDP_CONNS %d\r\n",UIP_UDP_CONNS);
				for(i = 0; i < UIP_UDP_CONNS; i++) {
					// printf("UIP_UDP_CONNS %d i %d try\r\n",UIP_UDP_CONNS,i);
					uip_udp_periodic(i);
					// printf("UIP_UDP_CONNS %d i %d try end\r\n",UIP_UDP_CONNS,i);
					/* If the above function invocation resulted in data that
					should be sent out on the network, the global variable
					uip_len is set to a value > 0. */
					if(uip_len > 0) {
						// printf("uip_arp_out try i %d try\r\n",i);
						uip_arp_out();
						// printf("uip_arp_out end i %d try\r\n",i);
						//   tapdev_send();
						// printf("UIP_UDP_CONNS %d sent\r\n",UIP_UDP_CONNS);
						juice_netcrard_send( uip_buf, uip_len);
						// printf("UIP_UDP_CONNS %d end\r\n",UIP_UDP_CONNS);
					}
				}
			// #endif /* UIP_UDP */
				
				/* Call the ARP timer function every 10 seconds. */
				if(timer_expired(&arp_timer)) {
					timer_reset(&arp_timer);
					uip_arp_timer();
				}
			}
		// }
	}
	return ret;
    
}
void
dhcpc_configured(const struct dhcpc_state *s)
{
	printf("Got IP address %d.%d.%d.%d\n",
		uip_ipaddr1(s->ipaddr), uip_ipaddr2(s->ipaddr),
		uip_ipaddr3(s->ipaddr), uip_ipaddr4(s->ipaddr));
	printf("Got netmask %d.%d.%d.%d\n",
		uip_ipaddr1(s->netmask), uip_ipaddr2(s->netmask),
		uip_ipaddr3(s->netmask), uip_ipaddr4(s->netmask));
	printf("Got DNS server %d.%d.%d.%d\n",
		uip_ipaddr1(s->dnsaddr), uip_ipaddr2(s->dnsaddr),
		uip_ipaddr3(s->dnsaddr), uip_ipaddr4(s->dnsaddr));
	printf("Got default router %d.%d.%d.%d\n",
		uip_ipaddr1(s->default_router), uip_ipaddr2(s->default_router),
		uip_ipaddr3(s->default_router), uip_ipaddr4(s->default_router));
	printf("Lease expires in %ld seconds\n",
		ntohs(s->lease_time[0])*65536ul + ntohs(s->lease_time[1]));
	uip_sethostaddr(s->ipaddr);
	uip_setnetmask(s->netmask);
	uip_setdraddr(s->default_router);
	while(1);
	exit(0);
//   resolv_conf(s->dnsaddr);
}

// void hexdump(void *data, size_t size) {
// 	unsigned char *p = (unsigned char *)data;
// 	unsigned int c;
// 	size_t n;
// 	char bytestr[4] = {0};
// 	char addrstr[10] = {0};
// 	char hexstr[16 * 3 + 5] = {0};
// 	char charstr[16 * 1 + 5] = {0};
// 	char buf[1024];

// 	for (n = 1; n <= size; n++) {
// 		if (n % 16 == 1) {
// 			/* store address for this line */
// 			snprintf(addrstr, sizeof(addrstr), "%.4zx",
// 			    (p - (unsigned char *)data) );
// 		}

// 		c = *p;
// 		if (isalnum(c) == 0) {
// 			c = '.';
// 		}

// 		/* store hex str (for left side) */
// 		snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
// 		strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);

// 		/* store char str (for right side) */
// 		snprintf(bytestr, sizeof(bytestr), "%c", c);
// 		strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);

// 		if (n % 16 == 0) { 
// 			/* line completed */
// 			(void)memset(buf, 0, sizeof buf);
// 			(void)snprintf(buf, sizeof buf,
// 			    "[%4.4s]   %-50.50s  %s", addrstr, hexstr, charstr);
// 			printf("%s\r\n",buf);
// 			hexstr[0] = 0;
// 			charstr[0] = 0;
// 		} else if (n % 8 == 0) {
// 			/* half line: add whitespaces */
// 			strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
// 			strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
// 		}
// 		p++; /* next byte */
// 	}

// 	/* print the rest of the buffer if not empty */
// 	if (strlen(hexstr) > 0) {
// 		(void)memset(buf, 0, sizeof buf);
// 		(void)snprintf(buf, sizeof buf, "[%4.4s]   %-50.50s  %s",
// 				addrstr, hexstr, charstr);
// 		printf("%s\r\n",buf);
// 	}
// }