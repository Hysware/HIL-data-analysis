
#include "dataTree.h"
#include "cube.h"
#include <TFile.h>
#include <TTree.h>

#include <iostream>

using std::cout; using std::endl;

int main()
{
  char cube_name[1024] = "hil.cub";
  char tab_name[1024] = "hil.tab";
  
  cube *cu = new cube(cube_name, tab_name, 2048);

  TFile *file_in = TFile::Open("../rootfile2/three.root");
  TTree *tr_in = (TTree*)file_in->Get("three");
  dataTree *dat = new dataTree(tr_in);
  Long64_t entries = dat->GetEntries();
  for(Long64_t i=0;i<entries;i++){
    dat->GetEntry(i);

    if(dat->energy1>=(2048-1.) || dat->energy2>=(2048-1.) || dat->energy3>=(2048-1.))
      continue;
    cu->fill(dat->energy1, dat->energy2, dat->energy3);
  }

  cu->save();

  return 0;
}

