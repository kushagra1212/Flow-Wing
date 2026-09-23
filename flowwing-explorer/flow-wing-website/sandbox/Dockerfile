# The playground's compile sandbox: FlowWing and Emscripten, for POST /compile
# in server.fg, which starts one throwaway container per compile:
#
#   docker run --rm --network none --cpus=1 --memory=512m --pids-limit=256 \
#     -v <submission>:/sandbox:ro flowwing-wasm-sandbox \
#     node /opt/playground/compile.mjs /sandbox/code.fg --target=wasm32 ...
#
# Build from this folder:
#
#   docker build -t flowwing-wasm-sandbox .
#
# The flowwing package it installs must include the wasm32 runtime
# (lib/wasm32-emscripten): a release newer than v1.0.19.

FROM ubuntu:24.04 AS toolchain
ENV DEBIAN_FRONTEND=noninteractive

# FlowWing from the apt repository, as in the other images. python3, git and
# xz-utils are for emsdk.
RUN apt-get update && \
    apt-get install -y --no-install-recommends curl gnupg ca-certificates git python3 xz-utils && \
    install -m 0755 -d /etc/apt/keyrings && \
    curl -fsSL https://kushagra1212.github.io/Flow-Wing/flowwing.gpg.key | gpg --dearmor -o /etc/apt/keyrings/flowwing.gpg && \
    echo "deb [signed-by=/etc/apt/keyrings/flowwing.gpg] https://kushagra1212.github.io/Flow-Wing/ ./" > /etc/apt/sources.list.d/flowwing.list && \
    apt-get update && apt-get install -y --no-install-recommends flowwing && \
    rm -rf /var/lib/apt/lists/*

# Emscripten, at the version the wasm target is tested with
# (.github/workflows/multi_platform_ci.yml). FlowWing finds emcc through
# EMSDK. The Node that emsdk brings runs compile.mjs.
ENV EMSDK=/opt/emsdk
RUN git clone --depth 1 https://github.com/emscripten-core/emsdk.git "$EMSDK" && \
    "$EMSDK/emsdk" install 6.0.10 && \
    "$EMSDK/emsdk" activate 6.0.10 && \
    rm -rf "$EMSDK/downloads" "$EMSDK/.git" && \
    ln -s "$EMSDK"/node/*/bin/node /usr/local/bin/node && \
    node --version

FROM toolchain
COPY compile.mjs /opt/playground/compile.mjs

# emcc builds the C library and the rest of its system libraries the first
# time a program needs them, into its cache. Build them now, with the programs
# the playground makes: plain, with tasks (another runtime shape), at -O0 and
# -O2. At run time the container has no network, and every compile would pay
# for the build.
RUN mkdir /tmp/warm && cd /tmp/warm && \
    printf 'bring vec\nbring map\nbring text\nprintln("warm")\n' > plain.fg && \
    printf 'bring sys\nfun nap() -> nthg {\n    sys::sleep(1)\n}\nspawn nap()\nprintln("warm")\n' > tasks.fg && \
    for program in plain.fg tasks.fg; do \
      for opt in 0 2; do \
        node /opt/playground/compile.mjs "$program" --opt="$opt" --wat > result.json && \
        grep -q '"ok":true' result.json || { cat result.json; exit 1; }; \
      done; \
    done && \
    cd / && rm -rf /tmp/warm

# From here on emcc only reads its cache. The sandbox user cannot write it, and
# a compile that needed a library missing from it should fail loudly, not try.
ENV EM_FROZEN_CACHE=1

RUN useradd -m -s /usr/sbin/nologin sandboxuser
USER sandboxuser
WORKDIR /home/sandboxuser

# The same check as the user compiles run as, with the cache frozen.
RUN printf 'println("ok")\n' > /tmp/check.fg && \
    node /opt/playground/compile.mjs /tmp/check.fg --wat > /tmp/check.json && \
    grep -q '"ok":true' /tmp/check.json && \
    rm /tmp/check.fg /tmp/check.json
