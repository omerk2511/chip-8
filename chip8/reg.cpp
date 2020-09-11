#include "reg.h"

std::ostream& operator<<(std::ostream& os, const reg reg)
{
    switch (reg) {
    case reg::v0: os << std::string{ "v0" }; break;
    case reg::v1: os << std::string{ "v1" }; break;
    case reg::v2: os << std::string{ "v2" }; break;
    case reg::v3: os << std::string{ "v3" }; break;
    case reg::v4: os << std::string{ "v4" }; break;
    case reg::v5: os << std::string{ "v5" }; break;
    case reg::v6: os << std::string{ "v6" }; break;
    case reg::v7: os << std::string{ "v7" }; break;
    case reg::v8: os << std::string{ "v8" }; break;
    case reg::v9: os << std::string{ "v9" }; break;
    case reg::va: os << std::string{ "va" }; break;
    case reg::vb: os << std::string{ "vb" }; break;
    case reg::vc: os << std::string{ "vc" }; break;
    case reg::vd: os << std::string{ "vd" }; break;
    case reg::ve: os << std::string{ "ve" }; break;
    case reg::vf: os << std::string{ "vf" }; break;
    }

    return os;
}