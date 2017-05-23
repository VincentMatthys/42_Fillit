# 42_Fillit

## Project Fillit @ 42

The goal of this project is to arrange the Tetriminos among themselves to make the
smallest possible square, but in some cases, this square may have holes when some given
pieces won’t fit perfectly with others.


## Generator
You can generate pieces with
```
python3 generator.py [1 to 26]
```
Save the generated pieces with the following command line
```
python3 generator.py [1 to 26] > testing_file
```

## To test the fillit
Take a test file in trials/ or generate one, then write :
```
make ; make clean
./fillit [generate_test_file]
```
