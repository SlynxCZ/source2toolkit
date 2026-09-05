#!/bin/bash
set -e

git submodule update --init --recursive

### --- Version -------------------------------------------------------------
# SEMVER comes in from the CI, whose version job resolves the tag -- and, on
# the pushbuild.txt path, creates it -- before any build starts. The tag is
# pushed by then but this checkout need not have it, so asking git first would
# come up empty and the build would ship as "Local".
#
# A build outside that (a local one, a manual docker compose up) has nothing
# passed in and falls back to whatever tag HEAD carries. An untagged HEAD is
# not an error: CMake stamps it "Local" and the line below says so.
if [ -n "${SEMVER:-}" ]; then
  export SEMVER
  echo "=== Version: $SEMVER (from the environment) ==="
elif SEMVER="$(git describe --tags --exact-match 2>/dev/null)"; then
  export SEMVER
  echo "=== Version: $SEMVER (tag on HEAD) ==="
else
  # Exported-but-empty is not the same as unset to CMake, and would stamp the
  # build with an empty version instead of falling back.
  unset SEMVER
  echo '=== Version: no tag on HEAD, building as "Local" ==='
fi

export GITHUB_SHA_SHORT="$(git rev-parse --short HEAD)"

### --- Download HL2SDK-CS2 + Metamod-Source -------------------------------
SDK_DIR="/tmp/sdk"
SOURCE2TOOLKITSDK_DIR="$SDK_DIR/source2toolkit-sdk"
HL2SDK_DIR="$SDK_DIR/hl2sdk-cs2"
MMSOURCE_DIR="$SDK_DIR/metamod-source"
CSGO_PROTO_DIR="$SDK_DIR/Protobufs"

echo "=== Preparing temporary SDK directory ==="
rm -rf "$SDK_DIR"
mkdir -p "$SDK_DIR"

echo "=== Downloading Source2Toolkit-SDK ==="
git clone --recursive https://github.com/SlynxCZ/source2toolkit-sdk.git "$SOURCE2TOOLKITSDK_DIR"

echo "=== Downloading HL2SDK-CS2 ==="
git clone --recursive --branch cs2 --single-branch https://github.com/alliedmodders/hl2sdk.git "$HL2SDK_DIR"

echo "=== Downloading Metamod-Source ==="
git clone --recursive --branch master --single-branch https://github.com/alliedmodders/metamod-source.git "$MMSOURCE_DIR"

echo "=== Downloading Protobufs ==="
git clone --recursive https://github.com/SteamDatabase/Protobufs "$CSGO_PROTO_DIR"

### --- Export env vars for CMake ------------------------------------------
export SOURCE2TOOLKIT_SDK="$SOURCE2TOOLKITSDK_DIR"
export HL2SDKCS2="$HL2SDK_DIR"
export MMSOURCE_DEV="$MMSOURCE_DIR"
export CSGO_PROTO="$CSGO_PROTO_DIR/csgo"

echo "Using SOURCE2TOOLKIT_SDK=$SOURCE2TOOLKIT_SDK"
echo "Using HL2SDKCS2=$HL2SDKCS2"
echo "Using MMSOURCE_DEV=$MMSOURCE_DEV"
echo "Using CSGO_PROTO=$CSGO_PROTO"

### --- Build ---------------------------------------------------------------
echo "=== Starting build ==="

rm -rf build
mkdir build
cd build

cmake .. -G Ninja \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_C_COMPILER=clang-18 \
  -DCMAKE_CXX_COMPILER=clang++-18

echo "=== Building with Clang | RelWithDebInfo ==="

cmake --build . -j"$(nproc)"