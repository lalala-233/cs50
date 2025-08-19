while True:
    n = input("Height: ")
    if n.isdecimal():
        n = int(n)
        if n >= 1 and n <= 8:
            break

for i in range(1, n + 1):
    print(" " * (n - i) + "#" * i)
