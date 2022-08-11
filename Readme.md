# reproduce steps

## run a debian bullsyeye docker container

* docker run -itd -name reproduce continuumio/miniconda3:4.12.0  bash

## add this repo to container 

## pip install

cd mmocr
pip install -r requirements.txt
pip install -e .

## make

## test

./test and you will see the stuck in loading model...
