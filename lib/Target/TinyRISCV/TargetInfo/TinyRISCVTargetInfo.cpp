//===-- TinyRISCVTargetInfo.cpp - LEG Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TinyRISCV.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target llvm::TheTinyRISCVTarget;

extern "C" void LLVMInitializeTinyRISCVTargetInfo() {
  RegisterTarget<Triple::leg> X(TheTinyRISCVTarget, "tinyriscv", "TinyRISCV");
}
