// cube.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 10月 13 14:23:25 2019 (+0800)
// Last-Updated: 二 4月 21 21:57:50 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 22
// URL: http://wuhongyi.cn 

#include "cube.hh"
#include <iostream>

cube::cube(int slave, int energy)
{
  
  if(energy==2048)
    {
      MODE = 1;
    }
  else if(energy==3072)
    {
      MODE = 2;
    }
  else
    {
      MODE = 0;
      std::cout<<"cube init pars error ！！！"<<std::endl;
    }

  
  BINNUMBER = energy*2;
  MAXENERGY = energy;
  SLAVE = slave;
  
  if(MODE > 0)
    {
      if(SLAVE == 0)
	{
	  hg3x = new TH1I("cube_hg3x","total projection spectrum for hg3xyz",BINNUMBER,0.0,MAXENERGY);
	  hg3xy = new TH2I("cube_hg3xy","x-y projection of hg3xyz",BINNUMBER,0,MAXENERGY,BINNUMBER,0.0,MAXENERGY);
	}


      hg3xyz = new TH2C *[2048];
      for (int i = 0; i < 2048; ++i)
	{
	  hg3xyz[i] = new TH2C(TString::Format("cube_%04d",i+SLAVE*2048).Data(),"",BINNUMBER,0.0,MAXENERGY,BINNUMBER,0.0,MAXENERGY);
	}

    }
}

cube::~cube()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cube::Fill(double ex,double ey,double ez)
{
  if(MODE > 0 && ex<MAXENERGY && ey<MAXENERGY && ez<MAXENERGY)
    {
      if(SLAVE == 0)
	{
	  hg3x->Fill(ex);
	  hg3xy->Fill(ex,ey);
	}
      
      // if(hg3xyz[int(ez/MAXENERGY*BINNUMBER)]->GetBinContent(hg3xyz[int(ez/MAXENERGY*BINNUMBER)]->FindBin(ex,ey)) > 125)
      // 	std::cout<<"Bin Content will FULL, bin number" << int(ez/MAXENERGY*BINNUMBER) <<"energy: "<<ex<<" , "<<ey<<std::endl;

      int binnumber = int((ez-SLAVE*1024)*2);
      if(binnumber >=0 && binnumber< 2048)
	{
	  if(hg3xyz[binnumber]->GetBinContent(hg3xyz[binnumber]->FindBin(ex,ey)) >= 127)
	    std::cout<<"Bin Content will FULL, bin number" << int(ez*2) <<"energy: "<<ex<<" , "<<ey<<std::endl;
	  hg3xyz[binnumber]->Fill(ex,ey);

	}
    }
}


void cube::Save(int run)
{
  if(MODE > 0)
    {
      TFile *cubesave;

      if(SLAVE == 0)
	{
	  cubesave = new TFile(TString::Format("cube/cube_R%04d.root",run).Data(),"RECREATE");
	  if(!cubesave->IsOpen())
	    {
	      std::cout<<"Can't open root file"<<std::endl;
	    }
	  hg3x->Write();
	  hg3xy->Write();
	  cubesave->Close();
	}

      for (int i = 0; i < 2048; ++i)
	{
	  cubesave = new TFile(TString::Format("cube/cube_%04d_R%04d.root",i+SLAVE*2048,run).Data(),"RECREATE");
	  if(!cubesave->IsOpen())
	    {
	      std::cout<<"Can't open root file"<<std::endl;
	    }
	  hg3xyz[i]->Write();
	  cubesave->Close();
	}
    }
}


// 
// cube.cc ends here
