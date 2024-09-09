unsigned char reverse_bits(unsigned char octet)
{
    return ((octet & 0b10000000) >> 7) |
           ((octet & 0b01000000) >> 5) |
           ((octet & 0b00100000) >> 3) |
           ((octet & 0b00010000) >> 1) |
           ((octet & 0b00001000) << 1) |
           ((octet & 0b00000100) << 3) |
           ((octet & 0b00000010) << 5) |
           ((octet & 0b00000001) << 7);
}