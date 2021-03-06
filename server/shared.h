/*
 * (c) 2008-2009 Adam Lackorzynski <adam@os.inf.tu-dresden.de>
 *     economic rights: Technische Universität Dresden (Germany)
 *
 * This file is part of TUD:OS and distributed under the terms of the
 * GNU General Public License 2.
 * Please see the COPYING-GPL-2 file for details.
 */

#pragma once

#define ENCRYPTION_SERVER_NAME "encr_server"


namespace Opcode {
	enum Opcodes {
		func_encrypt, func_decrypt
	};
};

namespace Protocol {
	enum Protocols {
		Encryption
	};
};
