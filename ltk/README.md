# [ HU-LTK ]
This small program opens in browser the satellite tracking webpage.

## [ Usage ]
The satellite array can be found in the source file `main.cpp`. Trackers may be openned by addressing them via name, `/<some_name>`, or via array offset, `:<some_offset>`.
```
HU-LTK :0
is the same as
HU-LTK /NOAA-15 
```

The default url is `https://www.n2yo.com/?s=`. This may be changed using the option `--url <some_url>`.
```
HU-LTK --url <some_url>
```
Caution! The trackers opened before this option are not affected.
```
HU-LTK :1 --url <some_url> :2
```
This will change the url only for `:2`. The option may be used multiple times.