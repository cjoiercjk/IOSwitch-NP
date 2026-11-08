#include "config.hpp"
#include <iostream>
int main(int argc,char**argv){if(argc!=2)return 2;try{auto c=ReadConfig(argv[1]);std::cout<<"Valid: "<<c["flows"].size()<<" flow(s)\n";return 0;}catch(const std::exception&e){std::cerr<<e.what()<<"\n";return 1;}}
