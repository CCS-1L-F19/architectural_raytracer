# architectural_raytracer

Raytracer for rendering architechtural designs in C++ (probably).

```
$ git clone git@github.com:CCS-1L-F19/architectural_raytracer.git
$ cd src
$ make clean
$ make main
$ ./main [1] [2] [3] [4]
```

Where:
* [1] Rays per pixel
* [2] [3] [4] are the coordinates of the camera (x,y,z)

Example (these are good values for a demo)
```
$ ./main 10 6 4 2
```

The image will be outputted to the image file `hell.ppm`.

Open image file in GIMP or [online ppm viewer](http://paulcuth.me.uk/netpbm-viewer/)

It should look something like 

![](https://i.imgur.com/XLNk4gS.png)

A cooler image, that took a bit longer to render, is below:

![](https://i.imgur.com/AgZUNIn.png)

To generate new documentation, cd into `docs` and run `doxygen`. To reconfigure, edit  `Doxyfile`.

Documentation for this project can be found at: https://ccs-1l-f19.github.io/architectural_raytracer/
