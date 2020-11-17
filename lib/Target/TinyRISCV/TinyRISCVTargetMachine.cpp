//===-- TinyRISCVTargetMachine.cpp - Define TargetMachine for TinyRISCV -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "TinyRISCVTargetMachine.h"
#include "TinyRISCV.h"
#include "TinyRISCVFrameLowering.h"
#include "TinyRISCVInstrInfo.h"
#include "TinyRISCVISelLowering.h"
#include "TinyRISCVSelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  // XXX Build the triple from the arguments.
  // This is hard-coded for now for this example target.
  return "e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-a:0:32-n32";
}

TinyRISCVTargetMachine::TinyRISCVTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Reloc::Model RM, CodeModel::Model CM,
                                   CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT, CPU, FS,
                        Options, RM, CM, OL),
      Subtarget(TT, CPU, FS, *this),
      TLOF(make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

namespace {
/// TinyRISCV Code Generator Pass Configuration Options.
class TinyRISCVPassConfig : public TargetPassConfig {
public:
  TinyRISCVPassConfig(TinyRISCVTargetMachine *TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  TinyRISCVTargetMachine &getTinyRISCVTargetMachine() const {
    return getTM<TinyRISCVTargetMachine>();
  }

  virtual bool addPreISel() override;
  virtual bool addInstSelector() override;
  virtual void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *TinyRISCVTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TinyRISCVPassConfig(this, PM);
}

bool TinyRISCVPassConfig::addPreISel() { return false; }

bool TinyRISCVPassConfig::addInstSelector() {
  addPass(createTinyRISCVISelDag(getTinyRISCVTargetMachine(), getOptLevel()));
  return false;
}

void TinyRISCVPassConfig::addPreEmitPass() {}

// Force static initialization.
extern "C" void LLVMInitializeTinyRISCVTarget() {
  RegisterTargetMachine<TinyRISCVTargetMachine> X(TheTinyRISCVTarget);
}
