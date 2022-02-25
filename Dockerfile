FROM prantlf/alpine-make-gcc:latest

COPY . /usr/src/feminist_api
WORKDIR /usr/src/feminist_api

RUN make install

CMD ["feminist_api"]
