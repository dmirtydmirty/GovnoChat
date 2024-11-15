FROM gcc:14.2.0-bookworm
RUN apt update && apt install -y curl g++ cmake ninja-build
WORKDIR /tmp
RUN curl https://archives.boost.io/release/1.86.0/source/boost_1_86_0.tar.gz --output boost.tar.gz \
        && tar xzf boost.tar.gz \
        &&  cd boost_1_86_0/ \
        && ./bootstrap.sh \
        && ./b2 install \
        && rm -r /tmp/*