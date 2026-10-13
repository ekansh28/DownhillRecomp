// Decompiles the functions at the given addresses to C.
// Usage (headless): -postScript DecompileFunctions.java 0x24d928,0x24d988 out.c
// @category PS2Recomp
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

import java.io.PrintWriter;

public class DecompileFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: DecompileFunctions.java addr,addr,... outfile");
            return;
        }
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(args[1])) {
            for (String text : args[0].split(",")) {
                long address = Long.decode(text.trim());
                Function function = getFunctionContaining(toAddr(address));
                if (function == null) {
                    out.println("// 0x" + Long.toHexString(address) + ": no function");
                    continue;
                }
                DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
                out.println("// ===== " + function.getName() + " @ " + function.getEntryPoint() + " =====");
                out.println(result.decompileCompleted() ? result.getDecompiledFunction().getC() : "// decompile failed: " + result.getErrorMessage());
            }
        }
    }
}
