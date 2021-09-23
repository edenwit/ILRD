
void GetPacketInfo(int *fd, struct in_pktinfo **pi)
{

    int opt = 0;
    /* sock is bound AF_INET socket, usually SOCK_DGRAM*/
    /* include struct in_pktinfo in the message "ancilliary" control data */
    setsockopt(*fd, IPPROTO_IP, IP_PKTINFO, &opt, sizeof(opt));
    /* the control data is dumped here */
    char cmbuf[0x100];
    /* the remote/source sockaddr is put here */
    struct sockaddr_in peeraddr;
    /* if you want access to the data you need to init the msg_iovec fields */
    struct msghdr mh = {
        .msg_name = &peeraddr,
        .msg_namelen = sizeof(peeraddr),
        .msg_control = cmbuf,
        .msg_controllen = sizeof(cmbuf),
    };
    recvmsg(*fd, &mh, 0);
    for ( /* iterate through all the control headers*/
        struct cmsghdr *cmsg = CMSG_FIRSTHDR(&mh);
        cmsg != NULL;
        cmsg = CMSG_NXTHDR(&mh, cmsg))
    {
        /* ignore the control headers that don't match what we want*/
        if (cmsg->cmsg_level != IPPROTO_IP ||
            cmsg->cmsg_type != IP_PKTINFO)
        {
            continue;
        }
        *pi = CMSG_DATA(cmsg);
        /* at this point, peeraddr is the source sockaddr
        pi->ipi_spec_dst is the destination in_addr
         pi->ipi_addr is the receiving interface in_addr*/
    }

    printf("My ip address: %d\n", getifaddrs());
    printf("%d\n", peeraddr.sin_addr.s_addr);

}