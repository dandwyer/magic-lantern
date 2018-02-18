#!/bin/bash
# script to manage MPU spell files
# run with -p to re-create patch files (after manually changing MPU spell files)
# run without arguments to re-create spell files (after updating the parsing script or the log files)

# export known spells to C first
python extract_init_spells.py > known_spells.h

LOGS_PATH=../../../../startup-logs

for log in \
        60D-mpu-large.log \
        550D-startup2.LOG \
        70D-startup-nf.log \
        5D3-123-sd-startup-menu-q-1.LOG \
        600D-startup.log \
        5D2-startup-ilia.log \
        450D-dm-mpu.log \
        700D-startup.LOG \
        EOSM-startup.LOG \
        500D-startup-menudisp.log \
        50D-startup-format.log \
        6D-startup_photo_mode.LOG \
    ; do

    MODEL=`echo $log | grep -oE "^[A-Z0-9]+"`
    echo $log $MODEL
    
    if [[ $@ == **-p** ]]; then
        # create patch files (differences from the autogenerated version)
        # run this after making some change to a spells file
        python extract_init_spells.py $LOGS_PATH/$log > ${MODEL}x.h
        diff -u --label=${MODEL}.h --label=${MODEL}.h ${MODEL}x.h ${MODEL}.h > ${MODEL}.patch
        rm ${MODEL}x.h
    else
        # autogenerate MPU spell files and apply user patches
        # run this after updating extract_init_spells.py or some input log file(s)
        python extract_init_spells.py $LOGS_PATH/$log > ${MODEL}.h
        patch -p0 < ${MODEL}.patch
    fi
done
