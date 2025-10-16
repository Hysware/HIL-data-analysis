// sort.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 6月  3 09:26:49 2017 (+0800)
// Last-Updated: 二 11月 16 11:03:33 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 54
// URL: http://wuhongyi.cn 

#ifndef _SORT_H_
#define _SORT_H_

#include "UserDefine.hh"
#include "cube.hh"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"
#include "TBenchmark.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TRandom.h"
#include "THnSparse.h"
#include "TSpectrum.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define MAXCHANNEL 256
#define MAXDETECTOR 100

class sort
{
public:
  sort(TString filename);
  virtual ~sort();

  void Process();
// xc
  void Processxc();
// xc  
private:
  void clearopt();
  void InitEvent();
  void ProcessEntry();

  // void EndEvent(TH2I *theh);
  // void EndEvent();
  void EndEvent(bool b); // 1 for prompt, 0 for random
private:
  TFile *file_in;
  TTree *t_in;
  Long64_t TotalEntry;

  // TBranch        *b_pileup;   //!
  // TBranch        *b_outofr;   //!
  // TBranch        *b_sid;   //!
  // TBranch        *b_ch;   //!
  // TBranch        *b_evte;   //!
  // TBranch        *b_ts;   //!
  // TBranch        *b_cfd;   //!
  // TBranch        *b_cfdft;   //!

  // Bool_t          pileup;
  // Bool_t          outofr;
  // Short_t         sid;
  // Short_t         ch;
  // UShort_t        evte;
  // Long64_t        ts;
  // Short_t         cfd;
  // Bool_t          cfdft;
  // Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxEAGLE = 1;


  // Declaration of leaf types
  // ulong should go to long, time at the beginning is negative. by EH
   ULong64_t       EventTS;
   Int_t           EAGLE_;
   UShort_t        EAGLE_fChannel[kMaxEAGLE];   //[EAGLE_]
   UShort_t        EAGLE_fBoard[kMaxEAGLE];   //[EAGLE_]
   UShort_t        EAGLE_fTimestamp[kMaxEAGLE];   //[EAGLE_]
   Bool_t          EAGLE_fPUR[kMaxEAGLE];   //[EAGLE_]
   Bool_t          EAGLE_fPLL[kMaxEAGLE];   //[EAGLE_]
   Float_t         EAGLE_fEnergy[kMaxEAGLE];   //[EAGLE_]
   Float_t         EAGLE_fCFD[kMaxEAGLE];   //[EAGLE_]

   // List of branches
   TBranch        *b_EventTimeStamp;   //!
   TBranch        *b_EAGLE_;   //!
   TBranch        *b_EAGLE_fChannel;   //!
   TBranch        *b_EAGLE_fBoard;   //!
   TBranch        *b_EAGLE_fTimestamp;   //!
   TBranch        *b_EAGLE_fPUR;   //!
   TBranch        *b_EAGLE_fPLL;   //!
   TBranch        *b_EAGLE_fEnergy;   //!
   TBranch        *b_EAGLE_fCFD;   //!

  

  TFile *file_out;
  TTree *t_out;
  Int_t nevt;

////add here
  FILE *tempfp;
////
///
  Short_t detflag[MAXCHANNEL];
  Short_t crystalflag[MAXCHANNEL];
  Double_t calia0[MAXCHANNEL];
  Double_t calia1[MAXCHANNEL];
  Double_t calia2[MAXCHANNEL];

  int nhitoneevent;
  Double_t DetEnergy[MAXDETECTOR][4];
  Long64_t DetTS[MAXDETECTOR][4];
  Short_t maxdetnum;
  int nhitoneeventaddback;
  Short_t NCrystal[MAXDETECTOR];
  Double_t DetAddbackE[MAXDETECTOR];
  Long64_t DetAddbackTS[MAXDETECTOR];
  Short_t DetFlag[MAXDETECTOR];
  Long64_t deltat;
  
  TH1I *haddback[MAXDETECTOR];
  TH1I *hdiff2crystalNeighbor[MAXDETECTOR];
  TH1I *hdiff2crystalDiagonal[MAXDETECTOR];

  TH1I *hdiff[MAXCHANNEL];//REF路与其它所有路的时间差
  TH1I *hspec[MAXCHANNEL];
  TH2I *tdiffte[MAXCHANNEL];
  TH2I *h;//两重及以上符合事件

  TH2I *h_o2;//只有两重符合事件
  TH2I *h_o23;//只有两重和三重符合事件
  TH2I *h_bg;
  // TH1D *spectrum;
  TH1I *counterrate2;
  TH1I *counterrate3;
  TH1I *counterrate4;
  
  double random;
  
  bool flag;
  Long64_t inittime;
  Long64_t tsnow;
  Long64_t lasteventtime;
  
  int RUNNUMBER;
  TBenchmark *benchmark;

  // =====
  // for all
  TH1I *hg1x;//add-back 能谱
  // TH1F *hg1xp;
  // TH1F *hg1xb;
  
  //for two-fold
  TH1I *hdiff2;
  // TH2I *hg2xy;
  // TH2I *hg2bxy;
  // TH1I *hg2x;
  // TH1I *hg2xp;
  // TH1I *hg2xb;  
  // TH2I *hg2xyb;
  // TH2I *hg2xyp;
  
#ifdef TESTMODE
  TH2I *hg2xy20;
  TH2I *hg2xy40;
  TH2I *hg2xy50;
#endif
  TH2I *hplanar;// 27
  TH2I *hsili;// 28
// xc
  TH2I *h_prompt;
  TH2I *h_random;
  TH2I *h_spectrum; // prompt-random
// xc
  TH2I *h79;//  0/1/8/9/16/17
  TH2I *h37;// 6/7/14/15/22
  TH2I *h101;//  35/36/33/29/31/32/24/25/27
  TH2I *h143;
  TH2I *h79_random;//  0/1/8/9/16/17
  TH2I *h37_random;// 2/3/10/11/18/  
  TH2I *h101_random;// 4/5/12/13/20/21
  TH2I *h143_random;// 26/28/34/37/38
  TH2I *h79_spectrum; // prompt-random
  TH2I *h37_spectrum; // prompt-random
  TH2I *h101_spectrum; // prompt-random
  TH2I *h143_spectrum; // prompt-random
  std::vector<TH2I*> prompt_vector;
  std::vector<TH2I*> random_vector;
  
  //for three-fold 
  // cube *threefold;
  
  TH1I *tdiff;
  
  TSpectrum *sa;
  
};

#endif /* _SORT_H_ */
// 
// sort.hh ends here
