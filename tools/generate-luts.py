# SPDX-FileCopyrightText: 2026 Joey Riches <josephriches@gmail.com>
# SPDX-License-Identifier: GPL-2.0-or-later
#
# Developer only script that exists to help verify the look up tables
# used for XML character classification are valid. If the LUTs need to
# changed for any reason in the future, the script exists to more easily
# build new LUTs.

def build_utf8_len_and_mask():
    utf8_len = [0] * 256
    utf8_mask = [0] * 256

    for b in range(256):
        if b < 0x80:
            continue
        elif (b & 0xE0) == 0xC0:
            utf8_len[b], utf8_mask[b] = 2, 0x1F
        elif (b & 0xF0) == 0xE0:
            utf8_len[b], utf8_mask[b] = 3, 0x0F
        elif (b & 0xF8) == 0xF0:
            utf8_len[b], utf8_mask[b] = 4, 0x07
        elif (b & 0xFC) == 0xF8:
            utf8_len[b], utf8_mask[b] = 5, 0x03
        elif (b & 0xFE) == 0xFC:
            utf8_len[b], utf8_mask[b] = 6, 0x01

    return utf8_len, utf8_mask


def build_char_class():
    B_INVALID   = 0x001
    B_NEWLINE   = 0x002
    B_UTF8      = 0x004
    B_WS        = 0x008
    B_CDATA     = 0x010
    B_TAG       = 0x020
    B_APOS      = 0x040
    B_QUOT      = 0x080
    B_RBRACKET  = 0x100

    # Every byte with the high bit set is a UTF-8 byte (lead or continuation).
    table = [B_UTF8] * 256

    for i in range(0x00, 0x80):
        table[i] = 0

    table[0x00] = B_INVALID
    table[0x09] = B_WS
    table[0x0A] = B_NEWLINE
    table[0x0D] = B_WS
    table[0x20] = B_WS

    table[0x22] = B_QUOT
    table[0x27] = B_APOS

    table[0x26] = B_CDATA
    table[0x3C] = B_CDATA

    table[0x2F] = B_TAG
    table[0x3D] = B_TAG
    table[0x3E] = B_TAG

    table[0x5D] = B_RBRACKET

    table[0xFE] = B_INVALID
    table[0xFF] = B_INVALID

    return table


def format_array(name, arr, ctype="unsigned char", fmt=str):
    """Render into a C-like array"""

    lines = [f"static const {ctype} {name}[256] = {{"]
    for i in range(0, 256, 16):
        chunk = ", ".join(fmt(x) for x in arr[i:i+16])
        lines.append("\t" + chunk + ",")
    lines[-1] = lines[-1].rstrip(",")
    lines.append("};")
    return "\n".join(lines)


def hex_mask(x):
    return "0" if x == 0 else f"0x{x:02X}"


def main():
    chars = build_char_class()
    utf8_len, utf8_mask = build_utf8_len_and_mask()

    print(format_array("utf8_len", utf8_len))
    print()
    print(format_array("utf8_mask", utf8_mask, fmt=hex_mask))
    print()
    print(format_array("char_class", chars, ctype="unsigned short"))


if __name__ == "__main__":
    main()
