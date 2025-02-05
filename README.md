# hls_parse
Parses an HLS playlist.

The library, test, and example code for this project is
available at:
https://github.com/barryaronson/hls_parse.git

`git clone https://github.com/barryaronson/hls_parse.git`
`cd hls_parse`

It has been built and tested on Windows 10 using WSL-Ubuntu and MacOS zsh.
Starting in the `hls_parse` directory:

`mkdir build`
`cd build`
`cmake -DCMAKE_BUILD_TYPE=Debug .. && make`

The example program parses a playlist file stored locally or will download 
one given a URL.

To run it:

`./example/hls_parse_example ../example/master_unenc_hdr10_all.m3u8`

Or

`./example/hls_parse_example --help`

Implementation Notes

The `Playlist` class was adapted from a different project.

Traditionally, input is split into tokens before parsing. This could have
been done using std::regex. However, attribute values of quoted strings
with multiple comma separated items would have been split into separate
tokens. This could have been handled by reading tokens until a know attribute
name was found and pushing that back. However, this approach would also mean
having to copy the string array to an std::string object. Also, tag and
attribute identifiers would have to have been compared to known values.

The approach chosen uses the first letter of a tag or attribute to narrow
the search and then does a string comparison to fully identify the tag or
attribute. Usually, there is only one to three identifiers per first letter.
Finding tokens and parsing is done in one pass.

Tags are represented by individual classes. Within each tag class are
programmatically useable attribute values (e.g., integers are converted
from strings and stored as integers). The attribute values are public
to reduce code clutter. This is fairly safe as they are unlikely to
change (given that this is based on an RFC) and clearly should not
be written to by consumers.