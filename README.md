# Raytracer Challenge
Raytracer development working through the book [The Ray Tracer Challenge](https://www.amazon.co.uk/Ray-Tracer-Challenge-Jamis-Buck/dp/1680502719/ref=sr_1_1?crid=VTW2K8UE11OA&keywords=ray+tracer+challenge&qid=1577102545&sprefix=ray+tr%2Caps%2C290&sr=8-1)

 
![alt text](https://github.com/buxtonpaul/raytrace_challenge/workflows/Build_Test/badge.svg "Build Status")

----

# Todo 
- [ ] Improve float_equals to handle zero
- [ ] Implement pre_inverse of objects transformations
- [ ] Add doxygen comments
- [ ] Refactor cmake and folders to be cleaner
- [ ] Implment other point/vector functions/tests. Try ad tidy up operators again (VECTOR-VECTOR)
- [ ] Refactor shape and intersection files
- [ ] Rework using slices....
- [x] Implement vector negate
- [x] Look at gtest shared setup.
- [x] Rework color to use RGB inputs
- [x] Enable use of pre-build gtest.
- [x] Move Vector and Point to inherted classes with raytuple as the base class
- [x] Implement transforms and identits as class members to allow chaining!
- [x] Implement time based filename generator
- [x] Tidy up test names
- [x] Update to use namespace for matrix as well

----
# Build info
The project uses cmake
Basic build would look like
```
mkdir build
cd build
cmake <path to source>
make
```

If you have downloaded gtest then you can point cmake at it so that you do not need to redownloade/build it using
```
mkdir build
cd build
cmake -DGTEST_ROOT=<path to gtest install> <path to source>
make 
```
# Implementation notes.

Build instructions
mkdir build
cd buil

Currently the lighting calculation is a stand alone function in the light module.
Perhaps will need to be turned into class or similar?



----
## Latest output
![alt test](./latest.png)

----
## Performance
### Debug
```
real    2m44.407s
user    2m44.297s
sys     0m0.063s
```

### Release
```
real    0m16.793s
user    0m16.703s
sys     0m0.078s
```
