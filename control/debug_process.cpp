#include "IOSwitch_tables.h"
#include <iostream>
void DebugProcess(){
 std::cout<<"IOSwitch: R counters, Q quit\n";char c;
 while(std::cin>>c){if(c=='Q'||c=='q')break;if(c=='R'||c=='r'){
  static const char*names[]={"rx","drop","direct","handoff","ack","nak","lock_busy","out_of_window"};
  Debugcounter t;for(unsigned i=0;i<8;++i){Debugcounter::Entry e;e.key.counter_index=i;e.data.counter_data.valid=true;int rc=t.EntryGet(e);std::cout<<names[i]<<"="<<e.data.counter_data.value<<" rc="<<rc<<"\n";}
 }}
}
