ROOTDIR="/DataStructuresHWs/hw1_data"
SCRIPTS_DIR="${ROOTDIR}/scripts"
IO_DIR="${ROOTDIR}/input_output"

echo 'compiling'
g++ main.cpp -o justify.exe

echo 'executing flush left'
${SCRIPTS_DIR}/justify.exe ${IO_DIR}/example.txt fl_out.txt 16 flush_left

echo 'executing flush right'
${SCRIPTS_DIR}/justify.exe ${IO_DIR}/example.txt fr_out.txt 16 flush_right

echo 'executing full justify'
${SCRIPTS_DIR}/justify.exe ${IO_DIR}/example.txt full_out.txt 16 full_justify

RETURN_STATUS=$?
if [ RETURN_STATUS -ne 0 ]; do
	echo 'Failed... exiting...'
	exit 1
else
	echo 'Success! exiting ...'
	exit 0
fi