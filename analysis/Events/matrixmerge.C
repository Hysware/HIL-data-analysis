// matrixmerge.C --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 11月 15 16:16:20 2021 (+0800)
// Last-Updated: 五 11月 19 19:32:06 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 8
// URL: http://wuhongyi.cn 
void matrixmerge(int run1=425,int run2=484){
  TFile *f = new TFile(Form("ggunsub_merged_%d_%d.root",run1,run2),"recreate");
  TH2I *hggmat = new TH2I("mat_merged","mat_merged",4096,0,2048,4096,0,2048);
  // hggmat->Clear();
  for(int i=run1;i<=run2;i++){
   // if(i==477||i==478)continue;
    TFile *fin = new TFile(Form("/media/cloud/ExpData-2021&2022/zy/data_R%04d_W100.root",i));
    TH2I *hggadd = (TH2I*)fin->Get("mat_all");
    hggmat->Add(hggmat,hggadd,1,1);
    cout << i << " merged" << endl;
  }
  f->cd();
  hggmat->Write();
  f->Close();
}
// 
// matrixmerge.C ends here
