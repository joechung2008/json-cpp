# Builder stage
FROM alpine:3.19 AS builder
RUN apk add --no-cache build-base cmake git
WORKDIR /app
COPY . .
# Build a static binary for Alpine compatibility
RUN cmake -S . -B build -DCMAKE_EXE_LINKER_FLAGS="-static" && \
    cmake --build build --config Release

# Runner stage
FROM alpine:3.19 AS runner
WORKDIR /app
COPY --from=builder /app/out/cli /app/cli
ENTRYPOINT ["/app/cli"]
