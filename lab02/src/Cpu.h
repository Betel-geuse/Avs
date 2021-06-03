
#ifndef RISCV_SIM_CPU_H
#define RISCV_SIM_CPU_H

#include "Memory.h"
#include "Decoder.h"
#include "RegisterFile.h"
#include "CsrFile.h"
#include "Executor.h"

class Cpu
{
public:
    Cpu(Memory& mem)
        : _mem(mem)
    {

    }

    void ProcessInstruction()
    {
        Word i = _mem.Request(_ip);
        InstructionPtr instr_ptr = _decoder.Decode(i);
        _rf.Read(instr_ptr);
        _csrf.Read(instr_ptr);
        _exe.Execute(instr_ptr, _ip);
        _mem.Request(instr_ptr);
        _rf.Write(instr_ptr);
        _csrf.Write(instr_ptr);
        _csrf.InstructionExecuted();
        _ip = instr_ptr->_nextIp;
    }

    void Reset(Word ip)
    {
        _csrf.Reset();
        _ip = ip;
    }

    std::optional<CpuToHostData> GetMessage()
    {
        return _csrf.GetMessage();
    }

private:
    Reg32 _ip;
    Decoder _decoder;
    RegisterFile _rf;
    CsrFile _csrf;
    Executor _exe;
    Memory& _mem;
};


#endif //RISCV_SIM_CPU_H
