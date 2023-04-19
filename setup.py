import subprocess
import numpy as np

def benchmark_fun():
    proc = subprocess.Popen(["./x86/main"], stdout=subprocess.DEVNULL)
    proc.wait()    
    f = open("//home//avezzu//context-switch-bmarks//x86//result.txt", 'r')
    return int(f.readline())



f = open("bmarks_res.txt", "w")

tmp = []
for i in range(0, 10000):
    tmp.append(benchmark_fun())  
    
f.write("%s\n" % np.mean(tmp))