void	print_bits(unsigned char octet)
{
    char bits[8] = {
        ((octet & 0b10000000) >> 7) + '0',
        ((octet & 0b01000000) >> 6) + '0', 
        ((octet & 0b00100000) >> 5) + '0', 
        ((octet & 0b00010000) >> 4) + '0', 
        ((octet & 0b00001000) >> 3) + '0', 
        ((octet & 0b00000100) >> 2) + '0', 
        ((octet & 0b00000010) >> 1) + '0', 
        ((octet & 0b00000001) >> 0) + '0'
    };
    write(1, bits, 8); 
}