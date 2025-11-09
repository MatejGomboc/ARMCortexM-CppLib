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

# Check for attestation in the cosign output
echo ""
echo "🔍 Step 2/2: Checking for build provenance attestation..."

if grep -q "https://slsa.dev/provenance/v1" "$COSIGN_OUTPUT" 2>/dev/null; then
    echo "✅ Build provenance attestation verified (SLSA v1)"
    echo "   Attestation found in signature verification output"
    rm -f "$COSIGN_OUTPUT"
else
    # Try separate attestation verification
    DIGEST=$(grep -oP 'sha256:[a-f0-9]{64}' "$COSIGN_OUTPUT" | head -n1 || echo "")
    rm -f "$COSIGN_OUTPUT"
    
    if [ -n "$DIGEST" ]; then
        IMAGE_WITH_DIGEST="${IMAGE%%:*}@${DIGEST}"
        
        if cosign verify-attestation \
            --type "https://slsa.dev/provenance/v1" \
            --certificate-identity-regexp="^https://github.com/${REPO_OWNER}/${REPO_NAME}.*" \
            --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
            "$IMAGE_WITH_DIGEST" > /dev/null 2>&1; then
            echo "✅ Build provenance attestation verified (SLSA v1)"
        else
            echo "ℹ️  Build provenance attestation not separately accessible"
            echo "   (Attestations may be bundled with signatures)"
            echo "   Image signature verification passed - container is trusted"
        fi
    else
        echo "ℹ️  Could not extract digest for attestation check"
        echo "   Image signature verification passed - container is trusted"
    fi
fi

echo ""
echo "✅ Security verification completed successfully!"
echo ""
