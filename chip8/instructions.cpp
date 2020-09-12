#include "instructions.h"

static constexpr size_t BITS_IN_BYTE = 8;

void instructions::cls::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    graphics.clear();
    graphics.draw();
}

std::string instructions::cls::to_string() const
{
    return "cls";
}

void instructions::ret::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.pc = memory.pop_address();
}

std::string instructions::ret::to_string() const
{
    return "ret";
}

instructions::sys::sys(word address)
    : address_{ address }
{
}

void instructions::sys::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    // ignored
}

std::string instructions::sys::to_string() const
{
    std::stringstream ss;
    ss << "sys " << std::hex << address_;

    return ss.str();
}

instructions::jp_addr::jp_addr(word address)
    : address_{ address }
{
}

void instructions::jp_addr::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.pc = address_;
}

std::string instructions::jp_addr::to_string() const
{
    std::stringstream ss;
    ss << "jp " << std::hex << address_;

    return ss.str();
}

instructions::jp_v0_addr::jp_v0_addr(word address)
    : address_{ address }
{
}

void instructions::jp_v0_addr::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.pc = cpu.gp_regs.v0 + address_;
}

std::string instructions::jp_v0_addr::to_string() const
{
    std::stringstream ss;
    ss << "jp v0, " << std::hex << address_;

    return ss.str();
}

instructions::call::call(word address)
    : address_{ address }
{
}

void instructions::call::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    memory.push_address(cpu.pc);
    cpu.pc = address_;
}

std::string instructions::call::to_string() const
{
    std::stringstream ss;
    ss << "call " << std::hex << address_;

    return ss.str();
}

instructions::se_reg_byte::se_reg_byte(reg reg, byte byte)
    : reg_{ reg }, byte_{ byte }
{
}

void instructions::se_reg_byte::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    if (cpu.gp_regs.arr[static_cast<size_t>(reg_)] == byte_) {
        cpu.pc += sizeof(word);
    }
}

std::string instructions::se_reg_byte::to_string() const
{
    std::stringstream ss;
    ss << "se " << reg_ << ", " << std::hex << static_cast<int>(byte_);

    return ss.str();
}

instructions::se_reg_reg::se_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::se_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    if (cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] ==
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)]) {
        cpu.pc += 2;
    }
}

std::string instructions::se_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "se " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::sne_reg_byte::sne_reg_byte(reg reg, byte byte)
    : reg_{ reg }, byte_{ byte }
{
}

void instructions::sne_reg_byte::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    if (cpu.gp_regs.arr[static_cast<size_t>(reg_)] != byte_) {
        cpu.pc += sizeof(word);
    }
}

std::string instructions::sne_reg_byte::to_string() const
{
    std::stringstream ss;
    ss << "se " << reg_ << ", " << std::hex << static_cast<int>(byte_);

    return ss.str();
}

instructions::sne_reg_reg::sne_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::sne_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    if (cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] !=
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)]) {
        cpu.pc += 2;
    }
}

std::string instructions::sne_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "se " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::add_reg_byte::add_reg_byte(reg reg, byte byte)
    : reg_{ reg }, byte_{ byte }
{
}

void instructions::add_reg_byte::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_)] += byte_;
}

std::string instructions::add_reg_byte::to_string() const
{
    std::stringstream ss;
    ss << "add " << reg_ << ", " << std::hex << static_cast<int>(byte_);

    return ss.str();
}

instructions::add_reg_reg::add_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::add_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto sum = static_cast<int>(cpu.gp_regs.arr[static_cast<size_t>(reg_1_)]) +
        static_cast<int>(cpu.gp_regs.arr[static_cast<size_t>(reg_2_)]);

    cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] = sum % 256;
    cpu.gp_regs.vf = sum / 256;
}

std::string instructions::add_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "add " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::add_i_reg::add_i_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::add_i_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.i += cpu.gp_regs.arr[static_cast<size_t>(reg_)];
}

std::string instructions::add_i_reg::to_string() const
{
    std::stringstream ss;
    ss << "add i, " << reg_;

    return ss.str();
}

instructions::or_reg_reg::or_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::or_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] |=
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];
}

std::string instructions::or_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "or " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::and_reg_reg::and_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::and_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] &=
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];
}

