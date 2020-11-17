//===-- TinyRISCVSelectionDAGInfo.h - TinyRISCV SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the TinyRISCV subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef TinyRISCVSELECTIONDAGINFO_H
#define TinyRISCVSELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class TinyRISCVSelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  ~TinyRISCVSelectionDAGInfo();
};
}

#endif
