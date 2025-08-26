import os
import random

cpp_files_2d = ["2D.cpp"]
exe_2d = cpp_files_2d[0].replace(".cpp", ".exe")

# 2D 나이트 투어는 상대적으로 빠르므로 N 범위를 넉넉하게 잡음
for N in range(100, 201):  # 예: 100부터 200까지
    start_positions = []

    corners = [0, N-1]

    # 1) 4개의 모서리 좌표 (2D라 4개)
    for x in corners:
        for y in corners:
            start_positions.append((x, y))

    # 2) 중앙
    start_positions.append((N // 2, N // 2))

    # 3) 각 변의 중앙 (4개)
    edges = [
        (N // 2, 0),
        (N // 2, N - 1),
        (0, N // 2),
        (N - 1, N // 2)
    ]
    start_positions.extend(edges)

    # 4) 랜덤 위치 10개 추가
    for _ in range(10):
        start_positions.append((
            random.randint(0, N - 1),
            random.randint(0, N - 1)
        ))

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
