#!/bin/bash
set -euo pipefail

echo ""
echo "🔐 Verifying development environment authenticity..."

IMAGE="ghcr.io/matejgomboc/armcortexm-cpplib-devenv:latest"

# Fail fast if cosign is missing (it should be in the image)
if ! command -v cosign >/dev/null 2>&1; then
    echo "❌ ERROR: cosign not found in image!"
    echo "   This image may be compromised or outdated."
    exit 1
fi

# Verify signature (critical security check)
echo "🔍 Verifying image signature..."
if cosign verify \
    --certificate-identity-regexp="^https://github.com/MatejGomboc/ARMCortexM-CppLib-DevEnv.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" > /dev/null 2>&1; then
    echo "✅ Image signature verified - authenticated build from GitHub Actions"
else
    echo "❌ ERROR: Image signature verification FAILED!"
    echo "   This image may be tampered with or not from the official pipeline."
    exit 1
fi

# Verify build provenance attestation (supplementary check)
# GitHub's actions/attest-build-provenance stores attestations in GitHub's API
# We'll try to verify but won't fail if it's not accessible via cosign
echo "🔍 Checking for build provenance attestation..."

ATTESTATION_VERIFIED=false

# Try without specifying predicate type (auto-detect)
if cosign verify-attestation \
    --certificate-identity-regexp="^https://github.com/MatejGomboc/ARMCortexM-CppLib-DevEnv.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" > /dev/null 2>&1; then
    ATTESTATION_VERIFIED=true
fi

# Try with explicit SLSA provenance v1 type if first attempt failed
if [ "$ATTESTATION_VERIFIED" = false ]; then
    if cosign verify-attestation \
        --type "https://slsa.dev/provenance/v1" \
        --certificate-identity-regexp="^https://github.com/MatejGomboc/ARMCortexM-CppLib-DevEnv.*" \
        --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
        "$IMAGE" > /dev/null 2>&1; then
        ATTESTATION_VERIFIED=true
    fi
fi

if [ "$ATTESTATION_VERIFIED" = true ]; then
    echo "✅ Build provenance attestation verified"
else
    echo "ℹ️  Build provenance attestation check skipped"
    echo "   Attestations are stored in GitHub's API and may require 'gh' CLI to verify"
    echo "   Image signature verification passed - container is trusted"
fi

echo ""
echo "✅ Security verification completed successfully!"
echo ""
