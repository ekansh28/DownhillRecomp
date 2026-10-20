#!/usr/bin/env python
# Substitui o "rsync -rc" do bind.sh no Windows (onde nao ha rsync).
# Copia de SRC para DST apenas os ficheiros com a extensao dada, e so quando o
# conteudo muda (comparacao por hash), preservando o mtime dos ficheiros iguais
# para nao disparar rebuilds desnecessarios dos ~26k ficheiros gerados.
# Uso: python -I tools/syncgen.py SRC DST EXT      (EXT com ponto, ex.: .cpp)
import hashlib
import os
import shutil
import sys


def digest(path):
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.digest()


def sync(src, dst, ext):
    copied = skipped = 0
    for name in sorted(os.listdir(src)):
        if not name.endswith(ext):
            continue
        s = os.path.join(src, name)
        if not os.path.isfile(s):
            continue
        d = os.path.join(dst, name)
        # So copia se for novo ou o conteudo for diferente; iguais ficam com o mtime intacto.
        if os.path.exists(d) and digest(s) == digest(d):
            skipped += 1
            continue
        os.makedirs(dst, exist_ok=True)
        shutil.copyfile(s, d)  # copyfile: nao copia metadados, mtime de DST so muda se copiar
        copied += 1
    return copied, skipped


def main(argv):
    if len(argv) != 4:
        sys.stderr.write("uso: syncgen.py SRC DST EXT\n")
        return 2
    src, dst, ext = argv[1], argv[2], argv[3]
    if not os.path.isdir(src):
        sys.stderr.write("origem nao existe: %s\n" % src)
        return 2
    os.makedirs(dst, exist_ok=True)
    copied, skipped = sync(src, dst, ext)
    print("syncgen %s -> %s (%s): %d copiados, %d iguais" % (src, dst, ext, copied, skipped))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
