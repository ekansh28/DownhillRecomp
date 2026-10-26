import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.mem.Memory;

public class FindMcVersionXrefs extends GhidraScript {
    @Override
    public void run() throws Exception {
        long value = Long.decode(getScriptArgs()[0]);
        Address address = toAddr(value);
        Memory memory = currentProgram.getMemory();
        byte[] needle = "too old release of mcserv.irx".getBytes("US-ASCII");
        Address found = memory.findBytes(currentProgram.getMinAddress(), needle, null, true, monitor);
        println("STRING requested=0x" + Long.toHexString(value) + " found=" + found);
        if (found != null)
            address = found;
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        for (Reference reference : getReferencesTo(address)) {
            Function function = getFunctionContaining(reference.getFromAddress());
            println("XREF " + reference.getFromAddress() + " function=" +
                    (function == null ? "<none>" : function.getName() + " @ " + function.getEntryPoint()));
            if (function != null) {
                DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
                if (result.decompileCompleted())
                    println(result.getDecompiledFunction().getC());
            }
        }
        decompiler.dispose();
    }
}
