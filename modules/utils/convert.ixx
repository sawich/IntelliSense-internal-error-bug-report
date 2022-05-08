export module pc.utils.convert;

export auto lodword(auto a) noexcept { return (DWORD)(((int64_t)(a)) & 0x00000000FFFFFFFF); }
export auto hidword(auto a) noexcept { return (DWORD)(((int64_t)(a)) >> 32); }
