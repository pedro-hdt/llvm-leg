//===-- TinyRISCVRegisterInfo.cpp - TinyRISCV Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TinyRISCV implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "TinyRISCVRegisterInfo.h"
#include "TinyRISCV.h"
#include "TinyRISCVFrameLowering.h"
#include "TinyRISCVInstrInfo.h"
#include "TinyRISCVMachineFunctionInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#define GET_REGINFO_TARGET_DESC
#include "TinyRISCVGenRegisterInfo.inc"

using namespace llvm;

TinyRISCVRegisterInfo::TinyRISCVRegisterInfo() : TinyRISCVGenRegisterInfo(TinyRISCV::X1) {}

const uint16_t *
TinyRISCVRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_TinyRISCV_SaveList;
}

BitVector TinyRISCVRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(TinyRISCV::X2);
  Reserved.set(TinyRISCV::X1);
  return Reserved;
}

const uint32_t *TinyRISCVRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                                      CallingConv::ID) const {
  return CSR_TinyRISCV_RegMask;
}

bool
TinyRISCVRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
TinyRISCVRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

bool TinyRISCVRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
  return false;
}

void TinyRISCVRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  MachineInstr &MI = *II;
  const MachineFunction &MF = *MI.getParent()->getParent();
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  MachineOperand &FIOp = MI.getOperand(FIOperandNum);
  unsigned FI = FIOp.getIndex();

  // Determine if we can eliminate the index from this kind of instruction.
  unsigned ImmOpIdx = 0;
  switch (MI.getOpcode()) {
  default:
    // Not supported yet.
    return;
  case TinyRISCV::LW:
  case TinyRISCV::SW:
    ImmOpIdx = FIOperandNum + 1;
    break;
  }

  // FIXME: check the size of offset.
  MachineOperand &ImmOp = MI.getOperand(ImmOpIdx);
  int Offset = MFI->getObjectOffset(FI) + MFI->getStackSize() + ImmOp.getImm();
  FIOp.ChangeToRegister(TinyRISCV::X2, false);
  ImmOp.setImm(Offset);
}

unsigned TinyRISCVRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return TinyRISCV::X8;
}
