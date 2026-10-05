"""Run py_babelc over every babelc_generate() header found in a set of repos.

Usage: python tools/sweep.py REPOS_DIR OUT_DIR [--orig BABELC] [--boost DIR]
Writes OUT_DIR/results.tsv: repo, kind, header, ours, original, message.
"""
import argparse
import concurrent.futures as cf
import glob
import os
import re
import subprocess
import sys

BLOCK = re.compile(r"babelc_generate\s*\((.*?)\)", re.S)


def find_suffix(repos, base, tok):
    """Locate a header by its trailing path (after ${VAR}/ or leading dirs)."""
    rel = re.sub(r"^.*?\}/", "", tok).lstrip("/")
    for root in (base, repos):
        for n in range(rel.count("/") + 1):
            suf = "/".join(rel.split("/")[n:])
            hits = [h for h in glob.glob(root + "/**/" + suf, recursive=True)
                    if "/build" not in h and "/gen_files" not in h]
            if hits:
                return sorted(hits, key=len)[0]
    return None


def jobs(repos):
    out = set()
    for repo in sorted(os.listdir(repos)):
        base = os.path.join(repos, repo)
        for cm in glob.glob(base + "/**/CMakeLists.txt", recursive=True):
            if "/build" in cm or "/gen_files" in cm:
                continue
            txt = open(cm, errors="replace").read()
            for m in BLOCK.finditer(txt):
                body = m.group(1)
                t = re.search(r"\bTYPE\s+(\w+)", body, re.I)
                kind = t.group(1).lower() if t else "ipc"
                for tok in re.findall(r"[^\s()\"]+\.(?:h|hpp)\b", body):
                    p = tok.replace("${CMAKE_SOURCE_DIR}", base)
                    p = p.replace("${PROJECT_SOURCE_DIR}", base)
                    p = p.replace("${CMAKE_CURRENT_SOURCE_DIR}", os.path.dirname(cm))
                    if "${" in p:
                        out.add((repo, kind, tok, find_suffix(repos, base, tok)))
                        continue
                    if p.startswith("/usr/include/"):
                        rel = p[len("/usr/include/"):]
                        hits = glob.glob(f"{repos}/*/include/{rel}")
                        p = hits[0] if hits else p
                    elif not p.startswith("/"):
                        c = os.path.join(os.path.dirname(cm), tok)
                        p = c if os.path.exists(c) else os.path.join(base, tok)
                    out.add((repo, kind, tok, p if os.path.exists(p)
                             else find_suffix(repos, base, tok)))
    return sorted(out, key=lambda x: (x[0], x[1], x[2]))


def incs(repos, repo, boost):
    d = []
    mine = os.path.join(repos, repo)
    for r in [mine] + sorted(glob.glob(repos + "/*")):
        for sub in ("include", "src", "dep/*/include", "dep/*/src", "dep/*/*/include"):
            d += [x for x in glob.glob(os.path.join(r, sub)) if os.path.isdir(x)]
    d.append(mine)
    d += [boost] if boost else []
    return ["-I" + x for x in d]


def run_one(args, job):
    repo, kind, tok, path = job
    if path is None:
        return (*job[:3], "SKIP", "-", "header not found or unresolved variable")
    if kind not in ("ipc", "json"):
        return (repo, kind, tok, "SKIP", "-", f"unsupported TYPE {kind}")
    tag = f"{repo}__{os.path.basename(path)}__{kind}"
    out = os.path.join(args.out, tag)
    os.makedirs(out, exist_ok=True)
    flags = incs(args.repos, repo, args.boost) + ["-std=gnu++20", "-include", "cstdint", "-babelcCompiler=g++",
             "-babelcForce", "-babelcNoColor", f"-babelcOutput={kind.capitalize()}",
             f"-babelcDirectory={out}"]
    env = dict(os.environ)
    ours = subprocess.run([sys.executable, "-m", "babelc_py.compat", *flags, path],
                          capture_output=True, text=True, env=env, timeout=300)
    msg = (ours.stderr or ours.stdout).strip().splitlines()
    msg = msg[-1][:300] if msg else ""
    orig = "-"
    if ours.returncode != 0 and args.orig:
        oo = out + "_orig"
        os.makedirs(oo, exist_ok=True)
        fl = [f if not f.startswith("-babelcDirectory") else f"-babelcDirectory={oo}" for f in flags]
        r = subprocess.run([args.orig, *fl, path], capture_output=True, text=True,
                           env=dict(env, CPLUS_INCLUDE_PATH=args.boost or ""), timeout=300)
        orig = "ok" if r.returncode == 0 else "FAIL"
    return (repo, kind, tok, "ok" if ours.returncode == 0 else "FAIL", orig, msg)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("repos")
    ap.add_argument("out")
    ap.add_argument("--orig")
    ap.add_argument("--boost")
    ap.add_argument("-j", type=int, default=8)
    args = ap.parse_args()
    js = jobs(args.repos)
    print(len(js), "jobs", file=sys.stderr)
    with cf.ThreadPoolExecutor(args.j) as ex:
        res = list(ex.map(lambda j: run_one(args, j), js))
    with open(os.path.join(args.out, "results.tsv"), "w") as f:
        for r in res:
            f.write("\t".join(map(str, r)) + "\n")
    from collections import Counter
    print(Counter((r[3], r[4]) for r in res))


if __name__ == "__main__":
    main()
