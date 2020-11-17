set(LLVM_TARGET_DEFINITIONS TinyRISCV.td)

tablegen(LLVM TinyRISCVGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TinyRISCVGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM TinyRISCVGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TinyRISCVGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM TinyRISCVGenCallingConv.inc -gen-callingconv)
tablegen(LLVM TinyRISCVGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM TinyRISCVGenMCCodeEmitter.inc -gen-emitter)
add_public_tablegen_target(TinyRISCVCommonTableGen)

add_llvm_target(TinyRISCVCodeGen
  TinyRISCVSubtarget.cpp
  TinyRISCVTargetMachine.cpp
  TinyRISCVRegisterInfo.cpp
  TinyRISCVInstrInfo.cpp
  TinyRISCVFrameLowering.cpp
  TinyRISCVISelLowering.cpp
  TinyRISCVSelectionDAGInfo.cpp
  TinyRISCVISelDAGToDAG.cpp
  TinyRISCVAsmPrinter.cpp
  TinyRISCVMCInstLower.cpp
  )

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
