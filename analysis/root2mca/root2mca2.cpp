#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <string>
#include "TSystem.h"

#include <filesystem>


void root2mca(TString filename) {
    // 你可以根据实际情况修改这行
    // std::string sourceFile = "/media/zhy/exp/2025_HIL/rf/run_0064_03-07-2025_14h29m35s/eagleLF_i2884_0064_0000_sorted.root";

    // TFile *file = TFile::Open(sourceFile.c_str());

    std::string filename_str(filename.Data()); 
		size_t run_pos = filename_str.find("run_");
    if (run_pos == std::string::npos) {
        std::cerr << "Error: 'run_' not found in filename!" << std::endl;
        return;
    }
    
    // 提取 "0022"（假设固定4位数字）
    std::string run_str = filename_str.substr(run_pos + 4, 4);  // "0022"
    
    // 2. 转换为整数
    int run_num;
    try {
        run_num = std::stoi(run_str);  // 22
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Failed to convert '" << run_str << "' to number!" << std::endl;
        return;
    }
    
    std::cout << "Extracted number: " << run_num << std::endl;  // 输出: 22
    
    // 3. 创建文件 "22mca"
    std::string mcadirname = "/mnt/user/zhanghongyi/hil/mca/"+std::to_string(run_num) + "mca";  // "22mca"
    
    if (!std::filesystem::create_directory(mcadirname)) {
        std::cerr << "错误：文件夹 " << mcadirname << " 已存在或创建失败！" << std::endl;
        return;
    }
    
    std::cout << "文件夹创建成功: " << mcadirname << std::endl;  // 输出: 文件夹创建成功: 22mca

    TFile *file = new TFile(filename.Data(),"READ");

    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }

    TTree *tree = (TTree*)file->Get("NeedleTree");
    if (!tree) {
        std::cerr << "Error getting tree: NeedleTree" << std::endl;
        file->Close();
        return;
    }
    TString dir = gSystem->DirName(filename);
    TFile *rootfile = new TFile(TString::Format("%s/raw_th1_0000.root",mcadirname.c_str()),"RECREATE");

    // TFile *rootfile = new TFile("./raw_th1.root","RECREATE");
    if(!rootfile->IsOpen())
    {
      std::cout<<"Can't create root file"<<std::endl;
    }
    rootfile->cd();
    for (int sid = 0; sid <= 2; ++sid) {
        for (int ch = 0; ch <= 15; ch += 2) {
	    if (sid ==2 && ch== 2) break;
            std::string histName = "sid" + std::to_string(sid) + "_ch" + std::to_string(ch);
            // TH1F *hist = new TH1F(histName.c_str(), histName.c_str(), 32768, 0, 32768);
            TH1F *hist = new TH1F(histName.c_str(), histName.c_str(), 16384, 0, 16384);

            std::string drawCmd = "EAGLE.fEnergy>>" + histName;
            std::string cut = "EAGLE.fBoard==" + std::to_string(sid) + " && EAGLE.fChannel==" + std::to_string(ch);

            std::cout << "Processing sid = " << sid << ", ch = " << ch << std::endl;
            tree->Draw(drawCmd.c_str(), cut.c_str(), "goff"); // 'goff' means off-screen, faster
	    hist->Write();
            // std::string outFile = "./board_" + std::to_string(sid) + "ch_" + std::to_string(ch) + ".mca";
            std::string outFile = TString::Format("%s/board_%dch_%d.mca",mcadirname.c_str(),sid,ch).Data();
	    std::ofstream fout(outFile);
            if (!fout.is_open()) {
                std::cerr << "Failed to open output file: " << outFile << std::endl;
                delete hist;
                continue;
            }

            fout << "<<PMCA SPECTRUM>>" << std::endl;
            fout << "TAG - PKUXIADAQ" << std::endl;
            fout << "DESCRIPTION - Hongyi Wu" << std::endl;
            fout << "GAIN - 6" << std::endl;
            fout << "THRESHOLD - " << std::endl;
            fout << "LIVE_MODE - " << std::endl;
            fout << "PRESET_TIME - " << std::endl;
            fout << "LIVE_TIME - " << std::endl;
            fout << "REAL_TIME - " << std::endl;
            fout << "START_TIME - " << std::endl;
            fout << "SERIAL_NUMBER - " << std::endl;
            fout << "<<DATA>>" << std::endl;

            for (int i = 1; i <= hist->GetNbinsX(); ++i) {
            // for (int i = 1; i <= 32000; ++i) {
                int count = static_cast<int>(hist->GetBinContent(i));
                fout << count << "\n";
            }

            fout << "<<END>>" << std::endl;
            fout.close();
            delete hist;
        }
    }

    file->Close();
    delete file;
    rootfile->Close();
    delete rootfile;
}

// main
int main(int argc, char *argv[]) {
     // 可按需修改
    TString filename(argv[1]);
    root2mca(filename);
    return 0;
}

