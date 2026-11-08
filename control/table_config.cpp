#include "IOSwitch_tables.h"
#include "config.hpp"
nlohmann::json iosConfig;
template<class T> static void Put(typename T::Entry&e){T t;if(t.EntryAdd(e)!=0)throw std::runtime_error("table write failed: "+t.name());}
void TableConfig(){
 // Configuration must be installed on a fresh, quiescent image, before enabling flows.
 for(unsigned i=0;i<256;++i){Connectiontable::Entry e;e.key.classKey=i;e.data.Valid=0;Put<Connectiontable>(e);Configtable::Entry c;c.key.flowKey=i;c.data.Enabled=0;Put<Configtable>(c);Routetable::Entry rt;rt.key.routeKey=i;rt.data.Valid=0;Put<Routetable>(rt);Ownerroutetable::Entry ot;ot.key.ownerRouteKey=i;ot.data.Valid=0;Put<Ownerroutetable>(ot);}
 for(unsigned i=0;i<4096;++i){Addresstable::Entry a;a.key.blockKey=i;a.data.table_data=0;Put<Addresstable>(a);}
 for(const auto&r:iosConfig["routes"]){
  uint32_t ip=r["ip"];Routetable::Entry t;t.key.routeKey=ip&255;t.data.Ip=ip;t.data.Mac=r["mac"].get<uint64_t>();t.data.Channel=r["channel"].get<unsigned>();t.data.Sq=r["sq"].get<unsigned>();t.data.Valid=1;t.data.Reserved=0;Put<Routetable>(t);
  Ownerroutetable::Entry o;o.key.ownerRouteKey=ip&255;o.data.Ip=ip;o.data.Mac=r["mac"].get<uint64_t>();o.data.Channel=r["channel"].get<unsigned>();o.data.Sq=r["sq"].get<unsigned>();o.data.Valid=1;o.data.Reserved=0;Put<Ownerroutetable>(o);
 }
 for(const auto&b:iosConfig["blocks"]){Addresstable::Entry a;a.key.blockKey=b["bucket"].get<unsigned>();a.data.table_data=b["owner_ip"].get<uint32_t>();Put<Addresstable>(a);}
 for(const auto&f:iosConfig["flows"]){
  unsigned id=f["id"],aq=f["access_qp"],cq=f["client_qp"],base=(f["initial_psn"].get<unsigned>()-1)&0xffffff;uint32_t c=f["client_ip"],a=f["access_ip"];
  Statetable::Entry s;s.key.flowKey=id;s.data.Access=base;s.data.Owner=base;s.data.High=base;s.data.TemplateValid=0;s.data.SeenHi=0;s.data.SeenLo=0;s.data.Reserved=0;Put<Statetable>(s);
  for(unsigned k=0;k<64;++k){Pendingtable::Entry p;p.key.pendingKey=id*64+k;p.data.Valid=0;p.data.Psn=0;p.data.OwnerIp=0;p.data.Epoch=0;p.data.Reserved=0;Put<Pendingtable>(p);}
  Connectiontable::Entry ce;ce.key.classKey=(c^a^aq)&255;ce.data.Src=c;ce.data.Dst=a;ce.data.Qp=aq;ce.data.Flow=id;ce.data.Role=1;ce.data.Valid=1;Put<Connectiontable>(ce);
  ce.key.classKey=(c^a^cq)&255;ce.data.Src=a;ce.data.Dst=c;ce.data.Qp=cq;ce.data.Role=2;Put<Connectiontable>(ce);
  Configtable::Entry cfg;cfg.key.flowKey=id;cfg.data.ClientIp=c;cfg.data.AccessIp=a;cfg.data.ClientQp=cq;cfg.data.AccessQp=aq;cfg.data.Epoch=f["epoch"].get<uint32_t>();cfg.data.Reserved=0;cfg.data.Enabled=1;Put<Configtable>(cfg);
 }
}
