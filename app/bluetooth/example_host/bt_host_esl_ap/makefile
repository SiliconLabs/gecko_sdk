# Build library dependencies and Python wrappers for the ESL AP script

.PHONY: all lib debug release wrapper clean clean_sql cleanlib cleanlib_sql cleancopy

all: release
debug: ARGS += debug
debug: lib wrapper
release: ARGS += release
release: lib wrapper
clean: cleanlib cleancopy
cleansql: cleanlib_sql cleancopy

lib:
	@$(MAKE) -C ../../common_host/esl_lib -j $(ARGS)
	@$(MAKE) -C ../../common_host/esl_key_lib -j $(ARGS)
	@cp -Rv ../../common_host/esl_lib/lib .
	@cp -Rv ../../common_host/esl_key_lib/lib .

wrapper:
	@$(MAKE) -C ../../common_host/esl_lib esl_lib_wrapper.py
	@$(MAKE) -C ../../common_host/esl_key_lib esl_key_lib_wrapper.py
	@cp -v ../../common_host/esl_lib/esl_lib_wrapper.py .
	@cp -v ../../common_host/esl_key_lib/esl_key_lib_wrapper.py .

cleanlib:
	@$(MAKE) -C ../../common_host/esl_lib clean
	@$(MAKE) -C ../../common_host/esl_key_lib clean_keep_sql

cleanlib_sql:
	@$(MAKE) -C ../../common_host/esl_lib clean
	@$(MAKE) -C ../../common_host/esl_key_lib clean

cleancopy:
	rm -f *_wrapper.py
	rm -rf lib