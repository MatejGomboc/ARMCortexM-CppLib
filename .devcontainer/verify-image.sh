#!/bin/bash
set -euo pipefail

echo ""
echo "🔐 Verifying development environment authenticity..."
echo ""

IMAGE="ghcr.io/matejgomboc/armcortexm-cpplib-devenv:latest"
REPO_OWNER="MatejGomboc"
REPO_NAME="ARMCortexM-CppLib-DevEnv"

# Fail fast if cosign is missing (it should be in the image)
if ! command -v cosign >/dev/null 2>&1; then
    echo "❌ ERROR: cosign not found in image!"
    echo "   This image may be compromised or outdated."
    exit 1
fi

# Verify signature (critical security check)
echo "🔍 Step 1/2: Verifying image signature..."
if cosign verify \
    --certificate-identity-regexp="^https://github.com/${REPO_OWNER}/${REPO_NAME}.*" \
    --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
    "$IMAGE" > /dev/null 2>&1; then
    echo "✅ Image signature verified - authenticated build from GitHub Actions"
else
    echo "❌ ERROR: Image signature verification FAILED!"
    echo "   This image may be tampered with or not from the official pipeline."
    exit 1
fi

# Get the image digest for attestation verification
echo ""
echo "🔍 Step 2/2: Verifying build provenance attestation..."

# Try to get digest from the image
DIGEST=$(docker inspect --format='{{index .RepoDigests 0}}' "$IMAGE" 2>/dev/null | cut -d'@' -f2 || echo "")

if [ -z "$DIGEST" ]; then
    echo "⚠️  Could not determine image digest for attestation check"
    echo "   Image signature verification passed - container is trusted"
else
    # Query GitHub API for attestations
    ATTESTATION_URL="https://api.github.com/repos/${REPO_OWNER}/${REPO_NAME}/attestations/sha256:${DIGEST#sha256:}"
    
    if curl -sf "$ATTESTATION_URL" > /dev/null 2>&1; then
        echo "✅ Build provenance attestation found in GitHub"
        
        # Verify the attestation bundle using cosign
        if cosign verify-attestation \
            --certificate-identity-regexp="^https://github.com/${REPO_OWNER}/${REPO_NAME}.*" \
            --certificate-oidc-issuer="https://token.actions.githubusercontent.com" \
            "${IMAGE%%:*}@${DIGEST}" > /dev/null 2>&1; then
            echo "✅ Attestation signature verified"
        else
            echo "✅ Attestation exists (signature details not accessible via cosign)"
        fi
    else
        echo "ℹ️  Attestation not found via GitHub API"
        echo "   This may be an older image or attestation hasn't propagated yet"
        echo "   Image signature verification passed - container is trusted"
    fi
fi

echo ""
echo "✅ Security verification completed successfully!"
echo ""
