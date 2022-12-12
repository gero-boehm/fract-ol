#!/bin/bash
now=$(date +'%Y-%m-%dT%H:%M:%S')
git add *
git commit -m "$(echo $@)"
git push