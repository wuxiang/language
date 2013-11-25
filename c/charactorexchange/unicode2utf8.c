#include <iostream>
#include <deque>

std::deque<int> unicode_to_utf8(int charcode)
{
    std::deque<int> d;
    if (charcode < 128)
    {
        d.push_back(charcode);
    }
    else
    {
        int first_bits = 6; 
        const int other_bits = 6;
        int first_val = 0xC0;
        int t = 0;
        while (charcode >= (1 << first_bits))
        {
            {
                t = 128 | (charcode & ((1 << other_bits)-1));
                charcode >>= other_bits;
                first_val |= 1 << (first_bits);
                first_bits--;
            }
            d.push_front(t);
        }
        t = first_val | charcode;
        d.push_front(t);
    }
    return d;
}


int utf8_to_unicode(std::deque<int> &coded)
{
    int charcode = 0;
    int t = coded.front();
    coded.pop_front();
    if (t < 128)
    {
        return t;
    }
    int high_bit_mask = (1 << 6) -1;
    int high_bit_shift = 0;
    int total_bits = 0;
    const int other_bits = 6;
    while((t & 0xC0) == 0xC0)
    {
        t <<= 1;
        t &= 0xff;
        total_bits += 6;
        high_bit_mask >>= 1; 
        high_bit_shift++;
        charcode <<= other_bits;
        charcode |= coded.front() & ((1 << other_bits)-1);
        coded.pop_front();
    } 
    charcode |= ((t >> high_bit_shift) & high_bit_mask) << total_bits;
    return charcode;
}

int main()
{
    int charcode; 

    for(;;)
    {
        std::cout << "Enter unicode value:" << std::endl;
        std::cin >> charcode; 
        auto x = unicode_to_utf8(charcode);
        for(auto c : x)
        {
            std::cout << "\\x" << std::hex << c << " ";
        }
        std::cout << std::endl;
        int c = utf8_to_unicode(x);
        std::cout << "reversed:" << std::dec << c << std::hex << " in hex:" << c << std::endl;
    }
}