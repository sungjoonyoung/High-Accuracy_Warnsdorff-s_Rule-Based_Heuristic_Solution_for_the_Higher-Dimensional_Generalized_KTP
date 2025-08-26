
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
    for N in range(200, 400):
        start_positions = []

        corners = [0, N-1]

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
        for _ in range(100):
            start_positions.append((random.randint(0, N-1),
                                    random.randint(0, N-1),
                                    random.randint(0, N-1)))

        for (sx, sy, sz) in start_positions:
            run_cmd = f".\\{exe_3d} {N} {sx} {sy} {sz}"
            print(f"Running: {run_cmd}")
            ret = os.system(run_cmd)







import os
import random

cpp_files = ["4D.cpp"]

for N in range(40, 70):  # 큰 수는 오래 걸리므로 예시로 10까지만
    start_positions = []

    corners = [0, N-1]

    # 1) 4D 공간의 모서리 (16개)
    for x in corners:
        for y in corners:
            for z in corners:
                for w in corners:
                    start_positions.append((x, y, z, w))

    # 2) 정중앙
    center = (N//2, N//2, N//2, N//2)
    start_positions.append(center)

    # 3) 각 면 중앙 (8x2 = 16개)
    mids = [0, N-1]
    for fixed_axis in range(4):  # x, y, z, w
        for pos in mids:
            coord = [N//2]*4
            coord[fixed_axis] = pos
            start_positions.append(tuple(coord))

    # 4) 랜덤 10개
    for _ in range(10):
        start_positions.append((
            random.randint(0, N-1),
            random.randint(0, N-1),
            random.randint(0, N-1),
            random.randint(0, N-1)
        ))

    for f in cpp_files:
        exe = f.replace(".cpp", ".exe")
        compile_cmd = f"g++ {f} -o {exe} -O2 -std=c++17"
        print(f"Compiling: {compile_cmd}")
        ret = os.system(compile_cmd)
        if ret != 0:
            print("Compilation failed, aborting.")
            break

        for (sx, sy, sz, sw) in start_positions:
            run_cmd = f".\\{exe} {N} {sx} {sy} {sz} {sw}"
            print(f"Running: {run_cmd}")
            ret = os.system(run_cmd)
            exit_code = ret >> 8  # Windows 또는 유닉스에서 exit code 추출
            if ret==1 : break



# import os
# import random

# cpp_files = ["3D.cpp"]

# for N in range(2,501):
        
#     # N = 100

#     start_positions = []

#     corners = [0, N-1]

#     # 1) 8개 모서리 좌표
#     for x in corners:
#         for y in corners:
#             for z in corners:
#                 start_positions.append((x,y,z))

#     # 2) 중앙
#     start_positions.append((N//2, N//2, N//2))

#     # 3) 각 면의 중앙 (6개)
#     faces = [
#         (N//2, N//2, 0),
#         (N//2, N//2, N-1),
#         (N//2, 0, N//2),
#         (N//2, N-1, N//2),
#         (0, N//2, N//2),
#         (N-1, N//2, N//2)
#     ]

#     start_positions.extend(faces)

#     # 4) 임의로 몇 개 랜덤 위치 추가 (예: 10개)
#     import random
#     for _ in range(10):
#         start_positions.append((random.randint(0, N-1),
#                                 random.randint(0, N-1),
#                                 random.randint(0, N-1)))


#     for f in cpp_files:
#         exe = f.replace(".cpp", ".exe")
#         compile_cmd = f"g++ {f} -o {exe} -O2 -std=c++17"
#         print(f"Compiling: {compile_cmd}")
#         ret = os.system(compile_cmd)
#         if ret != 0:
#             print("Compilation failed, aborting.")
#             break

#         for (sx, sy, sz) in start_positions:
#             # 실행 파일 경로 앞에 .\\ 붙임
#             run_cmd = f".\\{exe} {N} {sx} {sy} {sz}"
#             print(f"Running: {run_cmd}")
#             ret = os.system(run_cmd)
#             exit_code = ret >> 8  # Windows 또는 유닉스에서 exit code 추출
#             if ret==1 : break




# cpp_files = ["5D.cpp"]  # 5D 나이트 투어 C++ 파일명

# for N in range(2, 51):  # 예시로 2부터 50까지 반복, 너무 크면 오래걸림
#     start_positions = []

#     corners = [0, N-1]

#     # 1) 5D 공간의 모서리 (2^5 = 32개)
#     for x in corners:
#         for y in corners:
#             for z in corners:
#                 for w in corners:
#                     for v in corners:
#                         start_positions.append((x, y, z, w, v))

#     # 2) 정중앙
#     center = (N//2, N//2, N//2, N//2, N//2)
#     start_positions.append(center)

#     # 3) 각 축 고정 위치에 따른 면 중앙 (5축 * 2면 = 10개)
#     mids = [0, N-1]
#     for fixed_axis in range(5):  # 0~4 축
#         for pos in mids:
#             coord = [N//2]*5
#             coord[fixed_axis] = pos
#             start_positions.append(tuple(coord))

#     # 4) 랜덤 10개 위치
#     for _ in range(10):
#         start_positions.append((
#             random.randint(0, N-1),
#             random.randint(0, N-1),
#             random.randint(0, N-1),
#             random.randint(0, N-1),
#             random.randint(0, N-1)
#         ))

#     for f in cpp_files:
#         exe = f.replace(".cpp", ".exe")
#         compile_cmd = f"g++ {f} -o {exe} -O2 -std=c++17"
#         print(f"Compiling: {compile_cmd}")
#         ret = os.system(compile_cmd)
#         if ret != 0:
#             print("Compilation failed, aborting.")
#             break

#         for (sx, sy, sz, sw, sv) in start_positions:
#             run_cmd = f".\\{exe} {N} {sx} {sy} {sz} {sw} {sv}"
#             print(f"Running: {run_cmd}")
#             ret = os.system(run_cmd)
#             exit_code = ret >> 8  # Windows 또는 유닉스에서 exit code 추출
#             # print(ret)
#             if ret==1 : break




















# import os
# import random

# cpp_files = ["4D.cpp"]

# for N in range(2, 101):  # 큰 수는 오래 걸리므로 예시로 10까지만
#     start_positions = []

#     corners = [0, N-1]

#     # 1) 4D 공간의 모서리 (16개)
#     for x in corners:
#         for y in corners:
#             for z in corners:
#                 for w in corners:
#                     start_positions.append((x, y, z, w))

#     # 2) 정중앙
#     center = (N//2, N//2, N//2, N//2)
#     start_positions.append(center)

#     # 3) 각 면 중앙 (8x2 = 16개)
#     mids = [0, N-1]
#     for fixed_axis in range(4):  # x, y, z, w
#         for pos in mids:
#             coord = [N//2]*4
#             coord[fixed_axis] = pos
#             start_positions.append(tuple(coord))

#     # 4) 랜덤 10개
#     for _ in range(10):
#         start_positions.append((
#             random.randint(0, N-1),
#             random.randint(0, N-1),
#             random.randint(0, N-1),
#             random.randint(0, N-1)
#         ))

#     for f in cpp_files:
#         exe = f.replace(".cpp", ".exe")
#         compile_cmd = f"g++ {f} -o {exe} -O2 -std=c++17"
#         print(f"Compiling: {compile_cmd}")
#         ret = os.system(compile_cmd)
#         if ret != 0:
#             print("Compilation failed, aborting.")
#             break

#         for (sx, sy, sz, sw) in start_positions:
#             run_cmd = f".\\{exe} {N} {sx} {sy} {sz} {sw}"
#             print(f"Running: {run_cmd}")
#             ret = os.system(run_cmd)
#             exit_code = ret >> 8  # Windows 또는 유닉스에서 exit code 추출
#             if ret==1 : break









