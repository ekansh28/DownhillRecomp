import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

public class ListGhidraFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (Function function : currentProgram.getFunctionManager().getFunctions(true)) {
            println(function.getEntryPoint() + " " + function.getName() + " " + function.getBody().getNumAddresses());
        }
    }
}
