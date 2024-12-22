#!/bin/bash
source <(grep VERSION .ini)
source <(grep PORT .ini)
source <(grep CONTAINER_NAME .ini)
source <(grep LOG_FILE .ini)

rm $LOG_FILE

docker run --name $CONTAINER_NAME -p $PORT:15001 --rm ghcr.io/dmirtydmirty/govnochat:$VERSION  > $LOG_FILE &
