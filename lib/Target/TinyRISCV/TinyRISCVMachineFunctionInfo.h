//===-- TinyRISCVMachineFuctionInfo.h - TinyRISCV machine function info -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares TinyRISCV-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef TinyRISCVMACHINEFUNCTIONINFO_H
#define TinyRISCVMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

// Forward declarations
class Function;

/// TinyRISCVFunctionInfo - This class is derived from MachineFunction private
/// TinyRISCV target-specific information for each MachineFunction.
class TinyRISCVFunctionInfo : public MachineFunctionInfo {
public:
  TinyRISCVFunctionInfo() {}

  ~TinyRISCVFunctionInfo() {}
};
} // End llvm namespace

#endif // TinyRISCVMACHINEFUNCTIONINFO_H

