#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <asm/byteorder.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/ip.h>
#include <linux/tcp.h>

/* returns packet id */
static u_int32_t print_pkt (struct nfq_data *tb)
{
    int id = 0;
    struct nfqnl_msg_packet_hdr *ph;
    struct nfqnl_msg_packet_hw *hwph;
    u_int32_t mark,ifi; 
    int ret;
    unsigned char *data;

    ph = nfq_get_msg_packet_hdr(tb);
    if (ph) {
        id = ntohl(ph->packet_id);
        printf("hw_protocol=0x%04x hook=%u id=%u ",
                ntohs(ph->hw_protocol), ph->hook, id);
    }

    hwph = nfq_get_packet_hw(tb);
    if (hwph) {
        int i, hlen = ntohs(hwph->hw_addrlen);

        printf("hw_src_addr=");
        for (i = 0; i < hlen-1; i++)
            printf("%02x:", hwph->hw_addr[i]);
        printf("%02x ", hwph->hw_addr[hlen-1]);
    }

    mark = nfq_get_nfmark(tb);
    if (mark)
        printf("mark=%u ", mark);

    ifi = nfq_get_indev(tb);
    if (ifi)
        printf("indev=%u ", ifi);

    ifi = nfq_get_outdev(tb);
    if (ifi)
        printf("outdev=%u ", ifi);
    ifi = nfq_get_physindev(tb);
    if (ifi)
        printf("physindev=%u ", ifi);

    ifi = nfq_get_physoutdev(tb);
    if (ifi)
        printf("physoutdev=%u ", ifi);

    ret = nfq_get_payload(tb, &data);
    if (ret >= 0)
        printf("payload_len=%d ", ret);

    fputc('\n', stdout);

    return id;
}



#ifdef __LITTLE_ENDIAN
#define IPQUAD(addr) \
    ((unsigned char *)&addr)[0],                  \
((unsigned char *)&addr)[1],                \
((unsigned char *)&addr)[2],                \
((unsigned char *)&addr)[3]
#else
#define IPQUAD(addr)                            \
    ((unsigned char *)&addr)[3],                  \
((unsigned char *)&addr)[2],                \
((unsigned char *)&addr)[1],                \
((unsigned char *)&addr)[0]
#endif

static u_int16_t checksum(u_int32_t init, u_int8_t *addr, size_t count){
    /* Compute Internet Checksum for "count" bytes
     * beginning at location "addr".
     */
    u_int32_t sum = init;

    while( count > 1 ) {
        /* This is the inner loop */
        sum += ntohs(* (u_int16_t*) addr);
        addr += 2;
        count -= 2;
    }

    /* Add left-over byte, if any */
    if( count > 0 )
        sum += * (u_int8_t *) addr;

    /* Fold 32-bit sum to 16 bits */
    while (sum>>16)
        sum = (sum & 0xffff) + (sum >> 16);

    return (u_int16_t)~sum;
}

static u_int16_t ip_checksum(struct iphdr* iphdrp){
    return checksum(0, (u_int8_t*)iphdrp, iphdrp->ihl<<2);
}

static void set_ip_checksum(struct iphdr* iphdrp){
    iphdrp->check = 0;
    iphdrp->check = htons(checksum(0, (u_int8_t*)iphdrp, iphdrp->ihl<<2));
}

static u_int16_t tcp_checksum2(struct iphdr* iphdrp, struct tcphdr* tcphdrp){
    size_t tcplen = ntohs(iphdrp->tot_len) - (iphdrp->ihl<<2);
    u_int32_t cksum = 0;

    cksum += ntohs((iphdrp->saddr >> 16) & 0x0000ffff);
    cksum += ntohs(iphdrp->saddr & 0x0000ffff);
    cksum += ntohs((iphdrp->daddr >> 16) & 0x0000ffff);
    cksum += ntohs(iphdrp->daddr & 0x0000ffff);
    cksum += iphdrp->protocol & 0x00ff;
    cksum += tcplen;
    return checksum(cksum, (u_int8_t*)tcphdrp, tcplen);
}

