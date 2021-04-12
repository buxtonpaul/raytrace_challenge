# Raytracer Challenge
Raytracer development working through the book [The Ray Tracer Challenge](https://www.amazon.co.uk/Ray-Tracer-Challenge-Jamis-Buck/dp/1680502719/ref=sr_1_1?crid=VTW2K8UE11OA&keywords=ray+tracer+challenge&qid=1577102545&sprefix=ray+tr%2Caps%2C290&sr=8-1)

 
![alt text](https://github.com/buxtonpaul/raytrace_challenge/workflows/Build_Test/badge.svg "Build Status")

----

# Todo 
- [ ] Improve gradient to transition smoothly after x=1
- [ ] Nested patterns - Patterns should be provided other patterns. Only solid color pattern takes a color.
- [ ] Specify file and resolution as commandline params
- [ ] Implement cones
- [ ] Implement scene management
- [ ] Bounding boxes
- [ ] Improve float_equals to handle zero ?
- [ ] Rewrite gethit using lower_bound ?
- [ ] Refactor color to be simple struct ?
- [ ] Add doxygen comments
- [ ] Refactor cmake and folders to be cleaner ?
- [ ] Implment other point/vector functions/tests. Try and tidy up operators again (VECTOR-VECTOR) ?
- [ ] Refactor shape and intersection files
- [ ] Rework using slices....
- [ ] Canvas as a template
- [ ] Other file output (PNG/TIFF)?
- [ ] Refactor tuples/vectors/points. 

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


Currently the lighting calculation is a stand alone function in the light module.
Perhaps will need to be turned into class or similar?



----
## Latest output
![alt test](./latest.png)

----
## Performance (rendering latest image)

Implementing caching of inverse provided ~*6 performance improvement
### Multi Threaded (using OpenMP parallel for)
```

real    0m3.900s
user    0m30.559s
sys     0m0.020s
```
