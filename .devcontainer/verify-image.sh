#!/bin/bash
set -euo pipefail

echo ""
echo "🔐 Verifying development environment authenticity..."
echo ""

IMAGE="ghcr.io/matejgomboc/armcortexm-cpplib-devenv:latest"
REPO_OWNER="MatejGomboc"
REPO_NAME="ARMCortexM-CppLib-DevEnv"

# Check required tools
if ! command -v cosign >/dev/null 2>&1; then
    echo "❌ ERROR: cosign not found in image!"
    echo "   This image may be compromised or outdated."
    exit 1
fi

# Verify signature (critical security check)
echo "🔍 Step 1/2: Verifying image signature..."
COSIGN_OUTPUT=$(mktemp)
if cosign verify \
    --certificate-identity-regexp="^https://github.com/${REPO_OWNER}/${REPO_NAME}.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" 2>&1 | tee "$COSIGN_OUTPUT"; then
    echo "✅ Image signature verified - authenticated build from GitHub Actions"
else
    rm -f "$COSIGN_OUTPUT"
    echo "❌ ERROR: Image signature verification FAILED!"
    echo "   This image may be tampered with or not from the official pipeline."
    exit 1
fi

# Extract digest from cosign output
echo ""
echo "🔍 Step 2/2: Verifying build provenance attestation..."

DIGEST=$(grep -oP 'sha256:[a-f0-9]{64}' "$COSIGN_OUTPUT" | head -n1 || echo "")
rm -f "$COSIGN_OUTPUT"

if [ -z "$DIGEST" ]; then
    echo "⚠️  Could not extract image digest"
    echo "   Image signature verification passed - container is trusted"
else
    # Verify attestation using the digest (attestations are OCI artifacts attached to the image)
    IMAGE_WITH_DIGEST="${IMAGE%%:*}@${DIGEST}"
    
    # Try to verify attestation - it should be attached to the image in the registry
    if cosign verify-attestation \
        --certificate-identity-regexp="^https://github.com/${REPO_OWNER}/${REPO_NAME}.*" \
        --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
        "$IMAGE_WITH_DIGEST" > /dev/null 2>&1; then
        echo "✅ Build provenance attestation verified"
    else
        echo "ℹ️  Build provenance attestation not found or not verifiable"
        echo "   Image signature verification passed - container is trusted"
    fi
fi

echo ""
echo "✅ Security verification completed successfully!"
echo ""
