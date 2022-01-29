#! /usr/bin/python

import argparse
import svgpathtools
import sys

RESOL = 10

def normalize(dest) :
    """deset: Scale the dataset so that the greatest translation
       goes to 1.0; center of gravity goes to origin."""
    # Center of gravity
    xc     = yc = 0.0
    dl     = len(dset)
    min_r  = sys.maxsize
    max_r  = -sys.maxsize
    min_i  = sys.maxsize
    max_i  = -sys.maxsize
    
    for k in range(0, dl, 1) :
        xc += dset[k].real
        yc += dset[k].imag
        if min_r > dset[k].real :
            min_r = dset[k].real
        if max_r < dset[k].real :
            max_r = dset[k].real
        if min_i > dset[k].imag :
            min_i = dset[k].imag
        if max_i < dset[k].imag :
            max_i = dset[k].imag
    cen  = complex(xc/dl, yc/dl)
    ur   = complex(max_r, max_i)
    ll   = complex(min_r, min_i)
    maxd = abs(ur - ll)
    for k in range(0, dl, 1) :
        dset[k]     = (dset[k] - cen)/maxd 

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Plot points from SVG Path.')
    parser.add_argument('-d', '--density', type=int, action='store',  help='Plot point quantity as powers of two; 4 → 2⁴ → 16. Larger → denser. Defaults to 10 (1024)', default=RESOL)
    parser.add_argument('-o', '--output',  type=str, action='store',  help='Text file for output plots.')
    parser.add_argument('-n', '--normalize',         action='store_const', const='y', default=None, help='Normalize plots. (1) Center of gravity maps to origin. (2) Scaling of largest distance to 1, (3) Preserves aspect ratio.')
    parser.add_argument('fname', type=str, nargs=1, help='SVG file, 1.1 or lower')
    args=parser.parse_args()
    fresolv      = 2**int(args.density)
    paths, attrs = svgpathtools.svg2paths(args.fname[0])
    path_0       = paths[0]
    scale        = 1.0/(fresolv-1)
    dset         = [path_0.point(k) for k in [scale*j for j in range(fresolv)]]
    if type(args.normalize) == type('y') and args.normalize == 'y':
        normalize(dset)
    fd           = open(args.output, 'w', encoding='UTF-8')
    for i in range(len(dset)):
        fd.write("{0:03.9g},{1:03.9g}\n".format(dset[i].real, dset[i].imag))
    fd.close()
args.output[0]
