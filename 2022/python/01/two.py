INPUT: str = "input/one.txt"

with open(INPUT, 'r', newline='') as f:
    elf_calories: list[list[int]] = [
        list(map(int, elf.split()))
        for elf
        in f.read().split('\n\n')
    ]

    sum_top_three = sum(sorted(list(map(sum, elf_calories)), reverse=True)[0:3])
    print(f"{sum_top_three=}")
