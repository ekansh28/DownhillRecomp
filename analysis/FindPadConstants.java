import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;

public class FindPadConstants extends GhidraScript {
    @Override
    public void run() throws Exception {
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            boolean hit = false;
            StringBuilder text = new StringBuilder();
            for (Instruction i : currentProgram.getListing().getInstructions(f.getBody(), true)) {
                String s = i.toString().toLowerCase();
                if (s.contains("0x22") || s.contains("0x593") || s.contains("0x800001")) {
                    hit = true;
                    text.append(i.getAddress()).append(" ").append(i).append("\n");
                }
            }
            if (hit) {
                println("=== " + f.getEntryPoint() + " " + f.getName() + " ===");
                print(text.toString());
            }
        }
    }
}
