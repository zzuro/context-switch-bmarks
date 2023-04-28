import subprocess
import pandas as pd
from tqdm import tqdm

def benchmark_fun():
    proc = subprocess.Popen(["./ARM/main"], stdout=subprocess.DEVNULL)
    proc.wait()    
    f = open("//home//ubuntu//context-switch-bmarks//ARM//result.txt", 'r')
    return int(f.readline())



tmp = []
for i in tqdm(range(0, 10000)):
    res = benchmark_fun()
    tmp.append(res)  
    
pd.DataFrame({'cycles':tmp}).to_csv("ARM_results.csv", index=False)
