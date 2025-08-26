import subprocess
import random

def compile_cpp(source_cpp):
    exe_name = source_cpp.replace(".cpp", "")
    compile_cmd = ["g++", source_cpp, "-o", exe_name, "-O2", "-std=c++17"]
    print(f"Compiling: {' '.join(compile_cmd)}")
    ret = subprocess.run(compile_cmd)
    if ret.returncode != 0:
        print(f"{source_cpp} Compilation failed, aborting.")
        return None
    return exe_name

def run_program(exe_name, args):
    run_cmd = ["./" + exe_name] + list(map(str, args))
    print(f"Running: {' '.join(run_cmd)}")
    ret = subprocess.run(run_cmd)
    return ret.returncode


exe_3d = compile_cpp("3D.cpp")
if exe_3d:
    for N in range(1000, 400-1, -50):
        start_positions = []

        count = 0
        while count < 100:
            coords = (
                random.randint(0, N-1),
                random.randint(0, N-1),
                random.randint(0, N-1)
            )
            start_positions.append(coords)
            count += 1
            # if N % 2 == 0 or (N % 2 == 1 and sum(coords) % 2 == 0):
                

        for pos in start_positions:
            ret_code = run_program(exe_3d, (N,) + pos)
            # 필요 시 exit 코드 체크 가능
