#!/bin/bash
# demonstrate the shift command
echo I see $# arguments: "$@"
shift
echo now I see $# arguments: "$@"
exit 0

