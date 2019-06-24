# Facial Recognition

## Train program
train the model with the input files and save it in `trainer.yml`    
### Usage :
```
./train input.csv
```
### Build
```
g++ -o train train.cpp `pkg-config  --cflags --libs opencv`
```


## Reco program :
Detect the biggest face on the camera feed and acknowledge it as close as possible to one of the faces in the train model
### Require :
A trained `trainer.yml` file for an `EigenFaceRecognizer`.
The size of the trained input should be 92x92

### Usage :
```
./reco
```
### Build
```
g++ -o reco reco.cpp `pkg-config  --cflags --libs opencv`
```

## TakePhoto program :
photo is a program to take some facial photo (using key 'p')

### Usage :
```
./photo
```
### Build
```
g++ -o photo photo.cpp `pkg-config  --cflags --libs opencv`
```
