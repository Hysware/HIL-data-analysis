// UserDefine.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 10月 20 16:16:28 2017 (+0800)
// Last-Updated: 六 12月 28 13:35:58 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 51
// URL: http://wuhongyi.cn 

// The user needs to modify the parameters in this file.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef _USERDEFINE_H_
#define _USERDEFINE_H_

#define RAWFILEPATH "/home/zhy/Desktop/sort/Ge_Decode/"   //Path to the original ROOT file
#define RAWFILENAME "data"                   //The file name of the original file
#define ROOTFILEPATH "/home/zhy/Desktop/sort/matrix/"  //The path to generate the ROOT file

#define EVENTTIMEWINDOWSWIDTH  30  //unit: 10ns
#define COINTIMEWINDOWSWIDTH   100  //unit: 10ns

#define ADDBACKTIMEDIFF 10 // unit: 10 ns

// 阈值 keV
#define THRE_LOW  5

////   #define THRE_HIGH 2048

#define THRE_HIGH 2048
#define THRE_xiaopingmian 500

#define THRE_MULTIHIT 0

#define MATRIX_ENERGY_MAX 2048 //keV

#define REFSID 1
#define REFCH  0


// #define CUBEMATRIX //不生成三维矩阵则注释本行

// #define TESTMODE //调试模式下使用


#endif /* _USERDEFINE_H_ */
// 
// UserDefine.hh ends here
