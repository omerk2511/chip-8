#include "parsing.h"

std::unique_ptr<instruction> parsing::parse_instruction(const word opcode)
{
    switch (opcode >> 12) {
    case 0x00: {
        if ((opcode & 0xfff) == 0xe0)
            return std::make_unique<instructions::cls>();
        else if ((opcode & 0xfff) == 0xee)
            return std::make_unique<instructions::ret>();
        else
            return std::make_unique<instructions::sys>(opcode & 0xfff);
    }

    case 0x01: {
        return std::make_unique<instructions::jp_addr>(opcode & 0xfff);
    }

    case 0x02: {
        return std::make_unique<instructions::call>(opcode & 0xfff);
    }

    case 0x03: {
        return std::make_unique<instructions::se_reg_byte>(
            static_cast<reg>((opcode >> 8) & 0xf),
            opcode & 0xff
        );
    }

    case 0x04: {
        return std::make_unique<instructions::sne_reg_byte>(
            static_cast<reg>((opcode >> 8) & 0xf),
            opcode & 0xff
        );
    }

    case 0x05: {
        return std::make_unique<instructions::se_reg_reg>(
            static_cast<reg>((opcode >> 8) & 0xf),
            static_cast<reg>((opcode >> 4) & 0xf)
        );
    }

    case 0x06: {
        return std::make_unique<instructions::ld_reg_byte>(
            static_cast<reg>((opcode >> 8) & 0xf),
            opcode & 0xff
        );
    }

    case 0x07: {
        return std::make_unique<instructions::add_reg_byte>(
            static_cast<reg>((opcode >> 8) & 0xf),
            opcode & 0xff
        );
    }

    case 0x08: {
        switch (opcode & 0xf) {
        case 0x00: {
            return std::make_unique<instructions::ld_reg_reg>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x01: {
            return std::make_unique<instructions::or_reg_reg>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x02: {
            return std::make_unique<instructions::and_reg_reg>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x03: {
            return std::make_unique<instructions::xor_reg_reg>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x04: {
            return std::make_unique<instructions::add_reg_reg>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x05: {
            return std::make_unique<instructions::sub>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x06: {
            return std::make_unique<instructions::shr>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x07: {
            return std::make_unique<instructions::subn>(
                static_cast<reg>((opcode >> 8) & 0xf),
                static_cast<reg>((opcode >> 4) & 0xf)
            );
        }

        case 0x0e: {
            return std::make_unique<instructions::shl>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        default: {
            break;
        }
        }

        break;
    }

    case 0x09: {
        return std::make_unique<instructions::sne_reg_reg>(
            static_cast<reg>((opcode >> 8) & 0xf),
            static_cast<reg>((opcode >> 4) & 0xf)
        );
    }

    case 0x0a: {
        return std::make_unique<instructions::ld_i_addr>(opcode & 0xfff);
    }

    case 0x0b: {
        return std::make_unique<instructions::jp_v0_addr>(opcode & 0xfff);
    }

    case 0x0c: {
        return std::make_unique<instructions::rnd>(
            static_cast<reg>((opcode >> 8) & 0xf),
            opcode & 0xff
        );
    }

    case 0x0d: {
        return std::make_unique<instructions::drw>(
            static_cast<reg>((opcode >> 8) & 0xf),
            static_cast<reg>((opcode >> 4) & 0xf),
            opcode & 0xf
        );
    }

    case 0x0e: {
        if ((opcode & 0xff) == 0x9e)
            return std::make_unique<instructions::skp>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        else if ((opcode & 0xff) == 0xa1)
            return std::make_unique<instructions::sknp>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );

        break;
    }

    case 0x0f: {
        switch (opcode & 0xff) {
        case 0x07: {
            return std::make_unique<instructions::ld_reg_dt>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x0a: {
            return std::make_unique<instructions::ld_reg_k>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x15: {
            return std::make_unique<instructions::ld_dt_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x18: {
            return std::make_unique<instructions::ld_st_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x1e: {
            return std::make_unique<instructions::add_i_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x29: {
            return std::make_unique<instructions::ld_f_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x33: {
            return std::make_unique<instructions::ld_b_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x55: {
            return std::make_unique<instructions::ld_mem_reg>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        case 0x65: {
            return std::make_unique<instructions::ld_reg_mem>(
                static_cast<reg>((opcode >> 8) & 0xf)
            );
        }

        default: {
            break;
        }
        }

        break;
    }
    }

    return std::make_unique<instructions::invalid>();
}