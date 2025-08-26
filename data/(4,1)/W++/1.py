import pandas as pd
import glob
import re
import os

results = []

file_pattern = r"C:\Users\sungs\OneDrive\Documents\2-1\Project\data\(4,1)\W++\*.txt"

for filepath in glob.glob(file_pattern):
    with open(filepath, encoding="utf-8") as f:
        content = f.read()

    filename = os.path.basename(filepath)
    # 파일명에서 Dimension, N 추출
    dim_match = re.search(r"Dimension=(\d+)", filename)
    n_match = re.search(r"N=(\d+)", filename)
    dimension = int(dim_match.group(1)) if dim_match else None
    N_value = int(n_match.group(1)) if n_match else None

    # 전체 성공 / 실패 초기화
    total_success = 0
    total_fail = 0

    # 홀수/짝수 합 성공/실패 초기화
    odd_success = 0
    odd_fail = 0
    even_success = 0
    even_fail = 0

    times_ms = []
    times_us = []

    # dimension에 맞는 정규식 생성
    # 예: Start position: 0 0 0 0 0 - Success Execution time: 350 ms (350095 μs)
    coord_pattern = r"Start position:\s*"
    coord_pattern += r"\s+".join([r"(\d+)"] * dimension)  # 좌표 개수만큼 (\d+) 생성
    coord_pattern += r"\s*-\s*(\w+)\s*Execution time:\s*(\d+)\s*ms\s*\((\d+)\s*μs\)"

    regex = re.compile(coord_pattern)

    for line in content.splitlines():
        # Success / Fail summary
        succ_fail_match = re.search(r"Success:\s*(\d+)\s*Fail:\s*(\d+)", line)
        if succ_fail_match:
            total_success = int(succ_fail_match.group(1))
            total_fail = int(succ_fail_match.group(2))
            continue

        m = regex.match(line)
        if m:
            groups = m.groups()
            coords = list(map(int, groups[:dimension]))
            status = groups[dimension].lower()
            ms_time = int(groups[dimension + 1])
            us_time = int(groups[dimension + 2])

            times_ms.append(ms_time)
            times_us.append(us_time)

            pos_sum = sum(coords)

            if status == "success":
                if pos_sum % 2 == 1:
                    odd_success += 1
                else:
                    even_success += 1
            elif status == "fail":
                if pos_sum % 2 == 1:
                    odd_fail += 1
                else:
                    even_fail += 1

    total = total_success + total_fail
    overall_success_rate = total_success / total if total > 0 else None

    odd_total = odd_success + odd_fail
    odd_success_rate = odd_success / odd_total if odd_total > 0 else None

    even_total = even_success + even_fail
    even_success_rate = even_success / even_total if even_total > 0 else None

    avg_ms = sum(times_ms) / len(times_ms) if times_ms else None
    avg_us = sum(times_us) / len(times_us) if times_us else None

    results.append({
        "Dimension": dimension,
        "N": N_value,
        "평균 성공률": overall_success_rate,
        "평균 시간 (ms)": avg_ms,
        "평균 시간 (μs)": avg_us,
        "홀수 좌표 합 성공률": odd_success_rate,
        "짝수 좌표 합 성공률": even_success_rate
    })

df = pd.DataFrame(results)
df.to_excel("summary_by_file_odd_even_general.xlsx", index=False)
print("완료! summary_by_file_odd_even_general.xlsx 파일이 생성되었습니다.")
