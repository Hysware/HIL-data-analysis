// 修改成和文件里一致的类型
class CaenDPP_PHA {
public:
  unsigned short fChannel;
  unsigned short fBoard;
  unsigned short fTimestamp;
  bool fPUR;
  bool fPLL;
  Float_t fEnergy;
  Float_t fCFD;
  // ...
  ClassDef(CaenDPP_PHA, 1); // 继续使用 version 1 以避免误读
};