std::string instructions::and_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "and " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::xor_reg_reg::xor_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::xor_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] ^=
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];
}

std::string instructions::xor_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "xor " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::sub::sub(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::sub::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto &reg_1 = cpu.gp_regs.arr[static_cast<size_t>(reg_1_)];
    auto &reg_2 = cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];

    cpu.gp_regs.vf = static_cast<byte>(reg_1 > reg_2);

    reg_1 -= reg_2;
}

std::string instructions::sub::to_string() const
{
    std::stringstream ss;
    ss << "sub " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::subn::subn(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::subn::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto& reg_1 = cpu.gp_regs.arr[static_cast<size_t>(reg_1_)];
    auto& reg_2 = cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];

    cpu.gp_regs.vf = static_cast<byte>(reg_2 > reg_1);

    reg_1 = reg_2 - reg_1;
}

std::string instructions::subn::to_string() const
{
    std::stringstream ss;
    ss << "subn " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::shr::shr(reg reg)
    : reg_{ reg }
{
}

void instructions::shr::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto& reg = cpu.gp_regs.arr[static_cast<size_t>(reg_)];

    cpu.gp_regs.vf = reg & 1;
    reg >>= 1;
}

std::string instructions::shr::to_string() const
{
    std::stringstream ss;
    ss << "shr " << reg_;

    return ss.str();
}

instructions::shl::shl(reg reg)
    : reg_{ reg }
{
}

void instructions::shl::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto& reg = cpu.gp_regs.arr[static_cast<size_t>(reg_)];

    cpu.gp_regs.vf = reg >> 7;
    reg <<= 1;
}

std::string instructions::shl::to_string() const
{
    std::stringstream ss;
    ss << "shl " << reg_;

    return ss.str();
}

instructions::rnd::rnd(reg reg, byte byte)
    : reg_{ reg }, byte_{ byte }
{
}

void instructions::rnd::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_)] = (std::rand() % 256) & byte_;
}

std::string instructions::rnd::to_string() const
{
    std::stringstream ss;
    ss << "rnd " << reg_ << ", " << std::hex << static_cast<int>(byte_);

    return ss.str();
}

instructions::drw::drw(reg reg_1, reg reg_2, byte nibble)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }, nibble_{ nibble }
{
}

void instructions::drw::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto x = cpu.gp_regs.arr[static_cast<size_t>(reg_1_)];
    auto y = cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];

    cpu.gp_regs.vf = 0;

    byte (&bitmap)[PIXELS] = graphics.get_bitmap();

    for (auto i = 0; i < nibble_; i++) {
        auto sprite = memory.get<byte>(cpu.i + i);

        for (auto j = 0; j < BITS_IN_BYTE; j++) {
            auto index = (y + i) * PIXEL_WIDTH + (x + j);

            auto before = bitmap[index];
            bitmap[index] ^= (sprite >> (BITS_IN_BYTE - j - 1)) & 1;

            cpu.gp_regs.vf |= (before == 1) && (bitmap[index] == 0);
        }
    }

    graphics.draw();
}

std::string instructions::drw::to_string() const
{
    std::stringstream ss;
    ss << "drw " << reg_1_ << ", " << reg_2_ << ", " << std::hex << static_cast<int>(nibble_);

    return ss.str();
}

instructions::skp::skp(reg reg)
    : reg_{ reg }
{
}

void instructions::skp::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto reg_value = cpu.gp_regs.arr[static_cast<size_t>(reg_)];

    if (graphics.is_pressed(reg_value)) {
        cpu.pc += sizeof(word);
    }
}

std::string instructions::skp::to_string() const
{
    std::stringstream ss;
    ss << "skp " << reg_;

    return ss.str();
}

instructions::sknp::sknp(reg reg)
    : reg_{ reg }
{
}

void instructions::sknp::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    auto reg_value = cpu.gp_regs.arr[static_cast<size_t>(reg_)];

    if (!graphics.is_pressed(reg_value)) {
        cpu.pc += sizeof(word);
    }
}

std::string instructions::sknp::to_string() const
{
    std::stringstream ss;
    ss << "sknp " << reg_;

    return ss.str();
}

