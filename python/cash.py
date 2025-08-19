while True:
    n = input("Change: ")
    try:
        n = float(n)
        if n >= 0:
            break
    except ValueError:
        pass

n *= 100
n = int(n)

for i in range(n + 1):
    if n >= 25:
        n -= 25
    elif n >= 10:
        n -= 10
    elif n >= 5:
        n -= 5
    elif n >= 1:
        n -= 1
    else:
        print(i)
        break
