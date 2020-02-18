FROM alpine:3.11.3
RUN apk add -U build-base clang && \
    apk add -U rocksdb-dev -X http://dl-cdn.alpinelinux.org/alpine/edge/testing
COPY Makefile *.cc *.h ./
RUN make test && make app

FROM alpine:3.11.3
RUN apk add -U libstdc++ && \
    apk add -U rocksdb -X http://dl-cdn.alpinelinux.org/alpine/edge/testing
COPY --from=0 /app /app
ENTRYPOINT ["/app"]
