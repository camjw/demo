#include <demo/bitmask.hpp>

Bitmask::Bitmask()
    : bits(0)
{
}

void Bitmask::set_mask(Bitmask& other)
{
    bits = other.get_mask();
}

uint32_t Bitmask::get_mask() const
{
    return bits;
}

bool Bitmask::get_bit(int pos) const
{
    return (bits & (1 << pos)) != 0;
}

void Bitmask::set_bit(int pos, bool on)
{
    if (on)
    {
        set_bit(pos);
    }
    else
    {
        clear_bit(pos);
    }
}

void Bitmask::set_bit(int pos)
{
    bits = bits | 1 << pos;
}

void Bitmask::clear_bit(int pos)
{
    bits = bits & ~(1 << pos);
}

void Bitmask::clear()
{
    bits = 0;
}
