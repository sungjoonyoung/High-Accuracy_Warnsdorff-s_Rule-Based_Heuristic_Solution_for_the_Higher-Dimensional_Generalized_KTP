
import os
import random










# 3D 실행부
cpp_files_3d = ["3D.cpp"]
exe_3d = cpp_files_3d[0].replace(".cpp", ".exe")
compile_cmd_3d = f"g++ {cpp_files_3d[0]} -o {exe_3d} -O2 -std=c++17"
print(f"Compiling 3D: {compile_cmd_3d}")
ret = os.system(compile_cmd_3d)
if ret != 0:
    print("3D Compilation failed, aborting.")
else:
    for N in range(145, 501):
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






# 4D 실행부
cpp_files_4d = ["4D.cpp"]
exe_4d = cpp_files_4d[0].replace(".cpp", ".exe")
compile_cmd_4d = f"g++ {cpp_files_4d[0]} -o {exe_4d} -O2 -std=c++17"
print(f"Compiling 4D: {compile_cmd_4d}")
ret = os.system(compile_cmd_4d)
if ret != 0:
    print("4D Compilation failed, aborting.")
else:
    for N in range(20, 50):
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








            
# 5D 실행부
cpp_files_5d = ["5D.cpp"]
exe_5d = cpp_files_5d[0].replace(".cpp", ".exe")
compile_cmd_5d = f"g++ {cpp_files_5d[0]} -o {exe_5d} -O2 -std=c++17"
print(f"Compiling 5D: {compile_cmd_5d}")
ret = os.system(compile_cmd_5d)
if ret != 0:
    print("5D Compilation failed, aborting.")
else:
    for N in range(6, 15):
        start_positions = []

        # corners = [0, N-1]

        # # 1) 5D 공간의 모서리 (2^5 = 32개)
        # for x in corners:
        #     for y in corners:
        #         for z in corners:
        #             for w in corners:
        #                 for v in corners:
        #                     start_positions.append((x, y, z, w, v))

        # # 2) 정중앙
        # center = (N//2, N//2, N//2, N//2, N//2)
        # start_positions.append(center)

        # # 3) 각 축 고정 위치에 따른 면 중앙 (5축 * 2면 = 10개)
        # mids = [0, N-1]
        # for fixed_axis in range(5):
        #     for pos in mids:
        #         coord = [N//2]*5
        #         coord[fixed_axis] = pos
        #         start_positions.append(tuple(coord))

        # 4) 랜덤 500개 좌표를 합이 짝수인 것만 넣기
        count = 0
        while count < 100:
            coords = (
                random.randint(0, N-1),
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

        for (sx, sy, sz, sw, sv) in start_positions:
            run_cmd = f".\\{exe_5d} {N} {sx} {sy} {sz} {sw} {sv}"
            print(f"Running: {run_cmd}")
            ret = os.system(run_cmd)






