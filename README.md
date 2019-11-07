# architectural_raytracer
Raytracer for rendering architechtural designs in C++ (probably).

```
$ git clone git@github.com:CCS-1L-F19/architectural_raytracer.git
$ make clean
$ make main
$ ./main [1] [2] [3] [4]
```
[1]: Rays per Pixel

( [2] , [3] , [4] ): Coordinates of camera

Good values for a demo are (1,2,3,4) = (10,6,4,2)

The image will be outputted to the image file hell.ppm.

Open image file in GIMP or [online ppm viewer](http://paulcuth.me.uk/netpbm-viewer/)

It should look something like 

![](https://i.imgur.com/XLNk4gS.png)

A cooler image, that took a bit longer to render, is below:

![](https://i.imgur.com/AgZUNIn.png)
