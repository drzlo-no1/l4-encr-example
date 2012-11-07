PKGDIR          ?= ..
L4DIR           ?= $(PKGDIR)/../..

TARGET           = encr-srv encr-clnt
SRC_CC_encr-srv  = server.cc
SRC_CC_encr-clnt = client.cc
REQUIRES_LIBS    = cxx_libc_io cxx_io

include $(L4DIR)/mk/prog.mk

