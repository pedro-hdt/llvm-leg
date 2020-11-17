//===-- TinyRISCVSubtarget.cpp - TinyRISCV Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TinyRISCV specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "TinyRISCVSubtarget.h"
#include "TinyRISCV.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "tinyriscv-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TinyRISCVGenSubtargetInfo.inc"

using namespace llvm;

void TinyRISCVSubtarget::anchor() {}

TinyRISCVSubtarget::TinyRISCVSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                           TinyRISCVTargetMachine &TM)
    : TinyRISCVGenSubtargetInfo(TT, CPU, FS),
      DL("e-m:e-p:32:32-i1:8:32-i8:8:32-i16:16:32-i64:32-a:0:32-n32"),
      InstrInfo(), TLInfo(TM), TSInfo(), FrameLowering() {}
