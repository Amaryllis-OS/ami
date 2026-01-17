FROM alpine:latest AS builder

# Rustのインストール
RUN apk add --no-cache \
    curl \
    build-base \
    git

# rustupのインストール
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

# cmateのビルド
WORKDIR /build
RUN git clone https://github.com/sirasaki-konoha/cmate.git && \
    cd cmate && \
    git checkout cmate-rs && \
    cargo build --release

# 最終イメージ
FROM alpine:latest

# 必要なパッケージのインストール
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    make \
    libarchive-dev \
    libarchive-static \
    zlib-dev \
    zlib-static \
    bzip2-dev \
    bzip2-static \
    xz-dev \
    xz-static \
    lz4-dev \
    lz4-static \
    zstd-dev \
    zstd-static \
    openssl-libs-static \
    openssl-dev

COPY --from=builder /build/cmate/target/release/cmate /usr/local/bin/cmate


CMD /bin/sh