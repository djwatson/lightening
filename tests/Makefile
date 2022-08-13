TESTS ?= $(sort $(basename $(wildcard *.c)))
TARGETS ?= native ia32 aarch64 armv7 mips64el mipsel ppc ppc64 ppc64le

# Suitable values of cross-compiler variables for Debian:
#
#   make test CC_IA32=i668-linux-gnu-gcc CC_AARCH64=aarch64-linux-gnu-gcc
#
# The relevant packages that you need to run this:
#
#   dpkg --add-architecture i386
#   dpkg --add-architecture arm64
#   apt-get update -qq
#   apt-get install -y \
#     libc6-dev:amd64 gcc make \
#     qemu binfmt-support qemu-user-static \
#     gcc-i686-linux-gnu libc6-dev-i386-cross libc6:i386 \
#     gcc-aarch64-linux-gnu libc6-dev-arm64-cross libc6:arm64
#
CC = gcc
CC_IA32=guix environment --pure -s i686-linux --ad-hoc gcc-toolchain -- gcc
CC_AARCH64=guix environment --pure -s aarch64-linux --ad-hoc gcc-toolchain -- gcc
CC_ARMv7=guix environment --pure -s armhf-linux --ad-hoc gcc-toolchain -- gcc
CC_MIPS64EL=guix environment --pure -s mips64el-linux --ad-hoc gcc-toolchain -- gcc
CC_MIPSEL=guix environment --pure -s mipsel-linux --ad-hoc gcc-toolchain -- gcc
CC_PPC=guix environment --pure -s powerpc-linux --ad-hoc gcc-toolchain -- gcc
CC_PPC64=guix environment --pure -s powerpc64-linux --ad-hoc gcc-toolchain -- gcc
CC_PPC64LE=guix environment --pure -s powerpc64le-linux --ad-hoc gcc-toolchain -- gcc
CFLAGS = -Wall -O0 -g $(DEBUG)
LDFLAGS = -lpthread
RUNNER =

all: $(foreach TARGET,$(TARGETS),$(addprefix test-$(TARGET)-,$(TESTS)))

check: $(addprefix test-$(TARGET),$(TARGETS))

test-%: $(addprefix test-%-,$(TESTS))
	@echo "Running unit tests..."
	@set -e; for test in $?; do \
	  echo "Testing: $$test"; \
	  ./$$test; \
	done
	@echo "Success."

.PHONY: test check

lightening-%.o: ../lightening.h ../lightening/*.c ../lightening/*.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ -c ../lightening/lightening.c

test-native-%: %.c lightening-native.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-native.o $< $(LDFLAGS)

test-ia32-%: CC = $(CC_IA32)
test-ia32-%: %.c lightening-ia32.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-ia32.o $< $(LDFLAGS)

test-aarch64-%: CC = $(CC_AARCH64)
test-aarch64-%: %.c lightening-aarch64.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-aarch64.o $< $(LDFLAGS)

test-armv7-%: CC = $(CC_ARMv7)
test-armv7-%: %.c lightening-armv7.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-armv7.o $< $(LDFLAGS)

test-mips64el-%: CC = $(CC_MIPS64EL)
test-mips64el-%: %.c lightening-mips64el.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-mips64el.o $< $(LDFLAGS)

test-mipsel-%: CC = $(CC_MIPSEL)
test-mipsel-%: %.c lightening-mipsel.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-mipsel.o $< $(LDFLAGS)

test-ppc-%: CC = $(CC_PPC)
test-ppc-%: %.c lightening-ppc.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-ppc.o $< $(LDFLAGS)

test-ppc64-%: CC = $(CC_PPC64)
test-ppc64-%: %.c lightening-ppc.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-ppc64.o $< $(LDFLAGS)

test-ppc64le-%: CC = $(CC_PPC64LE)
test-ppc64le-%: %.c lightening-ppc64le.o test.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -I.. -o $@ lightening-ppc64le.o $< $(LDFLAGS)

.PRECIOUS: $(foreach TARGET,$(TARGETS),$(addprefix test-$(TARGET)-,$(TESTS)))
.PRECIOUS: $(foreach TARGET,$(TARGETS),lightening-$(TARGET).o)

clean:
	rm -f $(foreach TARGET,$(TARGETS),$(addprefix test-$(TARGET)-,$(TESTS)))
	rm -f $(foreach TARGET,$(TARGETS),lightening-$(TARGET).o)
