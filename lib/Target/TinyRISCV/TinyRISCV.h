//===-- TinyRISCV.h - Top-level interface for TinyRISCV representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// TinyRISCV back-end.
//
//===----------------------------------------------------------------------===//

#ifndef TARGET_TinyRISCV_H
#define TARGET_TinyRISCV_H

#include "MCTargetDesc/TinyRISCVMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class TinyRISCVTargetMachine;

FunctionPass *createTinyRISCVISelDag(TinyRISCVTargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;

#endif
