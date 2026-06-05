#Requires -Version 5.1
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

git submodule update --init --recursive

# Version env vars
try {
    $tag = git describe --tags --exact-match 2>$null
    if ($tag) { $env:SEMVER = $tag }
} catch {}

$env:GITHUB_SHA_SHORT = git rev-parse --short HEAD

### --- Clone SDKs ------------------------------------------------------------
$SDK_DIR = "$env:TEMP\sdk"
$SOURCE2TOOLKITSDK_DIR = "$SDK_DIR\source2toolkit-sdk"
$HL2SDK_DIR = "$SDK_DIR\hl2sdk-cs2"
$MMSOURCE_DIR = "$SDK_DIR\metamod-source"
$CSGO_PROTO_DIR = "$SDK_DIR\Protobufs\csgo"

Write-Host "=== Preparing temporary SDK directory ==="
if (Test-Path $SDK_DIR) { Remove-Item -Recurse -Force $SDK_DIR }
New-Item -ItemType Directory -Force $SDK_DIR | Out-Null

Write-Host "=== Downloading Source2Toolkit-SDK ==="
git clone --recursive https://github.com/SlynxCZ/source2toolkit-sdk.git $SOURCE2TOOLKITSDK_DIR

Write-Host "=== Downloading HL2SDK-CS2 ==="
git clone --recursive --branch cs2 --single-branch https://github.com/alliedmodders/hl2sdk.git $HL2SDK_DIR

Write-Host "=== Downloading Metamod-Source ==="
git clone --recursive --branch master --single-branch https://github.com/alliedmodders/metamod-source.git $MMSOURCE_DIR

Write-Host "=== Downloading Protobufs ==="
git clone --recursive https://github.com/SteamDatabase/Protobufs $CSGO_PROTO_DIR

### --- Export env vars for CMake ---------------------------------------------
$env:SOURCE2TOOLKIT_SDK = $SOURCE2TOOLKITSDK_DIR
$env:HL2SDKCS2 = $HL2SDK_DIR
$env:MMSOURCE_DEV = $MMSOURCE_DIR
$env:CSGO_PROTO = $CSGO_PROTO_DIR

Write-Host "Using HL2SDKCS2=$env:HL2SDKCS2"
Write-Host "Using MMSOURCE_DEV=$env:MMSOURCE_DEV"
Write-Host "Using CSGO_PROTO=$env:CSGO_PROTO"

### --- Build -----------------------------------------------------------------
Write-Host "=== Starting build ==="

if (Test-Path build) { Remove-Item -Recurse -Force build }
New-Item -ItemType Directory build | Out-Null
Set-Location build

cmake .. -G Ninja `
  -DCMAKE_BUILD_TYPE=RelWithDebInfo

Write-Host "=== Building | RelWithDebInfo ==="
cmake --build . -- -j $env:NUMBER_OF_PROCESSORS
