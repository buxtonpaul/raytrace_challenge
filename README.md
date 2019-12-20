# Raytracer Challenge
Raytracer development working through the book The Ray Tracer Challenge
 
Build Status -: ![alt text](https://github.com/buxtonpaul/raytrace_challenge/workflows/Build_Test/badge.svg "Build Status")

# Todo 
- [ ] Tidy up test names
- [ ] Implment other point/vector functions
- [ ] Move Vector and Point to inherted classes with raytuple as the base class
- [ ] Move tuple functions to cope with arbitrary lengths...
- [ ] Rework using slices....
- [ ] Override std::vector<double> == operator... 
- [ ] Replace use of valarray with vector

Look at using lambda e.g.
```
std::transform(a.begin(), a.end(),     // first
               b.begin(),              // second
               std::back_inserter(c),  // output
               [](double n, double m) { return n + m; } ); 
```

