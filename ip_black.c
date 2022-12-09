#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvisibility"
#pragma clang diagnostic ignored "-Wconstant-conversion"
int ip4black[] = {
        3137448128,
        1644275904,
        16885952,
        2516691136,
        2197924032,
        1140959424
};

int xdp_prog1(struct CTXTYPE * ctx) {
    nh_off = sizeof( * eth);

    if (data + nh_off > data_end) {
        return rc;
    }
    h_proto = eth -> h_proto;
    if (h_proto == htons(ETH_P_IP)) {
        int ip = get_ipv4(data, nh_off, data_end);
        if (ip == NOIP) {
            return XDP_DROP;
        }
#pragma unroll
        for (int i = 0; i < BLACK4SIZE; i++) {
            if (ip4black[i] == ip) {
                return XDP_DROP;
            }
        }
        return XDP_PASS;
    } else if (h_proto == htons(ETH_P_ARP)) {
        return XDP_PASS;
    } else {
        return XDP_DROP;
    }
}

#pragma clang diagnostic pop