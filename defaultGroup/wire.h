struct WIRE_ETH_S { uint<48> Dst; uint<48> Src; uint<16> Type; };
WIRE_ETH_S wireEth;
struct WIRE_IP_S {
 uint<8> VI; uint<8> Tos; uint<16> Len; uint<16> Id; uint<16> Frag;
 uint<8> Ttl; uint<8> Proto; uint<16> Sum; uint<32> Src; uint<32> Dst;
};
WIRE_IP_S wireIp;
struct WIRE_UDP_S { uint<16> Src; uint<16> Dst; uint<16> Len; uint<16> Sum; };
WIRE_UDP_S wireUdp;
struct WIRE_BTH_S {
 uint<8> Op; uint<8> Flags; uint<16> Pkey; uint<8> R0; uint<24> Qp;
 uint<8> R1; uint<24> Psn;
};
WIRE_BTH_S wireBth;
struct WIRE_AETH_S { uint<8> Syndrome; uint<24> Msn; };
WIRE_AETH_S wireAeth;
struct WIRE_CRC_S { uint<32> Value; };
WIRE_CRC_S wireCrc;
struct WIRE_CMD_S {
 uint<32> D0; uint<32> Nsid; uint<128> D2_5; uint<128> D6_9;
 uint<32> LbaLo; uint<32> LbaHi; uint<32> D12; uint<96> D13_15;
};
WIRE_CMD_S wireCmd;
struct WIRE_HANDOFF_S {
 uint<32> Magic; uint<8> Version; uint<8> Kind; uint<16> Flow;
 uint<32> Epoch; uint<8> Reserved; uint<24> Psn;
 uint<32> AccessIp; uint<8> Reserved2; uint<24> AccessQp;
};
WIRE_HANDOFF_S wireHandoff;
