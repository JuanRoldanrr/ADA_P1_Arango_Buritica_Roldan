#ifndef PICOSHA2_H
#define PICOSHA2_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <vector>
#include <cstdint> // Necesario para std::uint32_t

namespace picosha2 {
    typedef std::uint32_t word_t; // Cambiar 'unsigned long' por 'std::uint32_t'
    typedef unsigned char byte_t;

static const size_t k_digest_size = 32;

namespace detail {
inline byte_t mask_8bit(byte_t x) { return x & 0xff; }
inline word_t mask_32bit(word_t x) { return x & 0xffffffff; }

const word_t add_constant[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

const word_t initial_message_digest[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

inline word_t ch(word_t x, word_t y, word_t z) { return (x & y) ^ ((~x) & z); }
inline word_t maj(word_t x, word_t y, word_t z) { return (x & y) ^ (x & z) ^ (y & z); }
inline word_t rotr(word_t x, std::size_t n) { return mask_32bit((x >> n) | (x << (32 - n))); }
inline word_t bsig0(word_t x) { return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22); }
inline word_t bsig1(word_t x) { return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25); }
inline word_t shr(word_t x, std::size_t n) { return x >> n; }
inline word_t ssig0(word_t x) { return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3); }
inline word_t ssig1(word_t x) { return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10); }

template <typename RaIter1, typename RaIter2>
void hash256_block(RaIter1 message_digest, RaIter2 first, RaIter2 last) {
    (void)last;
    word_t w[64];
    std::fill(w, w + 64, word_t(0));
    for (std::size_t i = 0; i < 16; ++i) {
        w[i] = (static_cast<word_t>(mask_8bit(*(first + i * 4))) << 24) |
               (static_cast<word_t>(mask_8bit(*(first + i * 4 + 1))) << 16) |
               (static_cast<word_t>(mask_8bit(*(first + i * 4 + 2))) << 8) |
               (static_cast<word_t>(mask_8bit(*(first + i * 4 + 3))));
    }
    for (std::size_t i = 16; i < 64; ++i) {
        w[i] = mask_32bit(ssig1(w[i - 2]) + w[i - 7] + ssig0(w[i - 15]) + w[i - 16]);
    }

    word_t a = *message_digest;
    word_t b = *(message_digest + 1);
    word_t c = *(message_digest + 2);
    word_t d = *(message_digest + 3);
    word_t e = *(message_digest + 4);
    word_t f = *(message_digest + 5);
    word_t g = *(message_digest + 6);
    word_t h = *(message_digest + 7);

    for (std::size_t i = 0; i < 64; ++i) {
        word_t temp1 = mask_32bit(h + bsig1(e) + ch(e, f, g) + add_constant[i] + w[i]);
        word_t temp2 = mask_32bit(bsig0(a) + maj(a, b, c));
        h = g; g = f; f = e; e = mask_32bit(d + temp1);
        d = c; c = b; b = a; a = mask_32bit(temp1 + temp2);
    }
    *message_digest = mask_32bit(*message_digest + a);
    *(message_digest + 1) = mask_32bit(*(message_digest + 1) + b);
    *(message_digest + 2) = mask_32bit(*(message_digest + 2) + c);
    *(message_digest + 3) = mask_32bit(*(message_digest + 3) + d);
    *(message_digest + 4) = mask_32bit(*(message_digest + 4) + e);
    *(message_digest + 5) = mask_32bit(*(message_digest + 5) + f);
    *(message_digest + 6) = mask_32bit(*(message_digest + 6) + g);
    *(message_digest + 7) = mask_32bit(*(message_digest + 7) + h);
}
} // namespace detail

template <typename InIter>
void output_hex(InIter first, InIter last, std::ostream& os) {
    os.setf(std::ios::hex, std::ios::basefield);
    while (first != last) {
        os.width(2);
        os.fill('0');
        os << static_cast<unsigned int>(*first);
        ++first;
    }
    os.setf(std::ios::dec, std::ios::basefield);
}

class hash256_one_by_one {
public:
    hash256_one_by_one() { init(); }
    void init() {
        buffer_.clear();
        data_length_ = 0;
        std::copy(detail::initial_message_digest, detail::initial_message_digest + 8, h_);
    }

    template <typename RaIter>
    void process(RaIter first, RaIter last) {
        data_length_ += std::distance(first, last);
        std::copy(first, last, std::back_inserter(buffer_));
        std::size_t i = 0;
        for (; i + 64 <= buffer_.size(); i += 64) {
            detail::hash256_block(h_, buffer_.begin() + i, buffer_.begin() + i + 64);
        }
        buffer_.erase(buffer_.begin(), buffer_.begin() + i);
    }

    void finish() {
        byte_t temp[64];
        std::fill(temp, temp + 64, byte_t(0));
        std::size_t remains = buffer_.size();
        std::copy(buffer_.begin(), buffer_.end(), temp);
        temp[remains] = 0x80;

        if (remains > 55) {
            detail::hash256_block(h_, temp, temp + 64);
            std::fill(temp, temp + 64, byte_t(0));
        }

        std::uint64_t bit_len = data_length_ * 8;
        for (int i = 0; i < 8; ++i) {
            temp[63 - i] = static_cast<byte_t>(bit_len >> (i * 8));
        }
        detail::hash256_block(h_, temp, temp + 64);
    }

    template <typename OutIter>
    void get_hash_bytes(OutIter first, OutIter last) const {
        for (const word_t* iter = h_; iter != h_ + 8; ++iter) {
            for (std::size_t i = 0; i < 4 && first != last; ++i) {
                *(first++) = detail::mask_8bit(static_cast<byte_t>(*iter >> (24 - 8 * i)));
            }
        }
    }

private:
    std::vector<byte_t> buffer_;
    std::uint64_t data_length_;
    word_t h_[8];
};

template <typename InIter>
std::string hash256_hex_string(InIter first, InIter last) {
    hash256_one_by_one hasher;
    hasher.process(first, last);
    hasher.finish();
    byte_t hashed[k_digest_size];
    hasher.get_hash_bytes(hashed, hashed + k_digest_size);
    std::ostringstream oss;
    output_hex(hashed, hashed + k_digest_size, oss);
    return oss.str();
}

inline std::string hash256_hex_string(const std::string& src) {
    return hash256_hex_string(src.begin(), src.end());
}
} // namespace picosha2

#endif