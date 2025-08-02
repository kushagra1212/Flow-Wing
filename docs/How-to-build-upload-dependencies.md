```bash
 docker buildx build \
  -f docker/Dockerfile.deps \
  -t kushagra711/flow-wing-compiler-deps:latest \
  --platform linux/amd64,linux/arm64 \
  --push .
```
