#!/usr/bin/env bash
set -e

# Update vcpkg registries
vcpkg x-update-registry --all

# Install dependencies from vcpkg-configuration.json
vcpkg install

# Activate the environment
vcpkg activate
