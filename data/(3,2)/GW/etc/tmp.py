

# import os

# cpp_files = ["a.cpp", "b.cpp", "c.cpp"]
# for f in cpp_files:
#     exe = f.replace(".cpp", ".exe")
#     os.system(f"g++ {f} -o {exe}")
#     os.system(f"./{exe}")

# import os
# import platform

# cpp_files = ["3D.cpp"]

# for f in cpp_files:
#     exe = f.replace(".cpp", ".exe")
#     os.system(f"g++ {f} -o {exe}")
#     os.system(exe)

import os

cpp_files = ["3D.cpp"]

# N = 100
# start_positions = [
#     (0, 0, 0),
#     (0, 0, N-1),
#     (0, N-1, 0),
#     (0, N-1, N-1),
#     (N-1, 0, 0),
#     (N-1, 0, N-1),
#     (N-1, N-1, 0),
#     (N-1, N-1, N-1),
#     (N//2, N//2, N//2),
#     (1, 12, 15),
#     (2, 34, 15),
#     (34, 72, 15),
# ]

for N in range(0,501):
        
    # N = 100

    start_positions = []

    corners = [1, N-1]

    # 1) 8개 모서리 좌표
    for x in corners:
        for y in corners:
            for z in corners:
                start_positions.append((x,y,z))

    # 2) 중앙
    start_positions.append((N//2, N//2, N//2))

    # 3) 각 면의 중앙 (6개)
    faces = [
        (N//2, N//2, 0),
        (N//2, N//2, N-1),
        (N//2, 0, N//2),
        (N//2, N-1, N//2),
        (0, N//2, N//2),
        (N-1, N//2, N//2)
    ]

    start_positions.extend(faces)

    # 4) 임의로 몇 개 랜덤 위치 추가 (예: 10개)
    import random
    for _ in range(10):
        start_positions.append((random.randint(0, N-1),
                                random.randint(0, N-1),
                                random.randint(0, N-1)))


    for f in cpp_files:
        exe = f.replace(".cpp", ".exe")
        compile_cmd = f"g++ {f} -o {exe} -O2 -std=c++17"
        print(f"Compiling: {compile_cmd}")
        ret = os.system(compile_cmd)
        if ret != 0:
            print("Compilation failed, aborting.")
            break

        for (sx, sy, sz) in start_positions:
            # 실행 파일 경로 앞에 .\\ 붙임
            run_cmd = f".\\{exe} {N} {sx} {sy} {sz}"
            print(f"Running: {run_cmd}")
            os.system(run_cmd)
