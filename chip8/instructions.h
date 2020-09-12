#pragma once

#include <string>
#include <sstream>
#include <cstdlib>

#include "types.h"
#include "reg.h"
#include "instruction.h"
#include "cpu.h"
#include "memory.h"
#include "graphics.h"

namespace instructions
{
	class cls final : public instruction
	{
		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;
	};

	class ret final : public instruction
	{
		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;
	};

	class sys final : public instruction
	{
	public:
		sys(word address);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		word address_;
	};

	class jp_addr final : public instruction
	{
	public:
		jp_addr(word address);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		word address_;
	};

	class jp_v0_addr final : public instruction
	{
	public:
		jp_v0_addr(word address);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		word address_;
	};

	class call final : public instruction
	{
	public:
		call(word address);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		word address_;
	};

	class se_reg_byte final : public instruction
	{
	public:
		se_reg_byte(reg reg, byte byte);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
		byte byte_;
	};

	class se_reg_reg final : public instruction
	{
	public:
		se_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class sne_reg_byte final : public instruction
	{
	public:
		sne_reg_byte(reg reg, byte byte);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
		byte byte_;
	};

	class sne_reg_reg final : public instruction
	{
	public:
		sne_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class ld_reg_byte final : public instruction
	{
	public:
		ld_reg_byte(reg reg, byte byte);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
		byte byte_;
	};

	class ld_reg_reg final : public instruction
	{
	public:
		ld_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class ld_i_addr final : public instruction
	{
	public:
		ld_i_addr(word address);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		word address_;
	};

	class ld_reg_dt final : public instruction
	{
	public:
		ld_reg_dt(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_reg_k final : public instruction
	{
	public:
		ld_reg_k(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_dt_reg final : public instruction
	{
	public:
		ld_dt_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_st_reg final : public instruction
	{
	public:
		ld_st_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_f_reg final : public instruction
	{
	public:
		ld_f_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_b_reg final : public instruction
	{
	public:
		ld_b_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_mem_reg final : public instruction
	{
	public:
		ld_mem_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class ld_reg_mem final : public instruction
	{
	public:
		ld_reg_mem(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class add_reg_byte final : public instruction
	{
	public:
		add_reg_byte(reg reg, byte byte);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
		byte byte_;
	};

	class add_reg_reg final : public instruction
	{
	public:
		add_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class add_i_reg final : public instruction
	{
	public:
		add_i_reg(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class or_reg_reg final : public instruction
	{
	public:
		or_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class and_reg_reg final : public instruction
	{
	public:
		and_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class xor_reg_reg final : public instruction
	{
	public:
		xor_reg_reg(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class sub final : public instruction
	{
	public:
		sub(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class subn final : public instruction
	{
	public:
		subn(reg reg_1, reg reg_2);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
	};

	class shr final : public instruction
	{
	public:
		shr(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class shl final : public instruction
	{
	public:
		shl(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class rnd final : public instruction
	{
	public:
		rnd(reg reg, byte byte);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
		byte byte_;
	};

	class drw final : public instruction
	{
	public:
		drw(reg reg_1, reg reg_2, byte nibble);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_1_;
		reg reg_2_;
		byte nibble_;
	};

	class skp final : public instruction
	{
	public:
		skp(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class sknp final : public instruction
	{
	public:
		sknp(reg reg);

		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;

	private:
		reg reg_;
	};

	class invalid final : public instruction
	{
	public:
		void execute(cpu& cpu, memory& memory, graphics& graphics) const override;
		std::string to_string() const override;
	};
}