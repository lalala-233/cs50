def check_length_and_prefix(
    number: str, lengths: int | tuple[int, ...], prefix: str | tuple[str, ...]
) -> bool:
    if isinstance(lengths, int):
        lengths = (lengths,)
    return len(number) in lengths and number.startswith(prefix)


def is_american_express_card(number: str) -> bool:
    return check_length_and_prefix(number, 15, ("34", "37"))


def is_visa_card(number: str) -> bool:
    return check_length_and_prefix(number, (13, 16), "4")


def is_master_card(number: str) -> bool:
    return check_length_and_prefix(number, 16, ("51", "52", "53", "54", "55"))


def have_valid_checksum(number: str) -> bool:
    sum = 0
    for i, c in enumerate(reversed(number)):
        digit = int(c)
        if i % 2 == 0:
            sum += digit
        else:
            digit *= 2
            sum += (digit) % 10 + (digit) // 10
    return sum % 10 == 0


def card_type(number: str) -> str:
    if have_valid_checksum(number):
        match number:
            case n if is_master_card(n):
                return "MASTERCARD"
            case n if is_american_express_card(n):
                return "AMEX"
            case n if is_visa_card(n):
                return "VISA"
    return "INVALID"


number = input("Number: ")
print(card_type(number))
