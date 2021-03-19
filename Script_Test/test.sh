#!/bin/bash

set -e

echo "bash source : $BASH_SOURCE"
SCRIPT_DIR=$(dirname $(realpath $BASH_SOURCE))
echo "script dir: $SCRIPT_DIR"

TOP_DIR=$(realpath $SCRIPT_DIR/../../..)
echo "Top dir: $TOP_DIR"

