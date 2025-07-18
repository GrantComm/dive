#!/bin/bash

# Copyright 2025 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Usage: replay-with-dump.sh GFXR [GFXA]
#
# If you have more than one adb device, set ANDROID_SERIAL.
# GFXR is required. If the capture doesn't use the asset file, GFXA is optional

set -eux

if [ $# -lt 1 ]; then
    echo "Usage: replay-with-dump.sh GFXR [GFXA]"
    exit 1
fi

GFXR=$1
GFXR_BASENAME=$(basename "$GFXR")
BUILD_DIR=build
JSON_BASENAME=dump.json
JSON="$BUILD_DIR/$JSON_BASENAME"
# Fairly reliable directory on remote device, as long as app has MANAGE_EXTERNAL_STORAGE permissions.
# /data/local/tmp doesn't work on all devices tested.
REMOTE_TEMP_DIR=/sdcard/Download
PUSH_DIR="$REMOTE_TEMP_DIR/replay"
DUMP_DIR="$REMOTE_TEMP_DIR/dump"
GFXR_DUMP_RESOURCES=$(find "$BUILD_DIR" -name gfxr_dump_resources -executable -type f)
GFXRECON=./third_party/gfxreconstruct/android/scripts/gfxrecon.py
REPLAY_PACKAGE=com.lunarg.gfxreconstruct.replay

# Uninstall first since install can fail if the APK has a different cert from the one installed (i.e. it was built on another machine)
adb shell pm path "$REPLAY_PACKAGE" && adb uninstall "$REPLAY_PACKAGE"
python "$GFXRECON" install-apk ./install/gfxr-replay.apk
# Currently, REMOTE_TEMP_DIR is /sdcard/Download. Ensure the app has permissions to use it
# was not required on all devices tested but doesn't hurt.
adb shell appops set "$REPLAY_PACKAGE" MANAGE_EXTERNAL_STORAGE allow

adb logcat -c

$GFXR_DUMP_RESOURCES --last_draw_only "$GFXR" "$JSON"
adb shell mkdir -p "$PUSH_DIR"
adb shell mkdir -p "$DUMP_DIR"
adb push "$GFXR" "$JSON" "$PUSH_DIR"
if [ $# -eq 2 ]; then
    GFXA="$2"
    adb push "$GFXA" "$PUSH_DIR"
fi
python "$GFXRECON" replay \
    --dump-resources "$PUSH_DIR/$JSON_BASENAME" \
    --dump-resources-dir "$DUMP_DIR" \
    "$PUSH_DIR/$GFXR_BASENAME"

# gfxrecon.py replay does not wait for the app to start so.
# In order to use pidof to determine when the replay is done, we need to give it time to launch first.
sleep 5
# We can infer that replay is finished when the replay app process is gone.
while adb shell pidof "$REPLAY_PACKAGE"
do
    sleep 1
done

adb logcat -d -s gfxrecon
adb pull "$DUMP_DIR"
adb shell rm -rf "$DUMP_DIR"
adb shell rm -rf "$PUSH_DIR"
