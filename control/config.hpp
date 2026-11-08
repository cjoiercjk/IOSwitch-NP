#pragma once
#include "json.hpp"
#include <fstream>
#include <set>
#include <stdexcept>
inline nlohmann::json ReadConfig(const char*path){
 std::ifstream f(path);if(!f)throw std::runtime_error("cannot open configuration");
 nlohmann::json j;f>>j;
 std::set<unsigned> routeSlots,flowIds,classSlots,buckets;std::set<uint32_t> ips;
 for(const auto&r:j.at("routes")){
  auto ip=r.at("ip").get<uint32_t>();unsigned key=ip&255;
  if(!routeSlots.insert(key).second)throw std::runtime_error("route low-byte collision");ips.insert(ip);
  if(r.at("channel").get<unsigned>()>511||r.at("sq").get<unsigned>()>65535||r.at("mac").get<uint64_t>()>0xffffffffffffULL)throw std::runtime_error("invalid route fields");
 }
 for(const auto&f:j.at("flows")){
  unsigned id=f.at("id"),aq=f.at("access_qp"),cq=f.at("client_qp"),psn=f.at("initial_psn");
  uint32_t c=f.at("client_ip"),a=f.at("access_ip");
  if(id>255||aq>0xffffff||cq>0xffffff||psn>0xffffff||!flowIds.insert(id).second||!ips.count(c)||!ips.count(a))throw std::runtime_error("invalid flow");
  if(f.at("epoch").get<uint32_t>()==0)throw std::runtime_error("epoch must be nonzero and changed on reconnect");
  unsigned key=(a^c^aq)&255,rev=(a^c^cq)&255;
  if(!classSlots.insert(key).second||!classSlots.insert(rev).second)throw std::runtime_error("connection slot collision: choose different QPs or extend classifier");
 }
 for(const auto&b:j.at("blocks")){
  unsigned key=b.at("bucket");uint32_t ip=b.at("owner_ip");
  if(key>4095||!buckets.insert(key).second||!ips.count(ip))throw std::runtime_error("invalid owner mapping");
 }
 return j;
}
