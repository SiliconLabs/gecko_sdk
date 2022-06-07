ARG SYSTEM_ARCH=arm32v7
ARG BASE_CONTAINER=${SYSTEM_ARCH}/otbr_cpc
FROM    ${BASE_CONTAINER}
ARG SYSTEM_ARCH=arm32v7a # trick to make the build environment have the variable defined

RUN DEBIAN_FRONTEND=noninteractive apt update && apt install -y socat tmux procps libreadline8 systemd init lsb-release libmbedtls-dev

# Install some non-essential software
RUN DEBIAN_FRONTEND=noninteractive apt update && apt install -y nano gdb

# Install BlueZ
RUN DEBIAN_FRONTEND=noninteractive apt update && apt install -y bluetooth bluez bluez-tools rfkill libbluetooth-dev
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
