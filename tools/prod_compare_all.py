import re,glob,os,sys
exec(open('/tmp/opencode/prod/run.py').read().split("if __name__")[0])
import io,contextlib
repos=[d for d in os.listdir(R)]
incs0=[R+'lib-ocpcommon/include',R+'lib-ocplog/include','/home/calle/.conan2/p/b/boost4bdd9011deed7/p/include']
jobs=[]
for repo in repos:
    for cm in glob.glob(R+repo+'/**/CMakeLists.txt',recursive=True):
        txt=open(cm).read()
        for m in re.finditer(r'babelc_generate\((.*?)\)',txt,re.S):
            b=m.group(1)
            if not re.search(r'TYPE\s+json',b,re.I): continue
            for tok in re.findall(r'[^\s)]+\.(?:h|hpp)\b',b):
                p=tok.replace('${CMAKE_SOURCE_DIR}',R+repo).replace('${PROJECT_SOURCE_DIR}',R+repo)
                if p.startswith('/usr/include/'): p=R+'lib-ocpcommon/include/'+p[len('/usr/include/'):]
                elif not p.startswith('/'): p=os.path.join(os.path.dirname(cm),tok) if not os.path.exists(os.path.join(R+repo,tok)) else os.path.join(R+repo,tok)
                if os.path.exists(p): jobs.append((repo,p[len(R):]))
jobs=sorted(set(jobs))
print(len(jobs),'headers')
for repo,h in jobs:
    if h.endswith('babelconf_version.h'): continue
    incs=incs0+[R+repo+'/include',R+repo+'/src',R+repo]+glob.glob(R+repo+'/src/**/include',recursive=True)[:20]
    try: run(h,incs)
    except Exception as e: print('EXC',h,e)
