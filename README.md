# architectural_raytracer

Raytracer for rendering .stl files using C++. Put the files you want to render inside the `STL_files` folder.

Input your 

```
$ git clone git@github.com:CCS-1L-F19/architectural_raytracer.git
$ cd src
$ make clean
$ make main
$ ./main [file] [1] [2] [3] [4] [5] [6] [7]
```

Where:
* [file] is the name of the file, with .stl after it.
* [1] samples/rays per pixel
* [2] [3] [4] are the coordinates of the camera (x,y,z)
* [5] [7] [8] are the coordinates you want to look at

An example command to test your setup (these are good values for a demo)
```
$ ./main teapot.stl 30 0 5 20 0 0 0
```

The image will be outputted to the image file `output.ppm` in the `images` folder.

Open image file in GIMP or [online ppm viewer](http://paulcuth.me.uk/netpbm-viewer/)

It should look something like 

![](https://i.imgur.com/vKxx5uv.png)

Another example, this one of `dragon.stl`, is below:
```
$ ./main dragon.stl 40 0 30 90 0 0 0
```

The result should be look like this:

![](https://i.imgur.com/sNxnaI9.png)

A cooler image, that was rendered during the progress of this project, is below:

![](https://i.imgur.com/AgZUNIn.png)

To generate new documentation, cd into `docs` and run `doxygen`. To reconfigure, edit  `Doxyfile`.

Documentation for this project can be found at: https://ccs-1l-f19.github.io/architectural_raytracer/
