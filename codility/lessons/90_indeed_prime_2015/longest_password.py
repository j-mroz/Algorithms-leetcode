def is_letter(x):
    return ord('a') <= ord(x) <= ord('z') or ord('A') <= ord(x) <= ord('Z')

def is_digit(x):
    return ord('0') <= ord(x) <= ord('9')

def solution(S):
    words = S.split(" ")

    longest_valid = 0

    for word in words:
        letters_count, digits_count = 0, 0
        invalid = False
        for symbol in word:
            if is_letter(symbol):
                letters_count += 1
            elif is_digit(symbol):
                digits_count += 1
            else:
                invalid = True
                break
        if not invalid and letters_count % 2 == 0 and digits_count % 2 == 1:
            longest_valid = max(longest_valid, len(word))

    if not longest_valid:
        return -1
    return longest_valid
