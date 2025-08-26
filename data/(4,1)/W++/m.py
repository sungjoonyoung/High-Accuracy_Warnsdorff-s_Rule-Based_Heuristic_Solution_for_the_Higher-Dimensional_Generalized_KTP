import os
import random

cpp_files_2d = ["2D.cpp"]
exe_2d = cpp_files_2d[0].replace(".cpp", ".exe")

# 2D 나이트 투어는 상대적으로 빠르므로 N 범위를 넉넉하게 잡음
for N in range(7, 100):  # 예: 100부터 200까지
    start_positions = []

    # corners = [0, N-1]

    # # 1) 4개의 모서리 좌표 (2D라 4개)
    # for x in corners:
    #     for y in corners:
    #         start_positions.append((x, y))

    # # 2) 중앙
    # start_positions.append((N // 2, N // 2))

    # # 3) 각 변의 중앙 (4개)
    # edges = [
    #     (N // 2, 0),
    #     (N // 2, N - 1),
    #     (0, N // 2),
    #     (N - 1, N // 2)
    # ]
    # start_positions.extend(edges)

    # 4) 랜덤 500개 좌표를 합이 짝수인 것만 넣기
    count = 0
    while count < 100:
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











# 4D 실행부
cpp_files_4d = ["4D.cpp"]
exe_4d = cpp_files_4d[0].replace(".cpp", ".exe")
compile_cmd_4d = f"g++ {cpp_files_4d[0]} -o {exe_4d} -O2 -std=c++17"
print(f"Compiling 4D: {compile_cmd_4d}")
ret = os.system(compile_cmd_4d)
if ret != 0:
    print("4D Compilation failed, aborting.")
else:
    for N in range(1, 25):
        start_positions = []

        # corners = [0, N-1]

        # # 1) 4D 공간의 모서리 (16개)
        # for x in corners:
        #     for y in corners:
        #         for z in corners:
        #             for w in corners:
        #                 start_positions.append((x, y, z, w))

        # # 2) 정중앙
        # center = (N//2, N//2, N//2, N//2)
        # start_positions.append(center)

        # # 3) 각 면 중앙 (8x2 = 16개)
        # mids = [0, N-1]
        # for fixed_axis in range(4):
        #     for pos in mids:
        #         coord = [N//2]*4
        #         coord[fixed_axis] = pos
        #         start_positions.append(tuple(coord))

        # 4) 랜덤 500개 좌표를 합이 짝수인 것만 넣기
        count = 0
        while count < 100:
            coords = (
                random.randint(0, N-1),
                random.randint(0, N-1),
                random.randint(0, N-1),
                random.randint(0, N-1)
                )
            if N%2==0:
                start_positions.append(coords)
                count += 1
            if N%2==1 and sum(coords) % 2 == 0:  # 합이 짝수일 때만 추가
                start_positions.append(coords)
                count += 1

        for (sx, sy, sz, sw) in start_positions:
            run_cmd = f".\\{exe_4d} {N} {sx} {sy} {sz} {sw}"
            print(f"Running: {run_cmd}")
            ret = os.system(run_cmd)













# 3D 실행부
cpp_files_3d = ["3D.cpp"]
exe_3d = cpp_files_3d[0].replace(".cpp", ".exe")
compile_cmd_3d = f"g++ {cpp_files_3d[0]} -o {exe_3d} -O2 -std=c++17"
print(f"Compiling 3D: {compile_cmd_3d}")
ret = os.system(compile_cmd_3d)
if ret != 0:
    print("3D Compilation failed, aborting.")
else:
    for N in range(8, 50):
        start_positions = []

        # corners = [0, N-1]

        # # 1) 8개 모서리 좌표
        # for x in corners:
        #     for y in corners:
        #         for z in corners:
        #             start_positions.append((x,y,z))

        # # 2) 중앙
        # start_positions.append((N//2, N//2, N//2))

        # # 3) 각 면의 중앙 (6개)
        # faces = [
        #     (N//2, N//2, 0),
        #     (N//2, N//2, N-1),
        #     (N//2, 0, N//2),
        #     (N//2, N-1, N//2),
        #     (0, N//2, N//2),
        #     (N-1, N//2, N//2)
        # ]
        # start_positions.extend(faces)

        # 4) 랜덤 500개 좌표를 합이 짝수인 것만 넣기
        count = 0
        while count < 100:
            coords = (
                random.randint(0, N-1),
                random.randint(0, N-1),
                random.randint(0, N-1)
                )
            if N%2==0:
                start_positions.append(coords)
                count += 1
            if N%2==1 and sum(coords) % 2 == 0:  # 합이 짝수일 때만 추가
                start_positions.append(coords)
                count += 1  

        for (sx, sy, sz) in start_positions:
            run_cmd = f".\\{exe_3d} {N} {sx} {sy} {sz}"
            print(f"Running: {run_cmd}")
            ret = os.system(run_cmd)










            




