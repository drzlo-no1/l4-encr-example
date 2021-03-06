
#include <l4/sys/err.h>
#include <l4/sys/types.h>
#include <l4/re/env>
#include <l4/re/util/cap_alloc>
#include <l4/cxx/ipc_stream>

#include <stdio.h>

#include "shared.h"


static int call_encrypt(L4::Cap<void> const &server, unsigned char *in_buf, unsigned long size, unsigned char *out_buf) {

	L4::Ipc::Iostream s(l4_utcb());

	if(in_buf == NULL || size == 0 || size > (L4_UTCB_GENERIC_DATA_SIZE-2)*sizeof(l4_umword_t) || out_buf == NULL)
		return -L4_EINVAL;

	s << l4_umword_t(Opcode::func_encrypt) << L4::Ipc::Buf_cp_out<unsigned char>(in_buf, size);
	int ret = l4_error(s.call(server.cap(), Protocol::Encryption));
	if(ret != L4_EOK)
		return ret;
	s >> L4::Ipc::Buf_cp_in<unsigned char>(out_buf, size);
	return L4_EOK;
}

static int call_decrypt(L4::Cap<void> const &server, unsigned char *in_buf, unsigned long size, unsigned char *out_buf) {

	L4::Ipc::Iostream s(l4_utcb());

	if(in_buf == NULL || size == 0 || size > (L4_UTCB_GENERIC_DATA_SIZE-2)*sizeof(l4_umword_t) || out_buf == NULL)
		return -L4_EINVAL;

	s << l4_umword_t(Opcode::func_decrypt) << L4::Ipc::Buf_cp_out<unsigned char>(in_buf, size);
	int ret = l4_error(s.call(server.cap(), Protocol::Encryption));
	if(ret != L4_EOK)
		return ret;
	s >> L4::Ipc::Buf_cp_in<unsigned char>(out_buf, size);
	return L4_EOK;
}

static int hexprint(unsigned char *buf, unsigned size) {

	if(buf == NULL && size != 0)
		return -L4_EINVAL;
	for(unsigned i=0; i<size; i++)
		printf("%02x", buf[i]);
	return L4_EOK;
}

static int hexprintln(unsigned char *buf, unsigned size) {

	int ret = hexprint(buf, size);
	if(ret != L4_EOK)
		return ret;
	printf("\n");
	return L4_EOK;
}



int main() {

	unsigned char original_data[] = {0xde, 0xad, 0xbe, 0xef};
	unsigned char encrypted_data[sizeof(original_data)];
	unsigned char decrypted_data[sizeof(original_data)];
	int ret;


	L4::Cap<void> server = L4Re::Env::env()->get_cap<void>(ENCRYPTION_SERVER_NAME);
	if (!server.is_valid()) {
		printf("Could not get server capability!\n");
		return 1;
	}

	printf("original data  : "); hexprintln(original_data, sizeof(original_data));
	ret = call_encrypt(server, original_data, sizeof(original_data), encrypted_data);
	if(ret != L4_EOK) {
		fprintf(stderr, "error encrypting data, ret=%d\n", ret);
		return 1;
	}
	printf("encrypted data : "); hexprintln(encrypted_data, sizeof(encrypted_data));
	ret = call_decrypt(server, encrypted_data, sizeof(encrypted_data), decrypted_data);
	if(ret != L4_EOK) {
		fprintf(stderr, "error decrypting data, ret=%d\n", ret);
		return 1;
	}
	printf("decrypted data : "); hexprintln(decrypted_data, sizeof(decrypted_data));

	return 0;
}
