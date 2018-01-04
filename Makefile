# Invoke with: `make build first.cpp second.cpp output=executable`
# If the output variable is omitted, the generated executable is based on the name of the first input file (e.g. "bin/first")

CXX = g++
CPPFLAGS = -Iinclude -o bin/$(if $(output),$(output),$(basename $(notdir $(word 1, $(BUILD_ARGS)))))
LDFLAGS = -Llib
LDLIBS = -lsb7 -lglfw3 -lopengl32

# Allow `make build` with unnamed target variables
ifeq (build,$(firstword $(MAKECMDGOALS)))
  BUILD_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # And turn them into do-nothing targets
  $(eval $(BUILD_ARGS):;@:)
endif

build:
	$(CXX) $(BUILD_ARGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

# Allow `make run` with unnamed target variable
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

run: ./bin/$(RUN_ARGS)
	./bin/$(RUN_ARGS)
