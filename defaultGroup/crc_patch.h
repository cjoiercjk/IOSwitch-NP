void PatchAckCrc() {
 uint<24> change;
 uint<32> correction;
 change = oldPsn ^ wireBth.Psn;
 correction = 0;
 if (change[0:0] != 0) { correction[31:16] = correction[31:16] ^ 0xb029; correction[15:0] = correction[15:0] ^ 0x603d; }
 if (change[1:1] != 0) { correction[31:16] = correction[31:16] ^ 0x6053; correction[15:0] = correction[15:0] ^ 0xc07a; }
 if (change[2:2] != 0) { correction[31:16] = correction[31:16] ^ 0xc0a6; correction[15:0] = correction[15:0] ^ 0x80f5; }
 if (change[3:3] != 0) { correction[31:16] = correction[31:16] ^ 0xc14b; correction[15:0] = correction[15:0] ^ 0x7030; }
 if (change[4:4] != 0) { correction[31:16] = correction[31:16] ^ 0x8297; correction[15:0] = correction[15:0] ^ 0xe060; }
 if (change[5:5] != 0) { correction[31:16] = correction[31:16] ^ 0x042f; correction[15:0] = correction[15:0] ^ 0xc1c1; }
 if (change[6:6] != 0) { correction[31:16] = correction[31:16] ^ 0x4958; correction[15:0] = correction[15:0] ^ 0xf358; }
 if (change[7:7] != 0) { correction[31:16] = correction[31:16] ^ 0x92b0; correction[15:0] = correction[15:0] ^ 0xe6b1; }
 if (change[8:8] != 0) { correction[31:16] = correction[31:16] ^ 0xa5d3; correction[15:0] = correction[15:0] ^ 0x5ccb; }
 if (change[9:9] != 0) { correction[31:16] = correction[31:16] ^ 0x0ba1; correction[15:0] = correction[15:0] ^ 0xc84d; }
 if (change[10:10] != 0) { correction[31:16] = correction[31:16] ^ 0x1642; correction[15:0] = correction[15:0] ^ 0x919b; }
 if (change[11:11] != 0) { correction[31:16] = correction[31:16] ^ 0x6d82; correction[15:0] = correction[15:0] ^ 0x53ec; }
 if (change[12:12] != 0) { correction[31:16] = correction[31:16] ^ 0x9b02; correction[15:0] = correction[15:0] ^ 0xd603; }
 if (change[13:13] != 0) { correction[31:16] = correction[31:16] ^ 0x3605; correction[15:0] = correction[15:0] ^ 0xac07; }
 if (change[14:14] != 0) { correction[31:16] = correction[31:16] ^ 0x6c0a; correction[15:0] = correction[15:0] ^ 0x580f; }
 if (change[15:15] != 0) { correction[31:16] = correction[31:16] ^ 0xd814; correction[15:0] = correction[15:0] ^ 0xb01e; }
 if (change[16:16] != 0) { correction[31:16] = correction[31:16] ^ 0xb40b; correction[15:0] = correction[15:0] ^ 0x77a6; }
 if (change[17:17] != 0) { correction[31:16] = correction[31:16] ^ 0x2911; correction[15:0] = correction[15:0] ^ 0x9f97; }
 if (change[18:18] != 0) { correction[31:16] = correction[31:16] ^ 0x1324; correction[15:0] = correction[15:0] ^ 0x4ff4; }
 if (change[19:19] != 0) { correction[31:16] = correction[31:16] ^ 0x674e; correction[15:0] = correction[15:0] ^ 0xef33; }
 if (change[20:20] != 0) { correction[31:16] = correction[31:16] ^ 0xce9c; correction[15:0] = correction[15:0] ^ 0xde67; }
 if (change[21:21] != 0) { correction[31:16] = correction[31:16] ^ 0x9c39; correction[15:0] = correction[15:0] ^ 0xbdcf; }
 if (change[22:22] != 0) { correction[31:16] = correction[31:16] ^ 0x7975; correction[15:0] = correction[15:0] ^ 0x0b44; }
 if (change[23:23] != 0) { correction[31:16] = correction[31:16] ^ 0xf2ea; correction[15:0] = correction[15:0] ^ 0x1688; }
 wireCrc.Value = wireCrc.Value ^ correction;
}
