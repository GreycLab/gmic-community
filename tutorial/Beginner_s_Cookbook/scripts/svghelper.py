#! /usr/bin/python

import argparse
import svgpathtools
import sys

RESOL = 10

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Plot points from SVG Path.')
    parser.add_argument('-d', '--density', action='store', nargs=1, help='Density of plot points, as powers of two. Larger → denser.', default=RESOL)
    parser.add_argument('-o', '--output', type=str, nargs=1, help='Text file for output plots.')
    parser.add_argument('fname', type=str, nargs=1, help='SVG file, 1.1 or lower')
    args=parser.parse_args()
    fresolv      = 2**int(args.density[0])
    paths, attrs = svgpathtools.svg2paths(args.fname[0])
    path_0       = paths[0]
    scale        = 1.0/(fresolv-1)
    dset         = [path_0.point(k) for k in [scale*j for j in range(fresolv)]]
    fd           = open(args.output[0], 'w')
    for i in range(len(dset)):
        fd.write("{0:03.9g},{1:03.9g}\n".format(dset[i].real, dset[i].imag))
    fd.close()
