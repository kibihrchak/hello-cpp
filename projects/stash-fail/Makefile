#	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#	Default target and vars

default: test

ifndef VERBOSE
.SILENT:
endif

BUILD_DIR_BASE := build
CMAKE_ERROR_LOG_FILE := stderr.log


#	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#	Targets

generate:
	mkdir -p "$(BUILD_DIR_BASE)"
	cd "$(BUILD_DIR_BASE)" && cmake -DCMAKE_BUILD_TYPE=Debug ..

build: generate
	# 	Build is expected to fail, hence `true` is executed at the end
	# 	to keep the make execution going
	cd "$(BUILD_DIR_BASE)" \
		&& cmake --build . -- -k 2>"$(CMAKE_ERROR_LOG_FILE)" \
		|| true

test: build
	echo "Running tests"
	BUILD_DIR_BASE="$(BUILD_DIR_BASE)" pytest .


#	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#	Phony targets specification

.PHONY: build test
