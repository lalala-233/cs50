while True:
    n = input("Height: ")
    try:
        n = int(n)
        if n >= 1 and n <= 8:
            break
    except:
        n = ""

for i in range(1, n + 1):
    line = " " * (n - i) + "#" * i
    print(f"{line} {line[::-1]}")
