#!/bin/bash
source <(grep VERSION .ini)
source <(grep PORT .ini)
source <(grep CONTAINER_NAME .ini)
source <(grep LOG_FILE .ini)

tail -f $LOG_FILE -n 30 --retry

