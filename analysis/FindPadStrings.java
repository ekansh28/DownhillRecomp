import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;

public class FindPadStrings extends GhidraScript {
    @Override public void run() throws Exception {
        for (Data d : currentProgram.getListing().getDefinedData(true)) {
            Object v = d.getValue();
            if (v == null) continue;
            String s = v.toString();
            if (s.toLowerCase().contains("invalid function") || s.toLowerCase().contains("padman")) {
                println("DATA " + d.getAddress() + " " + s);
                for (Reference r : getReferencesTo(d.getAddress())) {
                    Function f = getFunctionContaining(r.getFromAddress());
                    println("  REF " + r.getFromAddress() + " func=" + (f == null ? "none" : f.getEntryPoint().toString()));
                }
            }
        }
    }
}
