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

# Verify signature
if cosign verify \
    --certificate-identity-regexp="^https://github.com/MatejGomboc/ARMCortexM-CppLib-DevEnv.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" 2>&1 | grep -q "Verification for"; then
    echo "✅ Image signature verified - authenticated build from GitHub Actions"
else
    echo "❌ ERROR: Image signature verification FAILED!"
    echo "   This image may be tampered with or not from the official pipeline."
    exit 1
fi

# Verify build provenance attestation
if cosign verify-attestation \
    --type slsaprovenance \
    --certificate-identity-regexp="^https://github.com/MatejGomboc/ARMCortexM-CppLib-DevEnv.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" >/dev/null 2>&1; then
    echo "✅ Build provenance verified - complete supply chain attestation"
else
    echo "⚠️  Build provenance attestation not verified (non-critical)"
fi

echo ""
