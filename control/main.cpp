#include "config.hpp"
#include "hal_oas_pub.h"
#include "ndi.h"
#include "ndi_mgr.h"
#include <cstring>
#include <iostream>
extern nlohmann::json iosConfig;
extern void TableConfig();extern void DebugProcess();
int main(int argc,char**argv){
 if(argc!=3||std::string(argv[1])!="--load"){std::cerr<<"Usage: ioswitch_on_board --load CONFIG.json (loads hardware)\n";return 2;}
 try{iosConfig=ReadConfig(argv[2]);}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 2;}
 bool initialized=false;
 try{
  std::string tables=std::string(RESOURCE_DIRECTORY)+"table_driver.json";
  if(HAL_OAS_LoadTableCfgFile(0,&tables[0],HAL_LOAD_TABLE_MODE_LOAD)!=0)throw std::runtime_error("load table layout failed");
  HalOasInitInfo info;std::memset(&info,0,sizeof(info));
  if(HAL_OAS_InitPhase1(&info)!=0)throw std::runtime_error("init phase1 failed");initialized=true;
  if(HAL_OAS_InitPhase2()!=0)throw std::runtime_error("init phase2 failed");
  if(HAL_OAS_LoadMicBinFile(0,(char*)BIN_FILE,HAL_LOAD_MICRO_MODE_LOAD)!=0)throw std::runtime_error("load microcode failed");
  std::string meta=std::string(RESOURCE_DIRECTORY)+"npc_table_info.json";
  if(NdiMgr::Instance()->Init(meta.c_str())!=NDI_OK)throw std::runtime_error("NDI init failed");
  TableConfig();HAL_OAS_BootOK(0);DebugProcess();
 }catch(const std::exception&e){std::cerr<<e.what()<<"\n";if(initialized)HAL_OAS_Destory();return 1;}
 return HAL_OAS_Destory()==0?0:1;
}
