#!/bin/bash

cd deb/cgame2-*/
debuild -S -kED52A1E7B5D34474
cd ../
dput ppa:youlanjie/cgame2 cgame2_*_source.changes

