from cs50 import get_int
import re


def check_valid(num):
    sum = 0
    count = 0
    while num > 0:
        tmp = (num % 10) * (count % 2 + 1)
        while tmp > 0:
            sum += tmp % 10
            tmp = tmp // 10
        num = num // 10
        count += 1
    if sum % 10 == 0:
        return True
    return False


def check_bits(num):
    num = f"{num}"
    length = len(num)
    AMEX_pattern = re.compile(r'^[3][47]')
    MASTERCARD_pattern = re.compile(r'^[5][1-5]')
    VISA_pattern = re.compile(r'^[4]')
    if length == 15 and AMEX_pattern.match(num):
        print("AMEX")
    elif length == 16 and MASTERCARD_pattern.match(num):
        print("MASTERCARD")
    elif (length == 13 or length == 16) and VISA_pattern.match(num):
        print("VISA")
    else:
        print("INVALID")


while True:
    credit = get_int("Number: ")
    if credit > 0:
        break
if check_valid(credit) == True:
    check_bits(credit)
else:
    print("INVALID")
