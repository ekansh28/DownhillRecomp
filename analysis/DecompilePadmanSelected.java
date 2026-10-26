import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import java.io.PrintWriter;

public class DecompilePadmanSelected extends GhidraScript {
    @Override public void run() throws Exception {
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter("C:/Users/ekansh/Documents/GitHub/Recomp-Domination/analysis/padman-selected.c")) {
            long[] addresses = {0x0,0x6c,0x1a8,0x3e0c,0x4690,0x4824,0x49d0,0x4c6c,0x5154,0x5234,0x5388,0x54f0,0x6f70};
            for (long value : addresses) {
                Function f = getFunctionContaining(toAddr(value));
                out.println("// ==== " + Long.toHexString(value) + " " + (f == null ? "none" : f.getName()) + " ====");
                if (f != null) {
                    DecompileResults r = d.decompileFunction(f, 60, monitor);
                    out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed " + r.getErrorMessage());
                }
            }
        }
        d.dispose();
    }
}
