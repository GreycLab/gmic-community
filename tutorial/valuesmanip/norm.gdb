===
![Théâtre Molière, Sète, Hérault](image/theatre_moliere.png)
**usphere.png**
*Color, luminance and norm.*
===
Norm regards the channel values of a pixel as components of a vector; it replaces the pixel with a single-channel value, the Euclidean length of that vector. See ''-orientation'' for the general discussion on RGB color spaces, including the treatment of a color as a position vector in that space.

# Luminance, Norm and Orientation: What is the Story?
In the RGB color space framework, ''-norm'' is complementary to ''-orientation'', which normalizes the channel values so that the vector so formed is of unit length. If it is one's wont to regard an image as consisting of color vectors, then ''-norm'' extracts the length of those vectors and ''-orientation'' extracts their direction. Norm is rarely an end in itself; it is an intermediary command that builds a dataset of vector lengths, generally to support further calculations.

Visually, -norm is often thought to be a kind of -luminance command, as its results are superficially like it. -luminance is intended to give a displayable result but  -norm will often exceed the upper limit of the 8 bit intensity range (0,255) The image on the left of Théâtre Molière, Sète, Hérault compares original color, luminance (middle) and norm (right). Since some pixels exceeded 255 in the right hand section, the highlights are flat and the overall results are washed out.

# Example


# Command reference
===
"""
gmic -h norm
"""
===
