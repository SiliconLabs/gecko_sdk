#!/bin/bash

CONTAINER_NAME=${CONTAINER_NAME:-"siliconlabsinc/multiprotocol"}

DAEMON=1
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            echo "Usage: $0 [options]"
            echo -e "\t-s\tStop running the multiprotocol container"
            echo -e "\t-c\tMount the supplied cpcd.conf file and start the multiprotocol container"
            echo -e "\t-o\tOpen a bash shell in the running multiprotocol container"
            echo -e "\t-O\tStart ot-cli application in the running multiprotocol container"
            echo -e "\t-T\tStart OTBR and ot-ctl application in the running multiprotocol container"
            echo -e "\t-Z\tStart Zigbeed and Z3GatewayHost application in the running multiprotocol container"
            echo -e "\t-L\tStart Bluetooth and bluetoothctl application in the running multiprotocol container"
            echo -e "\t-b\tStart the multiprotocol container as a bash shell only"
            echo "By default, this script will start the multiprotocol container"
            exit
            ;;
        -s|--stop)
            docker stop -t 0 multiprotocol
            exit
            ;;
        -c|--cpcd-conf)
            shift
            CPCD_CONFIG_FILE=$(realpath $1)
            shift
            ;;
        -l|--log)
            docker exec -it multiprotocol journalctl -fexu cpcd
            exit
            ;;
        -o|--open)
            docker exec -it multiprotocol /bin/bash
            exit
            ;;
        -O|--ot-cli)
            docker exec -it multiprotocol /usr/local/bin/ot-cli 'spinel+cpc://cpcd_0?iid=2'
            exit
            ;;
        -T|--ot-ctl)
            docker exec -it multiprotocol systemctl start otbr
            echo "OTBR started. Attempting to run ot-ctl..."
            while 
                docker exec -it multiprotocol ot-ctl
                [[ $? -eq 1 ]]
            do
                sleep 1
            done
            exit
            ;;
        -Z|--zigbee-host)
            docker exec -it multiprotocol systemctl start zigbeed
            sleep 3
            docker exec -it multiprotocol /usr/local/bin/Z3Gateway -p ttyZigbeeNCP
            exit
            ;;
        -L|--bluetoothctl)
            # stop bluetoothd on the host
            sudo service bluetooth stop
            # disable bluetoothd on the host
            sudo systemctl mask bluetooth.service
            docker exec -it multiprotocol systemctl start hciattach
            docker exec -it multiprotocol bluetoothctl
            exit
            ;;
        -b|--bash)
            DAEMON=0
            shift
            ;;
        -B|--build)
            BUILD=1
            # Only affect local build of multiprotocol
            CONTAINER_NAME=multiprotocol
            shift
            ;;
        *)
            echo "Unrecognized option '$1'"
            exit
            ;;
    esac
done

if [ "$BUILD" == "1" ]; then
    docker pull siliconlabsinc/otbr_cpc_private
    docker build -t ${CONTAINER_NAME} --build-arg BASE_CONTAINER=siliconlabsinc/otbr_cpc_private .
    if [ $? -ne 0 ]; then
        echo "Failed to build ${CONTAINER_NAME}"
        exit
    fi
else
    docker pull ${CONTAINER_NAME}
fi

docker stop -t 0 multiprotocol # stop container if it is running

RUN_ARGS="--rm --name multiprotocol" # Clean up after run
if [ -e "$CPCD_CONFIG_FILE" ]; then
    echo "Using host's cpcd config file: $CPCD_CONFIG_FILE"
    RUN_ARGS+=" -v $CPCD_CONFIG_FILE:/usr/local/etc/cpcd.conf:ro"
fi
RUN_ARGS+=" -v /tmp/multiprotocol-container/log:/var/log/" # Add in logging folder
RUN_ARGS+=" -v /accept_silabs_msla" # Accept the MSLA for Zigbeed
RUN_ARGS+=" --privileged --cap-add SYS_ADMIN" # Add in security permissions
RUN_ARGS+=" --cap-add=SYS_ADMIN --cap-add=NET_ADMIN --net=host" # Add bluetooth

if [ "$DAEMON" == "1" ]; then
    RUN_ARGS+=" -d" # Start as a daemon
else
    RUN_ARGS+=" -it --entrypoint /bin/bash" # Drop into a bash shell on start
fi

echo "Running 'docker run ${RUN_ARGS} ${CONTAINER_NAME}'"
docker run ${RUN_ARGS} ${CONTAINER_NAME}
