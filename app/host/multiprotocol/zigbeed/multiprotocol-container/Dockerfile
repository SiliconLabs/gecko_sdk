ARG SYSTEM_ARCH=arm32v7
ARG BASE_CONTAINER=${SYSTEM_ARCH}/otbr_cpc
FROM    ${BASE_CONTAINER}
ARG SYSTEM_ARCH=arm32v7a # trick to make the build environment have the variable defined
LABEL ok-to-prune="true"

ARG DEBIAN_FRONTEND=noninteractive

# Install software
RUN apt-get update && apt-get install -y \
    bluetooth \
    bluez \
    bluez-tools \
    python3 \
    python3-pip \
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

# Prerequisite to use Silabs python BGAPI program 
RUN pip3 install pybgapi

# Remove "tail -f /var/log/syslog" from shell script
RUN sed -i '/tail -f \/var\/log\/syslog/d' /app/etc/docker/docker_entrypoint.sh
# Fix 'pam_env' issue with unset locale
RUN locale >/etc/default/locale

# Limit the syslog size to 100MB
RUN sed -i '/rotate /a\\tsize 100m' /etc/logrotate.d/rsyslog
RUN sed -i '/-\/var\/log\/syslog/i\$outchannel mysyslog,\/var\/log\/syslog,104857600' /etc/rsyslog.d/50-default.conf
RUN sed -i '/-\/var\/log\/syslog/i\*.*;auth,authpriv.none  :omfile:$mysyslog' /etc/rsyslog.d/50-default.conf
RUN sed -i '/-\/var\/log\/syslog/d' /etc/rsyslog.d/50-default.conf

# Add in systemd files
COPY _artifacts/systemd/* /etc/systemd/system/
RUN systemctl enable cpcd.service
ENTRYPOINT ["/sbin/init"]

# Install artifacts
COPY _artifacts/bin_${SYSTEM_ARCH}/* /usr/local/bin/
COPY _artifacts/etc/* /usr/local/etc/
COPY _artifacts/firmware/* /opt/
