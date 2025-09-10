
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
    for N in range(400, 501, 20):
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
        while count < 500:
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




