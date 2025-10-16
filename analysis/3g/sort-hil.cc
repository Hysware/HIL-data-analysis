// sort.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 6月  3 09:27:02 2017 (+0800)
// Last-Updated: 二 12月 14 17:11:51 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 136
// URL: http://wuhongyi.cn 

#include "sort-hil.hh"

#include "TBranch.h"
#include "TMath.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "TSystem.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

sort::sort(TString filename)
{
  maxdetnum = -1;
  flag = false;
  nevt = 0;
  lasteventtime = -1;
  memset(detflag,0,MAXCHANNEL*sizeof(Short_t));
  memset(crystalflag,0,MAXCHANNEL*sizeof(Short_t));
  memset(calia0,0,MAXCHANNEL*sizeof(Double_t));
  memset(calia1,0,MAXCHANNEL*sizeof(Double_t));
  memset(calia2,0,MAXCHANNEL*sizeof(Double_t));
  
/*****************************************
  std::ifstream readtxt;
  readtxt.open("par1212szy.dat");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file."<<std::endl;
    }
*****************************************/
 // 找到 run_xxxx 的位置
  Ssiz_t pos = filename.Index("run_");
  if (pos != kNPOS) {
    TString runstr = filename(pos + 4, 4); // 取 run_ 后的4位数字
    int runnum = runstr.Atoi();            // 自动去除前导零，比如 0007 -> 7

    TString txtfilename = Form("./cali/%d.txt", runnum);
    std::ifstream readtxt(txtfilename.Data());
    if (!readtxt.is_open()) {
      std::cerr << "Error opening file: " << txtfilename << std::endl;
      return;
    }
   // cali
    std::cout << "Opened file: " << txtfilename << std::endl;

  std::string str_tmp;
  getline(readtxt,str_tmp);
  // std::cout<<str_tmp<<std::endl;
  Short_t sid_tmp, ch_tmp;
  Short_t det_tmp, crystal_tmp;
  Double_t a0_tmp, a1_tmp, a2_tmp;
  while(!readtxt.eof())
    {
      readtxt>>sid_tmp>>ch_tmp>>det_tmp>>crystal_tmp>>a0_tmp>>a1_tmp>>a2_tmp;
      // std::cout << sid_tmp << ch_tmp << det_tmp << crystal_tmp << a0_tmp << a1_tmp <<a2_tmp << std::endl;
      if(readtxt.eof()) break;
      Short_t flagchtmp = sid_tmp *16 +ch_tmp;
      // std::cout << flagchtmp << std::endl;
      // Short_t flagchtmp = ((sid_tmp)<<4)+ch_tmp;
      detflag[flagchtmp] = det_tmp;
      crystalflag[flagchtmp] = crystal_tmp;
      calia0[flagchtmp] = a0_tmp;
      calia1[flagchtmp] = a1_tmp;
      calia2[flagchtmp] = a2_tmp;

      if(det_tmp > maxdetnum) maxdetnum = det_tmp;
    }
    // std::cout << 1 << std::endl;
  readtxt.close();  

  } else {
    std::cerr << "run_ not found in filename" << std::endl;
  }

  h = new TH2I("mat_all","g-g matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h_prompt = new TH2I("mat_all_prompt","g-g matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h_random = new TH2I("mat_all_random","g-g matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h_o2 = new TH2I("mat_o2","g-g matrix only 2 g",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h_o23 = new TH2I("mat_o23","g-g matrix only 2/3 g",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h_bg = new TH2I("mat_bg","g-g background matrix",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold

  hplanar = new TH2I("mat_planar","planar-g matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV

  hsili = new TH2I("mat_sili","sili-g matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV

  h30 = new TH2I("mat_30","g-g 30 matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h90 = new TH2I("mat_90","g-g 90 matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h150 = new TH2I("mat_150","g-g 150 matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV
  h30150 = new TH2I("mat_30150","g-g 30-150 matrix all event",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//keV

      
  
  hg1x = new TH1I("hg1x","inclusive gamma spectrum",4096,0,MATRIX_ENERGY_MAX);
  // hg1xp = new TH1F("hg1xp","net peaks of inclusive gamma spectrum",4096,0,MATRIX_ENERGY_MAX);

  hdiff2 = new TH1I("Tdiff2","",100,-50,50);
  // TTree* tr;
/*
  tr = new TTree("three", "three_fold_energy");


  tr->Branch("energy1", &energy1);
  tr->Branch("energy2", &energy2);
  tr->Branch("energy3", &energy3);
*/
  // hg2xy = new TH2F("hg2xy","g-g matrix",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold
  // hg2bxy = new TH2F("hg2bxy","g-g background matrix",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold
  // hg2x = new TH1F("hg2x","total projection spectrum for hg2xy",4096,0,MATRIX_ENERGY_MAX);
  // hg2xp = new TH1F("hg2xp","net peaks of total projection spectrum of hg2xy",4096,0,MATRIX_ENERGY_MAX);
  // hg2xyb = new TH2F("hg2xyb","background gg-matrix",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX); 
  // hg2xyp = new TH2F("hg2xyp","background subtracted gg-matrix",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);

#ifdef TESTMODE
  hg2xy20 = new TH2I("hg2xy20","g-g matrix20",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold
  hg2xy40 = new TH2I("hg2xy40","g-g matrix40",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold
  hg2xy50 = new TH2I("hg2xy50","g-g matrix50",4096,0,MATRIX_ENERGY_MAX,4096,0,MATRIX_ENERGY_MAX);//for two-fold
#endif
  
#ifdef CUBEMATRIX
  threefold = new cube(0,3072);
#endif
  
  sa = new TSpectrum(200);
  
  counterrate2 = new TH1I("coin2rate","",7200,0,7200);
  counterrate3 = new TH1I("coin3rate","",7200,0,7200);
  counterrate4 = new TH1I("coin4rate","",7200,0,7200);

  tdiff = new TH1I("tdiff2event","",5000,0,5000);//us
  
  // for (int i = 0; i <= maxdetnum; ++i)
  //   {
  //     haddback[i] = new TH1I(TString::Format("Eaddback%02d",i).Data(),"",4096,0,2048);
  //     hdiff2crystalDiagonal[i] = new TH1I(TString::Format("Tdiff2crystalDiagonal_%02d",i).Data(),"",100,-50,50);
  //     hdiff2crystalNeighbor[i] = new TH1I(TString::Format("Tdiff2crystalNeighbor_%02d",i).Data(),"",100,-50,50);
  //   }


  for (int i = 0; i < MAXCHANNEL; ++i)
    {
      int j = (i&0xF0)>>4;
      int k = i&0x0F;
      hdiff[i] = new TH1I(TString::Format("Tdiff%02d_%02d",j,k).Data(),"",200,-100,100);
      hspec[i] = new TH1I(TString::Format("E%02d_%02d",j,k).Data(),"",4096,0,2048);
      //hspec2[i] = new TH1I(TString::Format("e%02d_%02d",j,k).Data(),"",65536,0,66536);
      // tdiffte[i] = new TH2I(TString::Format("ET%02d_%02d",j,k).Data(),"",100,-50,50,2048,0,2048);
    }

  benchmark = new TBenchmark;

  // file_in = new TFile(TString::Format("%s%s_R%04d_sort.root",RAWFILEPATH,RAWFILENAME,runnumber).Data(),"READ");
  // file_in = new TFile(TString::Format("%s%s_C1_%04d.root",RAWFILEPATH,RAWFILENAME,runnumber).Data(),"READ");
  file_in = new TFile(filename.Data(),"READ");
  if(!file_in->IsOpen())
    {
      std::cout<<"Can't open raw root file"<<std::endl;
      exit(1);
    }
  // t_in = (TTree*)file_in->Get("tree");
  // t_in->SetBranchAddress("pileup", &pileup, &b_pileup);
  // t_in->SetBranchAddress("outofr", &outofr, &b_outofr);
  // t_in->SetBranchAddress("sid", &sid, &b_sid);
  // t_in->SetBranchAddress("ch", &ch, &b_ch);
  // t_in->SetBranchAddress("evte", &evte, &b_evte);//道址
  // t_in->SetBranchAddress("ts", &ts, &b_ts);//
  // t_in->SetBranchAddress("cfd", &cfd, &b_cfd);
  // t_in->SetBranchAddress("cfdft", &cfdft, &b_cfdft); 
  gSystem->Load("libCaenDPP_PHA.so");
  t_in = (TTree*)file_in->Get("NeedleTree");
  t_in->SetBranchAddress("EventTS", &EventTS);
  b_EventTimeStamp=t_in->GetBranch("EventTS");
  b_EventTimeStamp->SetAutoDelete(true);
//
//no need for eagle. EH
//
  t_in->SetBranchAddress("EAGLE.fChannel", EAGLE_fChannel);
  b_EAGLE_fChannel=t_in->GetBranch("EAGLE.fChannel");
  t_in->SetBranchAddress("EAGLE.fBoard", EAGLE_fBoard);
  b_EAGLE_fBoard=t_in->GetBranch("EAGLE.fBoard");
  t_in->SetBranchAddress("EAGLE.fTimestamp", EAGLE_fTimestamp);
  b_EAGLE_fTimestamp=t_in->GetBranch("EAGLE.fTimestamp");
  // t_in->SetBranchAddress("EAGLE.fPUR", EAGLE_fPUR);
  // b_EAGLE_fPUR=t_in->GetBranch("EAGLE.fPUR");
  // t_in->SetBranchAddress("EAGLE.fPLL", EAGLE_fPLL);
  // b_EAGLE_fPLL=t_in->GetBranch("EAGLE.fPLL");
  t_in->SetBranchAddress("EAGLE.fEnergy", EAGLE_fEnergy);
  b_EAGLE_fEnergy=t_in->GetBranch("EAGLE.fEnergy");
  // t_in->SetBranchAddress("EAGLE.fCFD", EAGLE_fCFD);
  // b_EAGLE_fCFD=t_in->GetBranch("EAGLE.fCFD");

  TotalEntry = t_in->GetEntries();
  // t_in->Print();
  // std::cout<<"TotalEntry: "<<TotalEntry<<std::endl;

  // file_out = new TFile(TString::Format("%s%s_R%04d_W%d_part.root",ROOTFILEPATH,RAWFILENAME,runnumber,EVENTTIMEWINDOWSWIDTH).Data(),"RECREATE");
  filename2 = gSystem->BaseName(filename);

   Ssiz_t dotIndex = filename2.Last('.');
    if (dotIndex != kNPOS) {
        filename2.Remove(dotIndex);
    }
  
  // file_out = new TFile(TString::Format("../../rootfile/%s_mat_clean.root",filename2.Data()),"RECREATE");
  file_out = new TFile(TString::Format("./%s_mat_three.root",filename2.Data()),"RECREATE");
  // t_out = new TTree("t","PKU XIA Pixie-16 Event Data");
  // t_out->Branch("nevt",&nevt,"nevt/I");

  /////add here
  // char tempname[200]={0};
  // sprintf(tempname,"%s%d.m16",ROOTFILEPATH,runnumber); 
  // if((tempfp=fopen(tempname,"ab")) == NULL)
	//   std::cout<<"Can't open file m16"<<std::endl;
 ///
  // t_out->Print();
}

sort::~sort()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void sort::clearopt()
{
  memset(NCrystal,0,sizeof(NCrystal));
  memset(DetEnergy,0,sizeof(DetEnergy));
  memset(DetTS,0,sizeof(DetTS));

  nhitoneevent = 0;
  nhitoneeventaddback = 0;
}


//
//
//
void sort::Processxc()
{
  // benchmark->Start("event");//计时开始
  Long64_t entry;
    // for (Long64_t entry = 0; entry < TotalEntry; ++entry)
  std::cout <<"Total entry is "<<TotalEntry<<std::endl;
  

  fout = new TFile(TString::Format("./%s_three.root",filename2.Data()),"RECREATE");
  // tr->SetDirectory(fout);
  tr = new TTree("three", "three_fold_energy");
  tr->Branch("energy1", &energy1, "energy1/D");
  tr->Branch("energy2", &energy2, "energy2/D");
  tr->Branch("energy3", &energy3, "energy3/D");
  for(entry = 10; entry < TotalEntry; ++entry)
  {

      file_in->cd();
      if(entry % 100000 ==0)
        std::cout<<"====>Entry is "<<entry<<"\r";

      t_in->GetEntry(entry);
      //std::cout << " time is " << EventTS << std::endl;
      //std::cout << " channel is " << EAGLE_fChannel[0] << std::endl; 
      //std::cout << " board is " << EAGLE_fBoard[0] << std::endl; 
      //std::cout << " energy is " << EAGLE_fEnergy[0] << std::endl;      
      //-----------------------------------------------------------------------------------------------------------
      if(flag)
      {
        tsnow = EventTS;
        // std::cout << "!! " << tsnow << std::endl;
    

        if(TMath::Abs(tsnow-inittime) <= Long64_t(EVENTTIMEWINDOWSWIDTH))
        {
          ProcessEntry();
            
        }
        else
        {
            EndEvent(h_prompt);
            InitEvent();
        }
      }
      else
      {//event header
        InitEvent();
        flag = true;
      }
  }

  std::cout<<std::endl;

  //
  for(entry = 10; entry < TotalEntry; ++entry)
  {

      file_in->cd();
      if(entry % 100000 ==0)
        std::cout<<"====>Entry is "<<entry<<"\r";

      t_in->GetEntry(entry);
      //std::cout << " time is " << EventTS << std::endl;
      //std::cout << " channel is " << EAGLE_fChannel[0] << std::endl; 
      //std::cout << " board is " << EAGLE_fBoard[0] << std::endl; 
      //std::cout << " energy is " << EAGLE_fEnergy[0] << std::endl;      
      //-----------------------------------------------------------------------------------------------------------
      if(flag)
      {
        tsnow = EventTS;
        // std::cout << "!! " << tsnow << std::endl;
    

        if(TMath::Abs(tsnow-inittime) >= Long64_t(EVENTTIMEWINDOWSWIDTH) && TMath::Abs(tsnow-inittime) <= Long64_t(2*EVENTTIMEWINDOWSWIDTH))
        {
          ProcessEntry();
            
        }
        else
        {
            EndEvent(h_random);
            InitEvent();
        }
      }
      else
      {//event header
        InitEvent();
        flag = true;
      }
  }
  file_in->cd();
  file_in->Close();

#ifdef CUBEMATRIX
  threefold->Save(RUNNUMBER);
#endif
  
  // ----------  
  
  ////////////////////////////////////////////////////////////////////////////
  //h->Write();

  // int count;
  // for (int i=1;i<=16384;i++)
	//   for(int j=1;j<=16384;j++){
	// 	  count = int(h->GetBinContent(i,j));
	// 	  fwrite(&count,sizeof(int),1,tempfp);
	//   }
  // fclose(tempfp);

  ///////////////////////////////////////////////////////////////////////

  file_out->cd();

  for (int i = 0; i < MAXCHANNEL; ++i)
  {
    if(hspec[i]->GetEntries() > 0)
	  {
	  hspec[i]->Write();
	  // hdiff[i]->Write();
	  // tdiffte[i]->Write();
	  }
  }

  h_prompt->Add(h_random,-1);
  h_prompt->Write();
  h_o2->Write();
  h_o23->Write();
  h_bg->Write();
  // hplanar->Write();
  // hsili->Write();
  h30->Write();
  h150->Write();
  h90->Write();
  h30150->Write();
  hg1x->Write();
   // hg1xb->Write();
   
   // hg2xy->Write();
   // hg2bxy->Write();
   // hg2xyb->Write();
   // hg2xyp->Write();
   // hg2x->Write();
   // hg2xb->Write();
   // hg2xp->Write();
   
   hdiff2->Write();
#ifdef TESTMODE
   hg2xy20->Write();
   hg2xy40->Write();
   hg2xy50->Write();
#endif   

   tdiff->Write();
   
  file_out->Close();
  fout->cd();
  tr->Write();
  fout->Close(); 
  //benchmark->Show("event");//计时结束并输出时间
}

void sort::Process()
{
  // benchmark->Start("event");//计时开始
  Long64_t entry;
    // for (Long64_t entry = 0; entry < TotalEntry; ++entry)
  std::cout <<"Total entry is "<<TotalEntry<<std::endl;
  for(entry = 10; entry < TotalEntry; ++entry)
  {

      file_in->cd();
      if(entry % 100000 ==0)
        std::cout<<"====>Entry is "<<entry<<"\r";

      t_in->GetEntry(entry);
      //std::cout << " time is " << EventTS << std::endl;
      //std::cout << " channel is " << EAGLE_fChannel[0] << std::endl; 
      //std::cout << " board is " << EAGLE_fBoard[0] << std::endl; 
      //std::cout << " energy is " << EAGLE_fEnergy[0] << std::endl;      
      //-----------------------------------------------------------------------------------------------------------
      if(flag)
      {
        tsnow = EventTS;
        // std::cout << "!! " << tsnow << std::endl;
    

        if(TMath::Abs(tsnow-inittime) <= Long64_t(EVENTTIMEWINDOWSWIDTH))
        {
          ProcessEntry();
            
        }
        else
        {
            EndEvent(h);
            InitEvent();
        }
      }
      else
      {//event header
        InitEvent();
        flag = true;
      }
  }

  std::cout<<std::endl;

  file_in->cd();
  file_in->Close();

#ifdef CUBEMATRIX
  threefold->Save(RUNNUMBER);
#endif
  
  // ----------  
  
  ////////////////////////////////////////////////////////////////////////////
  //h->Write();

  // int count;
  // for (int i=1;i<=16384;i++)
	//   for(int j=1;j<=16384;j++){
	// 	  count = int(h->GetBinContent(i,j));
	// 	  fwrite(&count,sizeof(int),1,tempfp);
	//   }
  // fclose(tempfp);

  ///////////////////////////////////////////////////////////////////////

  file_out->cd();

  for (int i = 0; i < MAXCHANNEL; ++i)
  {
    if(hspec[i]->GetEntries() > 0)
	  {
	  hspec[i]->Write();
	  // hdiff[i]->Write();
	  // tdiffte[i]->Write();
	  }
  }

  h->Write();
  
  h_o2->Write();
  h_o23->Write();
  h_bg->Write();
  // hplanar->Write();
  // hsili->Write();
  h30->Write();
  h150->Write();
  h90->Write();
  h30150->Write();
  hg1x->Write();
   // hg1xb->Write();
   
   // hg2xy->Write();
   // hg2bxy->Write();
   // hg2xyb->Write();
   // hg2xyp->Write();
   // hg2x->Write();
   // hg2xb->Write();
   // hg2xp->Write();
   
   hdiff2->Write();
#ifdef TESTMODE
   hg2xy20->Write();
   hg2xy40->Write();
   hg2xy50->Write();
#endif   

   tdiff->Write();
   
  file_out->Close();

  
  //benchmark->Show("event");//计时结束并输出时间
}

void sort::InitEvent()
{
  if(lasteventtime > 0)
    {
      tdiff->Fill((inittime-lasteventtime)/100);
    }
  lasteventtime = inittime;
  clearopt();
  inittime = EventTS;
  //std::cout << " <<< >>>>" << inittime << std::endl;

  ProcessEntry();
}

void sort::ProcessEntry()
{
  //sid   ch
  Short_t flagchtmp = ((EAGLE_fBoard[0]) *16)+(EAGLE_fChannel[0]);
  //std::cout << "board " << EAGLE_fBoard[0]<< " ch" << EAGLE_fChannel[0] << std::endl;
  
  random = gRandom->Uniform();
  double tmp = calia0[flagchtmp]+calia1[flagchtmp]*(random+(EAGLE_fEnergy[0]))+calia2[flagchtmp]*(random+(EAGLE_fEnergy[0]))*(random+(EAGLE_fEnergy[0]));
  //std::cout << "222222222222222222222222" << tmp << " " << calia0[flagchtmp] << calia1[flagchtmp] << *EAGLE_fEnergy << std::endl;
  if(tmp >= THRE_LOW && tmp <= THRE_HIGH)
    {
      hspec[flagchtmp]->Fill(tmp);
      DetEnergy[detflag[flagchtmp]][crystalflag[flagchtmp]] = tmp;
      DetTS[detflag[flagchtmp]][crystalflag[flagchtmp]] = EventTS;
 
      //std::cout << "222222222222222222222222" << tmp << " " << calia0[flagchtmp] << calia1[flagchtmp] << *EAGLE_fEnergy << std::endl;
      nhitoneevent++;
    }
    //  std::cout << "222222222222222222222222" << tmp << " " << calia0[flagchtmp] << calia1[flagchtmp] << *EAGLE_fEnergy << std::endl;
}

void sort::EndEvent(TH2I *theh)
{
  if(nhitoneevent >1)
  {
    Short_t refflagchtmp = (REFSID*16)+REFCH;

// add EH anti compton
    for(int i=0;i<33;i++){
      if(i%2==0) continue; //skip Ge
      if(DetEnergy[i][0]==0) continue; // skip no data on BGO
      DetEnergy[i][0]=0;
      DetEnergy[i-1][0]=0;
      //if BGO has data, reset Ge to 0
    }
    // gg conincidence for matrix
    for(int i=0;i<33;i++){
      if((DetEnergy[i][0]) == 0) continue;
      for(int j=0;j<33;j++){
        if(i==j) continue;
        if(DetEnergy[i][0]>0&&DetEnergy[j][0]>0){
          theh->Fill(DetEnergy[i][0],DetEnergy[j][0]);
          if(DetEnergy[i][0]==0)
            std::cout<<"i 0"<<std::endl;
          if(DetEnergy[j][0]==0)
            std::cout<<"j 0"<<std::endl;
 
        }
      }
    }
    // ggg coincidence for cube, add HY
    for(int i=0;i<33;i++){
      if((DetEnergy[i][0]) == 0) continue;
      for(int j=i+1;j<33;j++){
        if(i==j) continue;
        for(int k=j+1;k<33;k++){
        if(i==k|| j==k)continue;
        if(DetEnergy[i][0]>0&&DetEnergy[j][0]>0&&DetEnergy[k][0]>0){
          energy1 = DetEnergy[i][0];
          energy2 = DetEnergy[j][0];
          energy3 = DetEnergy[k][0];
          tr->Fill();
        }
      }
     }
    }
    
// end add EH

    if(DetEnergy[detflag[refflagchtmp]][crystalflag[refflagchtmp]] > 100)
	  {
      for (int i = 0; i < MAXCHANNEL; ++i)
      {
        if(DetEnergy[detflag[i]][crystalflag[i]] > 100)
        {
          hdiff[i]->Fill(DetTS[detflag[refflagchtmp]][crystalflag[refflagchtmp]]-DetTS[detflag[i]][crystalflag[i]]);
          //tdiffte[i]->Fill(DetTS[detflag[refflagchtmp]][crystalflag[refflagchtmp]]-DetTS[detflag[i]][crystalflag[i]],int(DetEnergy[detflag[i]][crystalflag[i]]));
        }
      }
	  }

      
    for (int j = 0; j <= maxdetnum; ++j)
    {
      for (int k = 0; k < 4; ++k)
        if(DetEnergy[j][k] > 0) NCrystal[j]++;

      if(NCrystal[j] > 0)
      {
        bool tempfalgaddback;
          
        if(NCrystal[j] == 1)
        {
          tempfalgaddback = false;
          if(DetEnergy[j][0] > 0)
          {
            DetAddbackE[nhitoneeventaddback] = DetEnergy[j][0];
            DetAddbackTS[nhitoneeventaddback] = DetTS[j][0];
            
            tempfalgaddback = true;
          }
          else if(DetEnergy[j][1] > 0)
          {
            DetAddbackE[nhitoneeventaddback] = DetEnergy[j][1];
            DetAddbackTS[nhitoneeventaddback] = DetTS[j][1];

            tempfalgaddback = true;
          }
          else if(DetEnergy[j][2] > 0)
          {
            DetAddbackE[nhitoneeventaddback] = DetEnergy[j][2];
            DetAddbackTS[nhitoneeventaddback] = DetTS[j][2];

            tempfalgaddback = true;
          }
          else if(DetEnergy[j][3] > 0)
          {
            DetAddbackE[nhitoneeventaddback] = DetEnergy[j][3];
            DetAddbackTS[nhitoneeventaddback] = DetTS[j][3];

            tempfalgaddback = true;
          }
          DetFlag[nhitoneeventaddback] = j;
          if(tempfalgaddback && DetAddbackE[nhitoneeventaddback]>=THRE_MULTIHIT)
          {
            //haddback[j]->Fill(DetAddbackE[nhitoneeventaddback]);
            nhitoneeventaddback++;
          }
        }
        else if(NCrystal[j] == 2)
        {
        tempfalgaddback = false;
        if((DetEnergy[j][0] > 0 && DetEnergy[j][3] > 0) || (DetEnergy[j][1] > 0 && DetEnergy[j][2] > 0))
        {
          if(DetEnergy[j][0] > 0 && DetEnergy[j][3] > 0)
        hdiff2crystalDiagonal[j]->Fill(DetTS[j][0]-DetTS[j][3]);
          if(DetEnergy[j][1] > 0 && DetEnergy[j][2] > 0)
        hdiff2crystalDiagonal[j]->Fill(DetTS[j][1]-DetTS[j][2]);
        }
        else
        {
          if(DetEnergy[j][0] > 0 && DetEnergy[j][1] > 0)
          {
          hdiff2crystalNeighbor[j]->Fill(DetTS[j][0]-DetTS[j][1]);
          if(TMath::Abs(DetTS[j][0]-DetTS[j][1])<=ADDBACKTIMEDIFF)
            {
              DetAddbackE[nhitoneeventaddback] = DetEnergy[j][0]+DetEnergy[j][1];
              DetAddbackTS[nhitoneeventaddback] = DetTS[j][0]<DetTS[j][1] ? DetTS[j][0] :DetTS[j][1];
              tempfalgaddback = true;
            }
          
          }
          else if(DetEnergy[j][0] > 0 && DetEnergy[j][2] > 0)
          {
          hdiff2crystalNeighbor[j]->Fill(DetTS[j][0]-DetTS[j][2]);
          if(TMath::Abs(DetTS[j][0]-DetTS[j][2])<=ADDBACKTIMEDIFF)
            {
              DetAddbackE[nhitoneeventaddback] = DetEnergy[j][0]+DetEnergy[j][2];
              DetAddbackTS[nhitoneeventaddback] = DetTS[j][0]<DetTS[j][2] ? DetTS[j][0] :DetTS[j][2];
              tempfalgaddback = true;
            }
          }
          else if(DetEnergy[j][1] > 0 && DetEnergy[j][3] > 0)
          {
            hdiff2crystalNeighbor[j]->Fill(DetTS[j][1]-DetTS[j][3]);
            if(TMath::Abs(DetTS[j][1]-DetTS[j][3])<=ADDBACKTIMEDIFF)
            {
              DetAddbackE[nhitoneeventaddback] = DetEnergy[j][1]+DetEnergy[j][3];
              DetAddbackTS[nhitoneeventaddback] = DetTS[j][1]<DetTS[j][3] ? DetTS[j][1] :DetTS[j][3];
              tempfalgaddback = true;
            }
          }
          else if(DetEnergy[j][2] > 0 && DetEnergy[j][3] > 0)
          {
            hdiff2crystalNeighbor[j]->Fill(DetTS[j][2]-DetTS[j][3]);
            if(TMath::Abs(DetTS[j][2]-DetTS[j][3])<=ADDBACKTIMEDIFF)
            {
              DetAddbackE[nhitoneeventaddback] = DetEnergy[j][2]+DetEnergy[j][3];
              DetAddbackTS[nhitoneeventaddback] = DetTS[j][2]<DetTS[j][3] ? DetTS[j][2] :DetTS[j][3];
              tempfalgaddback = true;
            }
          }
          DetFlag[nhitoneeventaddback] = j;
          if(tempfalgaddback && DetAddbackE[nhitoneeventaddback]>=THRE_MULTIHIT)
          {
          //haddback[j]->Fill(DetAddbackE[nhitoneeventaddback]);
            nhitoneeventaddback++;
          }
        }
      }
          
      }

      
    }


  }

  //std::cout<<"after hit >1"<<std::endl;
  //for inclusive
  if(nhitoneeventaddback > 0)
  {
    for(int i = 0; i < nhitoneeventaddback; i++)
    hg1x->Fill(DetAddbackE[i]);	
  }

  

  // ===== matrix =====
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //Be Careful!!!!!!!

  //for two-fold
  if(nhitoneeventaddback > 1)
  {
    nevt++;
      // counterrate2->Fill(DetAddbackTS[0]*10/1000000000.0);
      // if(nhitoneeventaddback > 2) counterrate3->Fill(DetAddbackTS[0]*10/1000000000.0);
      // if(nhitoneeventaddback > 3) counterrate4->Fill(DetAddbackTS[0]*10/1000000000.0);


      
    for(int i = 0; i < nhitoneeventaddback; i++) 
	    for(int j = 0; j < nhitoneeventaddback; j++)
	    {
        if(i==j) continue;
        deltat = DetAddbackTS[i]-DetAddbackTS[j];
        hdiff2->Fill(deltat);

        #ifdef TESTMODE
        hg2xy50->Fill(DetAddbackE[i],DetAddbackE[j]);
        if(TMath::Abs(deltat)>=23 && TMath::Abs(deltat) <=43) hg2xy20->Fill(DetAddbackE[i],DetAddbackE[j]);
        if(TMath::Abs(deltat)>=40) hg2xy40->Fill(DetAddbackE[i],DetAddbackE[j]);
        #endif

	      if(TMath::Abs(deltat)<=COINTIMEWINDOWSWIDTH)
	      {
          //h->Fill(DetAddbackE[i],DetAddbackE[j]);
          // comment by EH
          if(nhitoneeventaddback == 2) h_o2->Fill(DetAddbackE[i],DetAddbackE[j]);
          
          if(nhitoneeventaddback < 4) h_o23->Fill(DetAddbackE[i],DetAddbackE[j]);		
	      }

	    
        bool bij = TMath::Abs(deltat) > COINTIMEWINDOWSWIDTH && TMath::Abs(deltat) <= 2*COINTIMEWINDOWSWIDTH; //prompt coincidence time window
        if(bij)
        {
          h_bg->Fill(DetAddbackE[i],DetAddbackE[j]);
        }
	    }
  }  

  //for three-fold
  #ifdef CUBEMATRIX
  if(nhitoneeventaddback > 2)
    {
      for(int i = 0; i < nhitoneeventaddback; i++) 
	for(int j = 0; j < nhitoneeventaddback; j++) 
	  for(int k = 0; k < nhitoneeventaddback; k++)
	    {
	      bool bij = TMath::Abs(DetAddbackTS[i]-DetAddbackTS[j]) > COINTIMEWINDOWSWIDTH;
	      bool bik = TMath::Abs(DetAddbackTS[i]-DetAddbackTS[k]) > COINTIMEWINDOWSWIDTH;
	      bool bjk = TMath::Abs(DetAddbackTS[j]-DetAddbackTS[k]) > COINTIMEWINDOWSWIDTH;
	      if(bij || bik || bjk) continue;
	      if(i==j || i==k || j==k) continue;

	      threefold->Fill(DetAddbackE[i],DetAddbackE[j],DetAddbackE[k]);
	    }
    }
#endif

}
	       
// 
// sort.cc ends here