instructions::ld_reg_byte::ld_reg_byte(reg reg, byte byte)
    : reg_{ reg }, byte_{ byte }
{
}

void instructions::ld_reg_byte::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_)] = byte_;
}

std::string instructions::ld_reg_byte::to_string() const
{
    std::stringstream ss;
    ss << "ld " << reg_ << ", " << std::hex << static_cast<int>(byte_);

    return ss.str();
}

instructions::ld_reg_reg::ld_reg_reg(reg reg_1, reg reg_2)
    : reg_1_{ reg_1 }, reg_2_{ reg_2 }
{
}

void instructions::ld_reg_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_1_)] =
        cpu.gp_regs.arr[static_cast<size_t>(reg_2_)];
}

std::string instructions::ld_reg_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld " << reg_1_ << ", " << reg_2_;

    return ss.str();
}

instructions::ld_i_addr::ld_i_addr(word address)
    : address_{ address }
{
}

void instructions::ld_i_addr::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.i = address_;
}

std::string instructions::ld_i_addr::to_string() const
{
    std::stringstream ss;
    ss << "ld i, " << std::hex << address_;

    return ss.str();
}

instructions::ld_reg_dt::ld_reg_dt(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_reg_dt::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.gp_regs.arr[static_cast<size_t>(reg_)] = cpu.dt;
}

std::string instructions::ld_reg_dt::to_string() const
{
    std::stringstream ss;
    ss << "ld " << reg_ << ", dt";
    
    return ss.str();
}

instructions::ld_reg_k::ld_reg_k(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_reg_k::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    try {
        cpu.gp_regs.arr[static_cast<size_t>(reg_)] = graphics.get_pressed_key();
    } catch (...) {
        cpu.pc -= sizeof(word);
    }
}

std::string instructions::ld_reg_k::to_string() const
{
    std::stringstream ss;
    ss << "ld " << reg_ << ", k";

    return ss.str();
}

instructions::ld_dt_reg::ld_dt_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_dt_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.dt = cpu.gp_regs.arr[static_cast<size_t>(reg_)];
}

std::string instructions::ld_dt_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld dt, " << reg_;

    return ss.str();
}

instructions::ld_st_reg::ld_st_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_st_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.st = cpu.gp_regs.arr[static_cast<size_t>(reg_)];
}

std::string instructions::ld_st_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld st, " << reg_;

    return ss.str();
}

instructions::ld_f_reg::ld_f_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_f_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    cpu.i = cpu.gp_regs.arr[static_cast<size_t>(reg_)] * FONT_SPRITE_SIZE;
}

std::string instructions::ld_f_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld f, " << reg_;

    return ss.str();
}

instructions::ld_b_reg::ld_b_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_b_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    byte reg_value = cpu.gp_regs.arr[static_cast<size_t>(reg_)];

    memory.set<byte>(cpu.i, reg_value / 100);
    memory.set<byte>(cpu.i + 1, (reg_value / 10) % 10);
    memory.set<byte>(cpu.i + 2, reg_value % 10);
}

std::string instructions::ld_b_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld b, " << reg_;

    return ss.str();
}

instructions::ld_mem_reg::ld_mem_reg(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_mem_reg::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    for (auto offset = 0; offset <= static_cast<size_t>(reg_); offset++) {
        memory.set<byte>(cpu.i + offset, cpu.gp_regs.arr[offset]);
    }
}

std::string instructions::ld_mem_reg::to_string() const
{
    std::stringstream ss;
    ss << "ld [i], " << reg_;

    return ss.str();
}

instructions::ld_reg_mem::ld_reg_mem(reg reg)
    : reg_{ reg }
{
}

void instructions::ld_reg_mem::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    for (auto offset = 0; offset <= static_cast<size_t>(reg_); offset++) {
        cpu.gp_regs.arr[offset] = memory.get<byte>(cpu.i + offset);
    }
}

std::string instructions::ld_reg_mem::to_string() const
{
    std::stringstream ss;
    ss << "ld " << reg_ << ", [i]";

    return ss.str();
}

void instructions::invalid::execute(cpu& cpu, memory& memory, graphics& graphics) const
{
    throw std::runtime_error("Invalid instruction.");
}

std::string instructions::invalid::to_string() const
{
    return "invalid";
}