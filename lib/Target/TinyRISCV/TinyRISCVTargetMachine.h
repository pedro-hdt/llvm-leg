//===-- TinyRISCVTargetMachine.h - Define TargetMachine for TinyRISCV ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the TinyRISCV specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef TinyRISCVTARGETMACHINE_H
#define TinyRISCVTARGETMACHINE_H

#include "TinyRISCV.h"
#include "TinyRISCVFrameLowering.h"
#include "TinyRISCVISelLowering.h"
#include "TinyRISCVInstrInfo.h"
#include "TinyRISCVSelectionDAGInfo.h"
#include "TinyRISCVSubtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class TinyRISCVTargetMachine : public LLVMTargetMachine {
  TinyRISCVSubtarget Subtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;

public:
  TinyRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options, Reloc::Model RM,
                   CodeModel::Model CM, CodeGenOpt::Level OL);
  
  const TinyRISCVSubtarget * getSubtargetImpl() const {
    return &Subtarget;
  }
  
  virtual const TargetSubtargetInfo *
  getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm

#endif
