# architectural_raytracer
Raytracer for rendering architechtural designs in C++ (probably).

```
$ git clone git@github.com:CCS-1L-F19/architectural_raytracer.git
$ cd hari\'s\ experiments/
$ make clean
$ make main
$ ./main [1] [2] [3] [4] > [filename].ppm
```
[1]: Rays per Pixel

( [2] , [3] , [4] ): Coordinates of camera

Good values for a demo are (1,2,3,4) = (20,0,0,0.5)

[filename]: Name of image file

Open image file in GIMP or [online ppm viewer](http://paulcuth.me.uk/netpbm-viewer/)

It should look something like 

![](https://i.imgur.com/7JLyUGV.png)
