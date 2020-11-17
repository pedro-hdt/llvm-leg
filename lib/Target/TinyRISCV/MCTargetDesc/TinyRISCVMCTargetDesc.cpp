//===-- TinyRISCVMCTargetDesc.cpp - LEG Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TinyRISCV specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "TinyRISCVMCTargetDesc.h"
#include "InstPrinter/TinyRISCVInstPrinter.h"
#include "TinyRISCVMCAsmInfo.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "TinyRISCVGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TinyRISCVGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TinyRISCVGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createTinyRISCVMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTinyRISCVMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTinyRISCVMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTinyRISCVMCRegisterInfo(X, TinyRISCV::X1);
  return X;
}

static MCSubtargetInfo *createTinyRISCVMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU,
                                                 StringRef FS) {
  return createTinyRISCVMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCAsmInfo *createTinyRISCVMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT) {
  return new TinyRISCVMCAsmInfo(TT);
}

static MCCodeGenInfo *createTinyRISCVMCCodeGenInfo(const Triple &TT, Reloc::Model RM,
                                             CodeModel::Model CM,
                                             CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  if (RM == Reloc::Default) {
    RM = Reloc::Static;
  }
  if (CM == CodeModel::Default) {
    CM = CodeModel::Small;
  }
  if (CM != CodeModel::Small && CM != CodeModel::Large) {
    report_fatal_error("Target only supports CodeModel Small or Large");
  }

  X->initMCCodeGenInfo(RM, CM, OL);
  return X;
}

static MCInstPrinter *
createTinyRISCVMCInstPrinter(const Triple &TT, unsigned SyntaxVariant,
                       const MCAsmInfo &MAI, const MCInstrInfo &MII,
                       const MCRegisterInfo &MRI) {
  return new TinyRISCVInstPrinter(MAI, MII, MRI);
}

// Force static initialization.
extern "C" void LLVMInitializeTinyRISCVTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheTinyRISCVTarget, createTinyRISCVMCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheTinyRISCVTarget, createTinyRISCVMCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTinyRISCVTarget, createTinyRISCVMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTinyRISCVTarget, createTinyRISCVMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTinyRISCVTarget,
                                          createTinyRISCVMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheTinyRISCVTarget, createTinyRISCVMCInstPrinter);

  // Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheTinyRISCVTarget, createTinyRISCVAsmBackend);

  // Register the MCCodeEmitter
  TargetRegistry::RegisterMCCodeEmitter(TheTinyRISCVTarget, createTinyRISCVMCCodeEmitter);
}
