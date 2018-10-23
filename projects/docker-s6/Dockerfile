FROM busybox:latest

ADD https://github.com/just-containers/s6-overlay/releases/download/v1.21.7.0/s6-overlay-amd64.tar.gz /tmp/

RUN tar xzf /tmp/s6-overlay-amd64.tar.gz -C / && rm -rf /tmp

# COPY rootfs /
ENTRYPOINT ["/init"] 
