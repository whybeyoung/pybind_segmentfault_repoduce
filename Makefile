python_version_full := $(wordlist 2,4,$(subst ., ,$(shell python --version 2>&1)))
python_version_major := $(word 1,${python_version_full})
python_version_minor := $(word 2,${python_version_full})
python_version_patch := $(word 3,${python_version_full})


PY_GT_3_6 := $(shell [ $(python_version_major) -gt 3 -o \( $(python_version_major) -eq 3 -a $(python_version_minor) -ge 6 \) ] && echo true)

PYLIB=$(shell python3-config  --ldflags)
PYINC=$(shell python3-config --cflags)
ifeq ($(PY_GT_3_6),true)
PYLIB=$(shell python3-config  --ldflags  --embed)
PYINC=$(shell python3-config --cflags --embed )
endif
build:
	echo $(python_version_minor)
	echo $(PY_GT_3_6)
	rm -f test
	g++ -Wall  -g -O0 -fPIC  -I./include/spdlog/include/ $(PYINC)  test_thread.cpp  -o test $(PYLIB)
