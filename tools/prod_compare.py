import sys, subprocess, os, glob
sys.path.insert(0,'/home/calle/git/volvo/py_babelc/tests'); sys.path.insert(0,'/home/calle/git/volvo/py_babelc')
from pymonad.maybe import Just
from babelc_py.clang_parser import *
from babelc_py.json_generator import render_json_header
from babelc_py.pre_process import *
from babelc_py.type_model import validate_type_model
import test_json_correctness as t
R='/home/calle/tmp/release/repos/'
BABELC='/opt/sspc/0.30.5/sysroots/x86_64-wrlinuxsdk-linux/usr/bin/babelc'
def run(hdr, incs):
    hdr=os.path.join(R,hdr); stem=os.path.basename(hdr).rsplit('.',1)[0]
    d=f'/tmp/opencode/prod/{stem}'; os.makedirs(d,exist_ok=True)
    env=dict(os.environ, CPLUS_INCLUDE_PATH=':'.join(incs))
    r=subprocess.run([BABELC,'-babelcOutput=Json',f'-babelcDirectory={d}',hdr],capture_output=True,text=True,env=env)
    ref=glob.glob(d+'/*.json.*')
    print(f'== {stem}: orig rc={r.returncode}', r.stderr[:300].replace('\n',' | '))
    try:
        res=(Just({"header_path":hdr,"clang_args":discover_system_cpp_includes()+[f'-I{i}' for i in incs],"cpp_std":17}).bind(rewrite_babelc_attributes).bind(parse_with_clang).bind(extract_type_model).bind(validate_type_model).bind(render_json_header('out.json.h')))
    finally: cleanup_temp_files()
    if res.is_nothing(): print('  OURS FAIL',str(res.value)[:400]); return
    ours=res.value['rendered_output']; open(d+'/ours.json.h','w').write(ours)
    for w in res.value.get('validation_warnings',[]): print('  warn',w)
    if not ref: return
    o=t.blocks(ours); rb=t.blocks(open(ref[0]).read())
    print('  missing',[b[:100] for b in rb if b not in o]); print('  extra',[b[:100] for b in o if b not in rb])
    c=subprocess.run(['g++','-std=c++17','-fsyntax-only','-Wall','-Wextra']+[f'-I{i}' for i in incs]+['-x','c++',d+'/ours.json.h'],capture_output=True,text=True)
    print('  g++ rc',c.returncode,c.stderr[:300])
if __name__=='__main__':
    inc=[R+'lib-ocpcommon/include', '/home/calle/.conan2/p/b/boost4bdd9011deed7/p/include']
    for h in sys.argv[1:]: run(h,inc)
