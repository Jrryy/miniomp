#!/usr/bin/env bash

set -ue

PAP=${1:-12}

echo "Upload to boada user pap00${PAP}"

scp -r src pap00${PAP}@boada.ac.upc.edu:miniomp

ssh pap00${PAP}@boada.ac.upc.edu