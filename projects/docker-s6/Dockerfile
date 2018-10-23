FROM ros:kinetic-perception

ADD https://github.com/just-containers/s6-overlay/releases/download/v1.21.7.0/s6-overlay-amd64.tar.gz /tmp/

RUN tar xzf /tmp/s6-overlay-amd64.tar.gz -C / && rm -rf /tmp

# COPY rootfs /

COPY services /etc/s6/services/

RUN mkdir -p /var/log/services

ENTRYPOINT ["/init"] 
