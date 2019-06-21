# FaceReco

* Use photo to create some photos to train

* Use train to train
usage:
```
./train input.csv outputFolder
```


Build files
```
g++ -o photo photo.cpp `pkg-config  --cflags --libs opencv`
```
