// Decompiles the functions at the given addresses to C, with callers/callees/strings as context.
// Function names from config/binds.txt are applied in memory first (run with -readOnly so nothing is saved),
// so decompiled callers read scePadGetState(...) instead of FUN_00245230(...).
// Usage (headless): -readOnly -postScript DecompileFunctions.java 0x24d928,0x24d988 out.c
// @category PS2Recomp
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;

import java.io.File;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.util.LinkedHashSet;
import java.util.Set;

public class DecompileFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 2) {
            printerr("usage: DecompileFunctions.java addr,addr,... outfile");
            return;
        }
        applyBinds();
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
                out.println("// callers: " + callers(function));
                out.println("// callees: " + names(function.getCalledFunctions(monitor)));
                out.println("// strings: " + strings(function));
                out.println(result.decompileCompleted() ? result.getDecompiledFunction().getC() : "// decompile failed: " + result.getErrorMessage());
            }
        }
        decompiler.dispose();
    }

    // binds.txt lines are "handler@0xADDR  # comment"; ret0/ret1 are experiments, not identifications.
    private void applyBinds() throws Exception {
        File binds = new File("config/binds.txt");
        if (!binds.exists()) return;
        int id = currentProgram.startTransaction("apply binds");
        try {
            for (String line : Files.readAllLines(binds.toPath())) {
                String code = line.split("#", 2)[0].trim();
                int at = code.indexOf("@0x");
                if (at < 0) continue;
                String name = code.substring(0, at);
                if (name.equals("ret0") || name.equals("ret1")) continue;
                Function f = getFunctionAt(toAddr(Long.decode(code.substring(at + 1).trim())));
                if (f == null) continue;
                try {
                    f.setName(name, SourceType.USER_DEFINED);
                } catch (Exception e) {
                    printerr("rename " + name + ": " + e.getMessage());
                }
            }
        } finally {
            currentProgram.endTransaction(id, true);
        }
    }

    private String callers(Function function) {
        Set<String> found = new LinkedHashSet<>();
        for (Reference ref : getReferencesTo(function.getEntryPoint())) {
            Function caller = getFunctionContaining(ref.getFromAddress());
            found.add(caller == null ? ref.getFromAddress().toString() : caller.getName());
        }
        return String.join(", ", found);
    }

    private String names(Set<Function> functions) {
        Set<String> found = new LinkedHashSet<>();
        for (Function f : functions) found.add(f.getName());
        return String.join(", ", found);
    }

    private String strings(Function function) {
        Set<String> found = new LinkedHashSet<>();
        for (Instruction ins : currentProgram.getListing().getInstructions(function.getBody(), true)) {
            for (Reference ref : ins.getReferencesFrom()) {
                Address to = ref.getToAddress();
                Data data = currentProgram.getListing().getDataAt(to);
                if (data != null && data.hasStringValue()) found.add("\"" + data.getDefaultValueRepresentation().replace("\"", "") + "\"");
            }
        }
        return String.join(", ", found);
    }
}
