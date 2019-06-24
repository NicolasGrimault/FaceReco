# FaceReco

Exemple of command to build code
```
g++ -o train train.cpp `pkg-config  --cflags --libs opencv`
```

# Usage

* photo is a program to take some facial photo (using key 'p')

* train train the model with the input files and save it in `trainer.yml` 
usage:
```
./train input.csv
```

* reco detect the biggest face on the camera and send the closest class Id in the console

The `trainer.yml` must be in the same folder (`Reco/`) as the reco program
