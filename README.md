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

* main detect if the biggest face on the camera is recognized and, If so, send the class Id in the console

