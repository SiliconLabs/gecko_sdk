# Build library dependencies and Python wrappers for the ESL AP script

.PHONY: all lib wrapper clean cleanlib cleancopy

all: lib wrapper
clean: cleanlib cleancopy

lib:
	@$(MAKE) -C ../../common_host/esl_lib -j $(ARGS)
	@$(MAKE) -C ../../common_host/esl_key_lib -j
	@cp -Rv ../../common_host/esl_lib/lib .
	@cp -Rv ../../common_host/esl_key_lib/lib .

wrapper:
	@$(MAKE) -C ../../common_host/esl_lib esl_lib_wrapper.py
	@$(MAKE) -C ../../common_host/esl_key_lib esl_key_lib_wrapper.py
	@cp -v ../../common_host/esl_lib/esl_lib_wrapper.py .
	@cp -v ../../common_host/esl_key_lib/esl_key_lib_wrapper.py .

cleanlib:
	@$(MAKE) -C ../../common_host/esl_lib clean
	@$(MAKE) -C ../../common_host/esl_key_lib clean

cleancopy:
	rm -f *_wrapper.py
	rm -rf lib
