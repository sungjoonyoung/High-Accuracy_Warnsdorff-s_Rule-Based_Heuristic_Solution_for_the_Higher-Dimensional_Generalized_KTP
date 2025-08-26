import pandas as pd
import glob
import re
import os

results = []

file_pattern = r"C:\Users\sungs\OneDrive\Documents\2-1\Project\data\accu-more\data_degree+distance\3D\*.txt"

for filepath in glob.glob(file_pattern):
    with open(filepath, encoding="utf-8") as f:
        content = f.read()

    filename = os.path.basename(filepath)
    n_match = re.search(r"N=(\d+)", filename)
    N_value = int(n_match.group(1)) if n_match else None

    # 전체 성공 / 실패 개수 초기화
    total_success = 0
    total_fail = 0

    # 홀수 합 / 짝수 합별 성공 / 실패 카운트
    odd_success = 0
    odd_fail = 0
    even_success = 0
    even_fail = 0

    # 시간 수집용 리스트
    times_ms = []
    times_us = []

    # 각 줄 처리
    for line in content.splitlines():
        # 성공/실패 요약줄
        succ_fail_match = re.search(r"Success:\s*(\d+)\s*Fail:\s*(\d+)", line)
        if succ_fail_match:
            total_success = int(succ_fail_match.group(1))
            total_fail = int(succ_fail_match.group(2))
            continue

        # Start position + 실행시간 줄 처리
        m = re.search(
            r"Start position:\s*(\d+)\s+(\d+)\s+(\d+)\s*-\s*(\w+)\s*Execution time:\s*(\d+)\s*ms\s*\((\d+)\s*μs\)", line)
        if m:
            x, y, z, status, ms_time, us_time = m.groups()
            x, y, z = int(x), int(y), int(z)
            ms_time, us_time = int(ms_time), int(us_time)

            times_ms.append(ms_time)
            times_us.append(us_time)

            pos_sum = x + y + z

            if status.lower() == "success":
                if pos_sum % 2 == 1:
                    odd_success += 1
                else:
                    even_success += 1
            elif status.lower() == "fail":
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
        "N": N_value,
        "평균 성공률": overall_success_rate,
        "평균 시간 (ms)": avg_ms,
        "평균 시간 (μs)": avg_us,
        "홀수 XYZ 합 성공률": odd_success_rate,
        "짝수 XYZ 합 성공률": even_success_rate
    })

df = pd.DataFrame(results)
df.to_excel("summary_by_file_odd_even.xlsx", index=False)
print("완료! summary_by_file_odd_even.xlsx 파일이 생성되었습니다.")
