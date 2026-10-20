#!/usr/bin/env python
# Teste de tools/syncgen.py: ficheiro identico, modificado, novo e filtro por extensao.
import importlib.util
import os
import tempfile
import time

spec = importlib.util.spec_from_file_location(
    "syncgen", os.path.join(os.path.dirname(__file__), "..", "tools", "syncgen.py"))
syncgen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(syncgen)


def write(path, text):
    with open(path, "w") as fh:
        fh.write(text)


def run():
    tmp = tempfile.mkdtemp(prefix="syncgen_test_")
    src = os.path.join(tmp, "src")
    dst = os.path.join(tmp, "dst")
    os.makedirs(src)
    os.makedirs(dst)

    # novo (.cpp), identico (.cpp), modificado (.cpp) e um .h que o filtro deve ignorar
    write(os.path.join(src, "new.cpp"), "novo\n")
    write(os.path.join(src, "same.cpp"), "igual\n")
    write(os.path.join(src, "changed.cpp"), "versao2\n")
    write(os.path.join(src, "ignored.h"), "nao copiar\n")
    write(os.path.join(dst, "same.cpp"), "igual\n")
    write(os.path.join(dst, "changed.cpp"), "versao1\n")

    # mtime antigo e conhecido no ficheiro identico, para provar que nao e tocado
    old = 1_000_000_000
    os.utime(os.path.join(dst, "same.cpp"), (old, old))

    copied, skipped = syncgen.sync(src, dst, ".cpp")

    ok = True

    def check(label, cond):
        nonlocal ok
        print(("PASS" if cond else "FAIL"), label)
        ok = ok and cond

    check("new.cpp copiado", read(dst, "new.cpp") == "novo\n")
    check("changed.cpp atualizado", read(dst, "changed.cpp") == "versao2\n")
    check("same.cpp inalterado", read(dst, "same.cpp") == "igual\n")
    check("mtime de same.cpp preservado", int(os.path.getmtime(os.path.join(dst, "same.cpp"))) == old)
    check("filtro de extensao: ignored.h NAO copiado", not os.path.exists(os.path.join(dst, "ignored.h")))
    check("contagem: 2 copiados (new+changed), 1 igual (same)", copied == 2 and skipped == 1)

    print("RESULTADO:", "OK" if ok else "FALHOU")
    return 0 if ok else 1


def read(d, name):
    with open(os.path.join(d, name)) as fh:
        return fh.read()


if __name__ == "__main__":
    raise SystemExit(run())
