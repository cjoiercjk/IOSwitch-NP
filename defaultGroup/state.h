#ifndef IOS_STATE_H
#define IOS_STATE_H
#include "lib/npc_arch.h"
#include "types_constant.h"
#include "headers.h"
struct CLASS_S { uint<32> Src; uint<32> Dst; uint<24> Qp; uint<8> Flow; uint<8> Role; uint<8> Valid; };
struct CFG_S {
 uint<32> ClientIp; uint<32> AccessIp; uint<24> ClientQp; uint<24> AccessQp;
 uint<32> Epoch; uint<8> Enabled; uint<8> Reserved;
};
struct ROUTE_S { uint<32> Ip; uint<48> Mac; uint<16> Channel; uint<16> Sq; uint<8> Valid; uint<8> Reserved; };
struct STATE_S {
 uint<24> Access; uint<24> Owner; uint<24> High; uint<8> TemplateValid;
 uint<32> SeenHi; uint<32> SeenLo; uint<16> Reserved;
};
struct PENDING_S { uint<24> Psn; uint<8> Valid; uint<32> OwnerIp; uint<32> Epoch; uint<32> Reserved; };
struct TEMPLATE_ETH_S { uint<48> Dst; uint<48> Src; uint<16> Type; };
struct TEMPLATE_NET_S { uint<8> VI; uint<8> Tos; uint<16> Len; uint<16> Id; uint<16> Frag; uint<8> Ttl; uint<8> Proto; uint<16> Sum; uint<32> Src; uint<32> Dst; };
struct TEMPLATE_S { uint<16> UdpSrc; uint<16> UdpDst; uint<16> UdpLen; uint<16> UdpSum; uint<8> BthOp; uint<8> BthFlags; uint<16> BthPkey; uint<8> BthR0; uint<24> BthQp; uint<8> BthR1; uint<24> BthPsn; uint<8> AethSyndrome; uint<24> AethMsn; uint<32> CrcValue; };
uint<8> classKey, flowKey, routeKey, ownerRouteKey;
uint<12> blockKey;
uint<14> pendingKey;
CLASS_S cls;
CFG_S cfg;
STATE_S st;
PENDING_S pending;
TEMPLATE_S ackTemplate;
TEMPLATE_NET_S ackNet;
TEMPLATE_ETH_S ackEth;
ROUTE_S route, ownerRoute;
uint<32> ownerIp;
uint<24> seq, delta, advance, safePsn, oldPsn;
uint<32> mask, scanLo, scanHi;
uint<8> kind;
STATUS_T lockStatus;
NPCLock flowLocks[IOS_FLOWS];
NPCCounter<uint<32>> debugCounter[DEBUG_CNTID_NUM];
table CLASS_T() {
 key={classKey:index;} CLASS_S _lookup(); actions={_lookup:no_action();} size=256;
}
table CFG_T() {
 key={flowKey:index;} CFG_S _lookup(); actions={_lookup:no_action();} size=256;
}
table ROUTE_T() {
 key={routeKey:index;} ROUTE_S _lookup(); actions={_lookup:no_action();} size=256;
}
table OWNER_ROUTE_T() {
 key={ownerRouteKey:index;} ROUTE_S _lookup(); actions={_lookup:no_action();} size=256;
}
table ADDR_T() {
 key={blockKey:index;} uint<32> _lookup(); actions={_lookup:no_action();} size=4096;
}
table STATE_T() {
 key={flowKey:index;} STATE_S _lookup(); void _write(STATE_S data);
 actions={_lookup:no_action();_write:no_action();} size=256;
}
table PENDING_T() {
 key={pendingKey:index;} PENDING_S _lookup(); void _write(PENDING_S data);
 actions={_lookup:no_action();_write:no_action();} size=16384;
}
table TEMPLATE_T() {
 key={flowKey:index;} TEMPLATE_S _lookup(); void _write(TEMPLATE_S data);
 actions={_lookup:no_action();_write:no_action();} size=256;
}
table TEMPLATE_NET_T() {
 key={flowKey:index;} TEMPLATE_NET_S _lookup(); void _write(TEMPLATE_NET_S data);
 actions={_lookup:no_action();_write:no_action();} size=256;
}
table TEMPLATE_ETH_T() {
 key={flowKey:index;} TEMPLATE_ETH_S _lookup(); void _write(TEMPLATE_ETH_S data);
 actions={_lookup:no_action();_write:no_action();} size=256;
}
TEMPLATE_ETH_T templateEthTable;
TEMPLATE_NET_T templateNetTable;
CLASS_T connectionTable;
CFG_T configTable;
ROUTE_T routeTable;
OWNER_ROUTE_T ownerRouteTable;
ADDR_T addressTable;
STATE_T stateTable;
PENDING_T pendingTable;
TEMPLATE_T templateTable;
#endif
