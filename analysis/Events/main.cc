// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 6月  3 09:24:39 2017 (+0800)
// Last-Updated: 四 5月  9 13:53:17 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
// URL: http://wuhongyi.cn 

#include "sort-hil.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  // if(argc != 2)
  //   {
  //     std::cout<<"error(argc != 2)      "<<argv[0]<<"  [RunNnumber]"<<std::endl;
  //     return 1;
  //   }

  TString filename(argv[1]);

  sort *tran = new sort(filename);
  //tran->Process();
  tran->Processxc();
  // delete tran;
  
  return 0;
}

// 
// main.cc ends here
