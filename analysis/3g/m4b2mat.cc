// root2m4b.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 8月  8 16:05:35 2016 (+0800)
// Last-Updated: 六 8月 13 17:00:58 2022 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 15
// URL: http://wuhongyi.cn 

#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

#include <fstream>
#include <iostream>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int m4b2mat()
{

  ifstream readfile;//fstream
  readfile.open("finalmax.m4b",std::ios::binary);//ios::bin ios::app
  ofstream writefile;//fstream
  writefile.open("final.mat",std::ios::binary);//ios::bin ios::app

  int raw;
  ushort data;
  for (int i = 0; i < 4096; ++i)
    for (int j = 0; j < 4096; ++j)
      {
        readfile.read((char*)&raw,sizeof(int));
	data=(ushort)raw;
        writefile.write((char*)&data,sizeof(ushort));
      }
   
  writefile.close(); 
  readfile.close();
  return 0;
}
// 
// root2m4b.cc ends here
