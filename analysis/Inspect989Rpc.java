import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.mem.Memory;
import java.io.PrintWriter;

public class Inspect989Rpc extends GhidraScript {
    public void run() throws Exception {
        String outName = getScriptArgs().length == 0 ? "analysis/989snd-rpc-target.txt" : getScriptArgs()[0];
        Memory mem = currentProgram.getMemory();
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(outName)) {
            for (int n : new int[] {1, 3, 9, 0x4d}) {
                Address slot = toAddr(0x1c5d4L + n * 4L);
                int target = mem.getInt(slot);
                out.printf("rpc=%d slot=%s target=0x%08x%n", n, slot, target);
                Function f = getFunctionAt(toAddr(Integer.toUnsignedLong(target)));
                if (f == null) f = getFunctionContaining(toAddr(Integer.toUnsignedLong(target)));
                if (f != null) {
                    out.println("function=" + f.getName() + " @ " + f.getEntryPoint());
                    DecompileResults r = d.decompileFunction(f, 60, monitor);
                    out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed " + r.getErrorMessage());
                }
            }
            for (long address : new long[] {0x8290L, 0x8b78L, 0x928cL, 0x1a6c4L}) {
                Function f = getFunctionContaining(toAddr(address));
                out.printf("direct=0x%08x function=%s%n", address, f == null ? "null" : f.getName());
                if (f != null) {
                    DecompileResults r = d.decompileFunction(f, 60, monitor);
                    out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed " + r.getErrorMessage());
                }
            }
        }
        d.dispose();
    }
}
