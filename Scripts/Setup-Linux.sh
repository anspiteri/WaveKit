#!/bin/bash
# ========================================================
# WaveKit Linux Build Helper Script
# ========================================================
# Usage:
#   - From root:    ./Scripts/setup-linux.sh [options]
#   - From Scripts: ./setup-linux.sh [options]
# Options:
#   --no-demo      Exclude Demo project
#   --no-tests     Exclude Test directory
# ========================================================

set -e

# -- Capture script path --
SCRIPT_PATH="$(realpath "$0")"
CALLER_DIR="$(dirname "$SCRIPT_PATH")"

# -- Root detection --
ROOT_DIR="$CALLER_DIR"
while [[ ! -f "$ROOT_DIR/Build.lua" && ! -d "$ROOT_DIR/.git" ]]; do
  if [[ "$ROOT_DIR" == "/" ]]; then
    echo "ERROR: Cannot locate project root"
    echo "Tried finding either:"
    echo "  - Build.lua"
    echo "  - .git directory"
    echo "Please run from within the WaveKit project"
    exit 1
  fi
  ROOT_DIR="$(dirname "$ROOT_DIR")"
done

# -- Path configuration --
# 1. Try standard Premake location
PREMAKE_PATH="$ROOT_DIR/Vendor/Binaries/Premake/Linux/premake5"

# 2. Fallback to searching for premake5
if [[ ! -x "$PREMAKE_PATH" ]]; then
  PREMAKE_PATH="$(find "$ROOT_DIR" -type f -name premake5 -executable | head -n 1)"
  if [[ -z "$PREMAKE_PATH" ]]; then
    echo "ERROR: Premake not found at:"
    echo "$ROOT_DIR/Vendor/Binaries/Premake/Linux/premake5"
    echo "And no alternative premake5 found in project"
    exit 1
  fi
fi

# -- Compute relative paths for display --
REL_SCRIPT_PATH="${SCRIPT_PATH#$ROOT_DIR/}"
REL_PREMAKE_PATH="${PREMAKE_PATH#$ROOT_DIR/}"

# -- Main execution --
echo
echo "[WaveKit] Generating solution..."
echo "Script: WaveKit/$REL_SCRIPT_PATH"
echo "Premake: WaveKit/$REL_PREMAKE_PATH"
echo

cd "$ROOT_DIR"
"$PREMAKE_PATH" --file="Build.lua" "$@" gmake2

if [[ $? -ne 0 ]]; then
  echo "ERROR: Generation failed (see above)"
  exit 1
fi