static u_int16_t tcp_checksum1(struct iphdr* iphdrp){
    struct tcphdr *tcphdrp = 
        (struct tcphdr*)((u_int8_t*)iphdrp + (iphdrp->ihl<<2));

    return tcp_checksum2(iphdrp, tcphdrp);
}

static void set_tcp_checksum2(struct iphdr* iphdrp, struct tcphdr* tcphdrp){
    tcphdrp->check = 0;
    tcphdrp->check = htons(tcp_checksum2(iphdrp, tcphdrp));
}

static void set_tcp_checksum1(struct iphdr* iphdrp){
    struct tcphdr *tcphdrp = 
        (struct tcphdr*)((u_int8_t*)iphdrp + (iphdrp->ihl<<2));

    set_tcp_checksum2(iphdrp, tcphdrp);
}

static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
        struct nfq_data *nfa, void *data){
    (void)nfmsg;
    (void)data;
    u_int32_t id = 0;
    struct nfqnl_msg_packet_hdr *ph;
    unsigned char *pdata = NULL;
    int pdata_len;

    ph = nfq_get_msg_packet_hdr(nfa);
    if (ph){
        id = ntohl(ph->packet_id);
    }

    pdata_len = nfq_get_payload(nfa, (unsigned char**)&pdata);
    if(pdata_len == -1){
        pdata_len = 0;
    }

    struct iphdr *iphdrp = (struct iphdr *)pdata;

    printf("len %d iphdr %d %u.%u.%u.%u ->",
            pdata_len,
            iphdrp->ihl<<2,
            IPQUAD(iphdrp->saddr));
    printf(" %u.%u.%u.%u %s",
            IPQUAD(iphdrp->daddr),
            getprotobynumber(iphdrp->protocol)->p_name);
    printf(" ipsum %hu", ip_checksum(iphdrp));
    if(iphdrp->protocol == IPPROTO_TCP){
        printf(" tcpsum %hu", tcp_checksum1(iphdrp));
    }

#define TO "220.181.37.55"
#define DNAT_TO "64.233.189.104"

    if(iphdrp->daddr == inet_addr(TO)){
        printf(" !hacked!");
        iphdrp->daddr = inet_addr(DNAT_TO);
        set_ip_checksum(iphdrp);
        if(iphdrp->protocol == IPPROTO_TCP){
            set_tcp_checksum1(iphdrp);
            printf(" ipsum+ %hu tcpsum+ %hu",
                    ip_checksum(iphdrp), tcp_checksum1(iphdrp));
        }
    }

    if(iphdrp->saddr == inet_addr(DNAT_TO)){
        iphdrp->saddr = inet_addr(TO);
        printf(" !hacked!");
        set_ip_checksum(iphdrp);
        if(iphdrp->protocol == IPPROTO_TCP){
            set_tcp_checksum1(iphdrp);
            printf(" ipsum+ %hu tcpsum+ %hu",
                    ip_checksum(iphdrp), tcp_checksum1(iphdrp));
        }
    }

    printf("\n");

    return nfq_set_verdict2(qh, id, NF_REPEAT, 1,
            (u_int32_t)pdata_len, pdata);
}

int main(int argc, char **argv){
    struct nfq_handle *h;
    struct nfq_q_handle *qh;
    struct nfnl_handle *nh;
    int fd;
    int rv;
    char buf[4096];

    h = nfq_open();
    if (!h) {
        printf("open failed");
        exit(1);
    }

    if (nfq_unbind_pf(h, AF_INET) < 0){
        printf("unbind failed");
        exit(1);
    }

    if (nfq_bind_pf(h, AF_INET) < 0) {
        printf("bind failed");
        exit(1);
    }

    int qid = 0;
    if(argc == 2){
        qid = atoi(argv[1]);
    }
    printf("binding this socket to queue %d\n", qid);
    qh = nfq_create_queue(h,  qid, &cb, NULL);
    if (!qh) {
        printf("create failed");
        exit(1);
    }

    if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
        printf("set mode failed");
        exit(1);
    }

    nh = nfq_nfnlh(h);
    fd = nfnl_fd(nh);

    while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0) {
        printf("recv %d bytes\n", rv);
        nfq_handle_packet(h, buf, rv);
    }

    /* never reached */
    nfq_destroy_queue(qh);

    nfq_close(h);

    exit(0);
}

