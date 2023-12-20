#pragma once
#include "utility.h"

#include "alu.h"
#include "icache.h"
#include "memctrl.h"
#include "ifetch.h"
#include "decoder.h"
#include "register.h"
#include "controller.h"
#include "writer.h"

namespace dark {

struct cpu_input {
    wire mem_in;
    wire io_buffer_full;
};
struct cpu_component {
    memctrl     Memctrl;
    icache      Icache;

    ifetch      Fetcher;
    decoder     Decoder;

    controller  Control;
    scalar_file Scalars;
    scalar_ALU  ScalarALU;

    writer      Writeback;
};


struct cpu : public cpu_input, private cpu_component {
  public:
    using sync = sync_tag <cpu_component>;
    friend class caster <cpu>;

    const wire mem_out  = Memctrl.mem_out;
    const wire mem_addr = Memctrl.mem_addr;
    const wire mem_wr   = Memctrl.mem_wr;

  public:

    void init();
    void work();
    auto return_value() { return Scalars.return_value() & 0xff; }
};

// Link the wires.
void cpu::init() {
    Memctrl.mem_in          = mem_in;
    Memctrl.io_buffer_full  = io_buffer_full;
    Memctrl.iFetchOn        = Icache.iFetch;
    Memctrl.iFetchPc        = Fetcher.pc;
    Memctrl.memType         = Writeback.memType;
    Memctrl.memSize         = Writeback.memSize;
    Memctrl.memAddr         = Writeback.memAddr;
    Memctrl.scalarStore     = Writeback.scalarStore;

    Icache.addrIn           = Fetcher.pc;
    Icache.writeEnable      = Memctrl.iDone;
    Icache.dataIn           = Memctrl.scalarLoad;

    Fetcher.hit             = Icache.hit;
    Fetcher.instData        = Icache.dataOut;
    Fetcher.brDone          = Writeback.brDone;
    Fetcher.brData          = Writeback.brData;
    Fetcher.insAvail        = Decoder.notFull;

    Decoder.insDone         = Fetcher.insDone;
    Decoder.insData         = Fetcher.insOut;
    Decoder.insPc           = Fetcher.insPc;
    Decoder.rs1Busy         = Scalars.rs1Busy;
    Decoder.rs2Busy         = Scalars.rs2Busy;
    Decoder.rdBusy          = Scalars.rdBusy;
    Decoder.nextBubble      = Control.nextBubble;

    Control.issue           = Decoder.issue;
    Control.iType           = Decoder.iType;
    Control.ALUPc           = Decoder.ALUPc;
    Control.immediate       = Decoder.immediate;
    Control.rdIndex         = Decoder.rdIndex;
    Control.memDone         = Memctrl.memDone;
    Control.dbgCmd          = Decoder.dbgCmd;

    Scalars.rs1             = Decoder.rs1Head;
    Scalars.rs2             = Decoder.rs2Head;
    Scalars.rd              = Decoder.rdHead;
    Scalars.rs1ALU          = Decoder.rs1Index;
    Scalars.rs2ALU          = Decoder.rs2Index;
    Scalars.issue           = Decoder.issue;
    Scalars.issueRd         = Decoder.rdIndex;
    Scalars.wbDone          = Writeback.wbDone;
    Scalars.wbData          = Writeback.wbData;

    ScalarALU.issue         = Decoder.issue;
    ScalarALU.iType         = Decoder.iType;
    ScalarALU.ALUPc         = Decoder.ALUPc;
    ScalarALU.immediate     = Decoder.immediate;
    ScalarALU.rs1Data       = Scalars.rs1Data;
    ScalarALU.rs2Data       = Scalars.rs2Data;
    ScalarALU.opType        = Decoder.opType;
    ScalarALU.isBubbling    = Control.isBubbling;

    Writeback.wrWork        = Control.wrWork;
    Writeback.wrType        = Control.wrType;
    Writeback.wbPc          = Control.wbPc;
    Writeback.wbImm         = Control.wbImm;
    Writeback.wbRd          = Control.wbRd;
    Writeback.scalarOut     = ScalarALU.scalarOut;
    Writeback.memDone       = Memctrl.memDone;
    Writeback.loadData      = Memctrl.scalarLoad;
    Writeback.scalarData    = Scalars.rs2Data;
    Writeback.memStatus     = Memctrl.status;
    Writeback.dbgCmd        = Control.dbgOut;
}

void cpu::work() {
    Memctrl.work();
    Icache.work();
    Fetcher.work();
    Decoder.work();
    Control.work();
    Scalars.work();
    ScalarALU.work();
    Writeback.work();
}

} // namespace dark
