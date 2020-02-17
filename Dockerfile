FROM alpine:3.11.3
RUN apk add -U build-base clang
COPY Makefile *.cc *.h ./
RUN make test && make app

FROM alpine:3.11.3
RUN apk add -U libstdc++
COPY --from=0 /app /app
ENTRYPOINT ["/app"]
