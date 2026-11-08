#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
platform=${XUANWU_PLATFORM:-$(cd ../../.. && pwd)}
mkdir -p ../defaultGroup/lib ../defaultGroup/bin
cp -f "$platform"/compiler/include/* ../defaultGroup/lib/
cp -f "$platform"/compiler/arm/* ./
export LD_LIBRARY_PATH="$PWD${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
./icomp -perfconf perf.json -preproccmd "gcc -E -x c -I ../defaultGroup/lib" -outf IOSwitch -outfdir ../defaultGroup/bin/ ../defaultGroup/control_flow.npc 2>&1 | tee compiler.log
grep -Eq 'Errors: *0' compiler.log
./ilink ../defaultGroup/bin/IOSwitch.obj 2>&1 | tee linker.log
