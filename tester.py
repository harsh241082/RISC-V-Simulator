import os
import subprocess

folder_path = 'test_cases/'
file_names = os.listdir(folder_path)

for file in file_names:
    with open(("test_cases/" + file),'r') as f:
        content = f.read()
    with open("input.s",'w') as o:
        o.write(content)
    if os.path.exists("riscv_asm.exe"):
        pass
    else:
        print("Please run make all befor this file")
    subprocess.run(["riscv_asm.exe"])
    if os.path.exists("output.hex"):
        with open("output.hex",'r') as f:
            print("---------------Start---------------")
            print(f.read())
            print("----------------End---------------")
            print("\n \n")