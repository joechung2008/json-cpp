# Builder stage
FROM alpine:3.19 AS builder
RUN apk add --no-cache build-base cmake git
WORKDIR /app
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static" && \
    cmake --build build

# Runner stage
FROM scratch
WORKDIR /app
COPY --from=builder /app/out/cli /app/cli
ENTRYPOINT ["/app/cli"]
