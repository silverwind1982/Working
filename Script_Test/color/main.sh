#!/bin/sh
set -e

source ./color.sh

print_info "whilte"
print_error "error"
print_warning "warning"
print_title "title"
print_orange "orange"

echo "$(date +%F\ %T)"

