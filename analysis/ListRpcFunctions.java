import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Data;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;

public class ListRpcFunctions extends GhidraScript {
    public void run() throws Exception {
        String outName = getScriptArgs().length == 0 ? "analysis/989snd-rpc.txt" : getScriptArgs()[0];
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        try (PrintWriter out = new PrintWriter(outName)) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                boolean hit = false;
                for (Instruction i : currentProgram.getListing().getInstructions(f.getBody(), true)) {
                    String text = i.toString().toLowerCase();
                    if (text.contains("0x4d") || text.contains("0x3") || text.contains("sifregisterrpc") || text.contains("rpc")) hit = true;
                    for (Reference r : i.getReferencesFrom()) {
                        Data data = currentProgram.getListing().getDataAt(r.getToAddress());
                        if (data != null && data.hasStringValue()) {
                            String s = data.getDefaultValueRepresentation().toLowerCase();
                            if (s.contains("main rpc") || s.contains("loading rpc") || s.contains("do_rpc") || s.contains("989snd")) hit = true;
                        }
                    }
                }
                if (!hit) continue;
                out.println("===== " + f.getName() + " @ " + f.getEntryPoint() + " =====");
                DecompileResults r = d.decompileFunction(f, 30, monitor);
                out.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed " + r.getErrorMessage());
            }
        }
        d.dispose();
    }
}
