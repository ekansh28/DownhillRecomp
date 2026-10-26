import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.symbol.Reference;
import java.io.PrintWriter;

public class ListPadCallers extends GhidraScript {
    public void run() throws Exception {
        String outName = getScriptArgs().length == 0 ? "analysis/pad-callers.txt" : getScriptArgs()[0];
        try (PrintWriter out = new PrintWriter(outName)) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                for (Instruction i : currentProgram.getListing().getInstructions(f.getBody(), true)) {
                    for (Reference r : i.getReferencesFrom()) {
                        Function target = currentProgram.getFunctionManager().getFunctionAt(r.getToAddress());
                        if (target == null) continue;
                        String name = target.getName();
                        if (name.toLowerCase().contains("scepad")) {
                            out.println(f.getEntryPoint() + " " + f.getName() + " -> " +
                                r.getToAddress() + " " + name + " at " + i.getAddress());
                        }
                    }
                }
            }
        }
    }
}
