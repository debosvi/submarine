# build docker

docker build --tag docker-s6 .

# start docker

docker run -it --rm --name docker-s6 --mount type=tmpfs,destination=/var/run,tmpfs-mode=0755,tmpfs-size=10M --read-only  docker-s6:latest
