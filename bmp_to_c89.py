import struct
import sys

def read_bmp_1bit(path):
    with open(path, "rb") as f:
        data = f.read()

    if data[0:2] != b'BM':
        raise ValueError("Not a BMP file")

    pixel_offset = struct.unpack_from("<I", data, 10)[0]
    width  = struct.unpack_from("<I", data, 18)[0]
    height = struct.unpack_from("<I", data, 22)[0]
    bpp    = struct.unpack_from("<H", data, 28)[0]

    if bpp != 1:
        raise ValueError("BMP is not 1-bit")

    row_bytes = ((width + 31) // 32) * 4

    bits = []
    for y in range(height):
        row_start = pixel_offset + (height - 1 - y) * row_bytes
        row = data[row_start:row_start + row_bytes]

        for x in range(width):
            byte = row[x >> 3]
            bit  = 7 - (x & 7)
            #bits.append(1 - ((byte >> bit) & 1))
            bits.append((byte >> bit) & 1)  # 0 = black, 1 = white

    return width, height, bits

def pack_bits(bits):
    out = []
    byte = 0
    count = 0

    for b in bits:
        byte = (byte << 1) | b
        count += 1

        if count == 8:
            out.append(byte)
            byte = 0
            count = 0

    if count != 0:
        byte <<= (8 - count)
        out.append(byte)

    return out

def emit_c_array(name, width, height, data):
    print("/* 1-bit bitmap, packed, row-major */")
    print("/* width=%d, height=%d */" % (width, height))
    print("static const unsigned char %s[] = {" % name)

    for i, b in enumerate(data):
        if i % 12 == 0:
            print("    ", end="")
        print("0x%02X" % b, end="")
        if i != len(data) - 1:
            print(", ", end="")
        if i % 12 == 11:
            print()

    if len(data) % 12 != 0:
        print()

    print("};")
    print("static const unsigned int %s_width  = %d;" % (name, width))
    print("static const unsigned int %s_height = %d;" % (name, height))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: bmp1_to_c89_hex.py <font.bmp> <array_name>")
        sys.exit(1)

    w, h, bits = read_bmp_1bit(sys.argv[1])
    packed = pack_bits(bits)
    emit_c_array(sys.argv[2], w, h, packed)
