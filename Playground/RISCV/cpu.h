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
    memctrl     memctrl;
    icache      icache;

    ifetch      fetcher;
    decoder     decoder;

    controller  control;
    scalar_file scalars;
    scalar_ALU  scalarALU;

    writer      writeback;
};


struct cpu : public cpu_input, private cpu_component {
  public:
    using sync = sync_tag <cpu_component>;
    friend class caster <cpu>;

    const wire mem_out  = memctrl.mem_out;
    const wire mem_addr = memctrl.mem_addr;
    const wire mem_wr   = memctrl.mem_wr;

  public:

    void init();
    void work();
    auto return_value() { return scalars.return_value(); }
};

// Link the wires.
void cpu::init() {
    memctrl.mem_in          = mem_in;
    memctrl.io_buffer_full  = io_buffer_full;
    memctrl.iFetchOn        = icache.iFetch;
    memctrl.iFetchPc        = fetcher.pc;

    memctrl.memType         = writeback.memType;
    memctrl.memAddr         = writeback.memAddr;
    memctrl.memData         = writeback.memData;

    icache.addrIn           = fetcher.pc;
    icache.writeEnable      = memctrl.iDone;
    icache.dataIn           = memctrl.loadData[0];

    fetcher.hit             = icache.hit;
    fetcher.instData        = icache.dataOut;
    fetcher.brDone          = writeback.brDone;
    fetcher.brData          = writeback.brData;
    fetcher.insAvail        = decoder.notFull;

    decoder.insDone         = fetcher.insDone;
    decoder.insData         = fetcher.insOut;
    decoder.insPc           = fetcher.insPc;
    decoder.rs1Busy         = scalars.rs1Busy;
    decoder.rs2Busy         = scalars.rs2Busy;
    decoder.rdBusy          = scalars.rdBusy;
    decoder.nextBubble      = control.nextBubble;

    control.issue           = decoder.issue;
    control.iType           = decoder.iType;
    control.ALUPc           = decoder.ALUPc;
    control.immediate       = decoder.immediate;
    control.rdIndex         = decoder.rdIndex;
    control.memDone         = memctrl.memDone;

    scalars.rs1             = decoder.rs1Head;
    scalars.rs2             = decoder.rs2Head;
    scalars.rd              = decoder.rdHead;
    scalars.rs1ALU          = decoder.rs1Index;
    scalars.rs2ALU          = decoder.rs2Index;
    scalars.issue           = decoder.issue;
    scalars.issueRd         = decoder.rdIndex;
    scalars.wbDone          = writeback.wbDone;
    scalars.wbData          = writeback.wbData;

    scalarALU.issue         = decoder.issue;
    scalarALU.iType         = decoder.iType;
    scalarALU.ALUPc         = decoder.ALUPc;
    scalarALU.immediate     = decoder.immediate;
    scalarALU.rs1Data       = scalars.rs1Data;
    scalarALU.rs2Data       = scalars.rs2Data;
    scalarALU.opType        = decoder.opType;
    scalarALU.isBubbling    = control.isBubbling;

    writeback.wrWork        = control.wrWork;
    writeback.wrType        = control.wrType;
    writeback.wbPc          = control.wbPc;
    writeback.wbImm         = control.wbImm;
    writeback.wbRd          = control.wbRd;
    writeback.scalarOut     = scalarALU.scalarOut;
    writeback.memDone       = memctrl.memDone;
    writeback.loadData      = memctrl.loadData[0];
    writeback.scalarData    = scalars.rs2Data;
    writeback.memStatus     = memctrl.status;
}

void cpu::work() {
    memctrl.work();
    icache.work();
    fetcher.work();
    decoder.work();
    control.work();
    scalars.work();
    scalarALU.work();
    writeback.work();
}

} // namespace dark
