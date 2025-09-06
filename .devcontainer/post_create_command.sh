#!/bin/sh

set -e

export Z_VCPKG_POSTSCRIPT="$(mktemp).sh"

vcpkg x-update-registry --all
vcpkg activate

#echo 'eval "$(vcpkg activate 2>/dev/null)"' >> ~/.bashrc

if [ -f "${Z_VCPKG_POSTSCRIPT}" ]; then
    . "${Z_VCPKG_POSTSCRIPT}"
    rm "${Z_VCPKG_POSTSCRIPT}"
fi
