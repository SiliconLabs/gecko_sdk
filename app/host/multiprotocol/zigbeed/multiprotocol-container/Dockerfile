ARG SYSTEM_ARCH=arm32v7
ARG BASE_CONTAINER=${SYSTEM_ARCH}/otbr_cpc
FROM    ${BASE_CONTAINER}
ARG SYSTEM_ARCH=arm32v7a # trick to make the build environment have the variable defined
LABEL okToPrune="true"

ARG DEBIAN_FRONTEND=noninteractive

# Install software
RUN apt-get update && apt-get install -y \
    bluetooth \
    bluez \
    bluez-tools \
    gdb \
    init \
    libbluetooth-dev \
    libmbedtls-dev \
    libreadline8 \
    lsb-release \
    nano \
    procps \
    rfkill \
    tmux \
    socat \
    systemd \
    && rm -rf /var/lib/apt/lists/*

# Don't auto-start bluetooth service
RUN systemctl disable bluetooth.service

# Remove "tail -f /var/log/syslog" from shell script
RUN sed -i '$ d' /app/etc/docker/docker_entrypoint.sh
# Fix 'pam_env' issue with unset locale
RUN locale >/etc/default/locale

# Add in systemd files
COPY _artifacts/systemd/* /etc/systemd/system/
RUN systemctl enable cpcd.service
ENTRYPOINT ["/sbin/init"]

# Install artifacts
COPY _artifacts/bin_${SYSTEM_ARCH}/* /usr/local/bin/
COPY _artifacts/etc/* /usr/local/etc/
COPY _artifacts/firmware/* /opt/
