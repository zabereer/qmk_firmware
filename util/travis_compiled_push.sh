#!/bin/bash

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

git config --global user.name "Travis CI"
git config --global user.email "jack.humb+travis.ci@gmail.com"

if [[ "$TRAVIS_BRANCH" == "master" && "$TRAVIS_PULL_REQUEST" == "false" ]] ; then

increment_version ()
{
  declare -a part=( ${1//\./ } )
  part[2]=$((part[2] + 1))
  new="${part[*]}"
  echo -e "${new// /.}"
} 

NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)' | wc -l)
if [[ $NEFM -gt 0 ]] ; then
	echo "Essential files modified."
	git fetch --tags
	lasttag=$(git tag | grep -Ev '\-' | xargs -I@ git log --format=format:"%ai @%n" -1 @ | sort -V | awk '{print $4}' | tail -1)
	newtag=$(increment_version $lasttag)
	git tag $newtag
	git push --tags -q https://$GH_TOKEN@github.com/qmk/qmk_firmware
else
	echo "No essential files modified."
fi

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then

	make ergodox-ez AUTOGEN=true

	find . -name ".build" | xargs rm -rf
	cd ..
	git clone https://$GH_TOKEN@github.com/jackhumbert/qmk.fm.git
	cd qmk.fm
	git submodule update --init --recursive
	#rm -rf keyboard
	#rm -rf keyboards
	yes | cp -rf ../qmk_firmware/keyboards .
	#mkdir keyboards/ergodox_ez/
	cp ../qmk_firmware/util/ergodox_ez.html keyboards/ergodox_ez/index.html
	cp ../qmk_firmware/readme.md qmk_readme.md
	./generate.sh

	git add -A
	git commit -m "generated from qmk/qmk_firmware@${rev}" 
	git push

fi

fi