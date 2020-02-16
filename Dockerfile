FROM alpine
RUN apk add -U build-base clang
COPY Makefile *.cpp *.h ./
RUN make test && make app
ENTRYPOINT ["/app"]
