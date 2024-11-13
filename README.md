# hls_parse
Parses an HLS playlist.

The library, test, and example code for this project is
available at:
https://github.com/barryaronson/hls_parse.git

`git clone https://github.com/barryaronson/hls_parse.git`
`cd hls_parse`

It has been built and tested on Windows 10 using WSL-Ubuntu.
It should also build and run in MacOS zsh or Linux bash.
Starting in the `hls_parse` directory:

`mkdir build`
`cd build`
`cmake -DCMAKE_BUILD_TYPE=Debug .. && make`

The example program parses the playlist and sorts the STREAM-INF
tags by the value of the BANDWIDTH attribute in ascending or
descending order.

To run it:

`./example/hls_parse_example ../example/master_unenc_hdr10_all.m3u8`

Or

`./example/hls_parse_example -help`
