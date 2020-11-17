//===-- TinyRISCVMCAsmInfo.h - LEG asm properties --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the TinyRISCVMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef TinyRISCVTARGETASMINFO_H
#define TinyRISCVTARGETASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class StringRef;
class Target;
class Triple;

class TinyRISCVMCAsmInfo : public MCAsmInfoELF {
  virtual void anchor();

public:
  explicit TinyRISCVMCAsmInfo(const Triple &TT);
};

} // namespace llvm

#endif
