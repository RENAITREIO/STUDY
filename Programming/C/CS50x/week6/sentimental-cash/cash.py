from cs50 import get_float

while True:
    cash = get_float("Charge: ") * 100
    if cash > 0:
        break
num = int(cash // 25 + cash % 25 // 10 + cash % 25 % 10 // 5 + cash % 25 % 10 % 5 // 1)
print(num)
