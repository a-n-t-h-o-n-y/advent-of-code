INPUT: str = "input/one.txt"

with open(INPUT, 'r', newline='') as f:
    elf_calories: list[list[int]] = [
        list(map(int, elf.split()))
        for elf
        in f.read().split('\n\n')
    ]

    max_elf_calories: int = max(map(sum, elf_calories))
    print(f"{max_elf_calories=}")
