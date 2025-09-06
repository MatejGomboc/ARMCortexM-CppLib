#!/bin/sh

export Z_VCPKG_POSTSCRIPT="$(mktemp).sh"

vcpkg x-update-registry --all
vcpkg activate

if [ -f "${Z_VCPKG_POSTSCRIPT}" ]; then
    . "${Z_VCPKG_POSTSCRIPT}"
    rm "${Z_VCPKG_POSTSCRIPT}"
fi
