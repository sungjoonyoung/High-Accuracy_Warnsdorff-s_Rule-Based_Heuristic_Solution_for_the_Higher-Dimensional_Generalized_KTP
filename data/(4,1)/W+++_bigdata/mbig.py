import os
import random

cpp_files_2d = ["2D.cpp"]
exe_2d = cpp_files_2d[0].replace(".cpp", ".exe")

# 2D 나이트 투어는 상대적으로 빠르므로 N 범위를 넉넉하게 잡음
for N in range(1, 5000):  # 예: 100부터 200까지
    start_positions = []

    count = 0
    while count < 200:
        coords = (
            random.randint(0, N-1),
            random.randint(0, N-1)
            )
        if N%2==0:
            start_positions.append(coords)
            count += 1
        if N%2==1 and sum(coords) % 2 == 0:  # 합이 짝수일 때만 추가
            start_positions.append(coords)
            count += 1


    # 컴파일
    compile_cmd_2d = f"g++ {cpp_files_2d[0]} -o {exe_2d} -O2 -std=c++17"
    print(f"Compiling 2D: {compile_cmd_2d}")
    ret = os.system(compile_cmd_2d)
    if ret != 0:
        print("2D Compilation failed, aborting.")
        break

    # 실행
    for (sx, sy) in start_positions:
        run_cmd = f".\\{exe_2d} {N} {sx} {sy}"
        print(f"Running: {run_cmd}")
        ret = os.system(run_cmd)
        exit_code = ret >> 8
        if exit_code == 1:
            print("Early stop requested by program exit code 1.")
            break

