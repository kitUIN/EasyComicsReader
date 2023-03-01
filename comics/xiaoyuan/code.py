
import pathlib
import json
p = pathlib.Path(r"C:\Users\kulujun\Documents\xiaoyuan").rglob("*")
b = {"docs":[]}
for i in p:
    a = {"path":str(i),"name":str(i)[-8:-4]}
    b["docs"].append(a)
print(json.dumps(b))