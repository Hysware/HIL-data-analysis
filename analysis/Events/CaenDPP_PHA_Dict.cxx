// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME CaenDPP_PHA_Dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "CaenDPP_PHA.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_CaenDPP_PHA(void *p = nullptr);
   static void *newArray_CaenDPP_PHA(Long_t size, void *p);
   static void delete_CaenDPP_PHA(void *p);
   static void deleteArray_CaenDPP_PHA(void *p);
   static void destruct_CaenDPP_PHA(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CaenDPP_PHA*)
   {
      ::CaenDPP_PHA *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CaenDPP_PHA >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("CaenDPP_PHA", ::CaenDPP_PHA::Class_Version(), "CaenDPP_PHA.h", 2,
                  typeid(::CaenDPP_PHA), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CaenDPP_PHA::Dictionary, isa_proxy, 4,
                  sizeof(::CaenDPP_PHA) );
      instance.SetNew(&new_CaenDPP_PHA);
      instance.SetNewArray(&newArray_CaenDPP_PHA);
      instance.SetDelete(&delete_CaenDPP_PHA);
      instance.SetDeleteArray(&deleteArray_CaenDPP_PHA);
      instance.SetDestructor(&destruct_CaenDPP_PHA);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CaenDPP_PHA*)
   {
      return GenerateInitInstanceLocal(static_cast<::CaenDPP_PHA*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::CaenDPP_PHA*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr CaenDPP_PHA::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *CaenDPP_PHA::Class_Name()
{
   return "CaenDPP_PHA";
}

//______________________________________________________________________________
const char *CaenDPP_PHA::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CaenDPP_PHA*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int CaenDPP_PHA::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CaenDPP_PHA*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CaenDPP_PHA::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CaenDPP_PHA*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CaenDPP_PHA::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CaenDPP_PHA*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void CaenDPP_PHA::Streamer(TBuffer &R__b)
{
   // Stream an object of class CaenDPP_PHA.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CaenDPP_PHA::Class(),this);
   } else {
      R__b.WriteClassBuffer(CaenDPP_PHA::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CaenDPP_PHA(void *p) {
      return  p ? new(p) ::CaenDPP_PHA : new ::CaenDPP_PHA;
   }
   static void *newArray_CaenDPP_PHA(Long_t nElements, void *p) {
      return p ? new(p) ::CaenDPP_PHA[nElements] : new ::CaenDPP_PHA[nElements];
   }
   // Wrapper around operator delete
   static void delete_CaenDPP_PHA(void *p) {
      delete (static_cast<::CaenDPP_PHA*>(p));
   }
   static void deleteArray_CaenDPP_PHA(void *p) {
      delete [] (static_cast<::CaenDPP_PHA*>(p));
   }
   static void destruct_CaenDPP_PHA(void *p) {
      typedef ::CaenDPP_PHA current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::CaenDPP_PHA

namespace ROOT {
   static TClass *vectorlECaenDPP_PHAgR_Dictionary();
   static void vectorlECaenDPP_PHAgR_TClassManip(TClass*);
   static void *new_vectorlECaenDPP_PHAgR(void *p = nullptr);
   static void *newArray_vectorlECaenDPP_PHAgR(Long_t size, void *p);
   static void delete_vectorlECaenDPP_PHAgR(void *p);
   static void deleteArray_vectorlECaenDPP_PHAgR(void *p);
   static void destruct_vectorlECaenDPP_PHAgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<CaenDPP_PHA>*)
   {
      vector<CaenDPP_PHA> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<CaenDPP_PHA>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<CaenDPP_PHA>", -2, "vector", 428,
                  typeid(vector<CaenDPP_PHA>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlECaenDPP_PHAgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<CaenDPP_PHA>) );
      instance.SetNew(&new_vectorlECaenDPP_PHAgR);
      instance.SetNewArray(&newArray_vectorlECaenDPP_PHAgR);
      instance.SetDelete(&delete_vectorlECaenDPP_PHAgR);
      instance.SetDeleteArray(&deleteArray_vectorlECaenDPP_PHAgR);
      instance.SetDestructor(&destruct_vectorlECaenDPP_PHAgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<CaenDPP_PHA> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<CaenDPP_PHA>","std::vector<CaenDPP_PHA, std::allocator<CaenDPP_PHA> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<CaenDPP_PHA>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlECaenDPP_PHAgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<CaenDPP_PHA>*>(nullptr))->GetClass();
      vectorlECaenDPP_PHAgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlECaenDPP_PHAgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlECaenDPP_PHAgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<CaenDPP_PHA> : new vector<CaenDPP_PHA>;
   }
   static void *newArray_vectorlECaenDPP_PHAgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<CaenDPP_PHA>[nElements] : new vector<CaenDPP_PHA>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlECaenDPP_PHAgR(void *p) {
      delete (static_cast<vector<CaenDPP_PHA>*>(p));
   }
   static void deleteArray_vectorlECaenDPP_PHAgR(void *p) {
      delete [] (static_cast<vector<CaenDPP_PHA>*>(p));
   }
   static void destruct_vectorlECaenDPP_PHAgR(void *p) {
      typedef vector<CaenDPP_PHA> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<CaenDPP_PHA>

namespace {
  void TriggerDictionaryInitialization_CaenDPP_PHA_Dict_Impl() {
    static const char* headers[] = {
"CaenDPP_PHA.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/zhy/APP/root_6_34/root/include/",
"/home/zhy/Desktop/2025_HIL/Events/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "CaenDPP_PHA_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$CaenDPP_PHA.h")))  CaenDPP_PHA;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "CaenDPP_PHA_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "CaenDPP_PHA.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"CaenDPP_PHA", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CaenDPP_PHA_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CaenDPP_PHA_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CaenDPP_PHA_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CaenDPP_PHA_Dict() {
  TriggerDictionaryInitialization_CaenDPP_PHA_Dict_Impl();
}
